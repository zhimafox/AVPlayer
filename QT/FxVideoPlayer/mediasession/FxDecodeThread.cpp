#include "FxDecodeThread.h"
#include "FxPacketQueue.h"
#include "FxFrameQueue.h"
#include <QDebug>
#include <QImage>
#include <QMutex>
#include <qdatetime.h>
using namespace fox::player;

namespace fox
{
    namespace player
    {
        FxDecodeThread::FxDecodeThread(FxPacketQueuePtr packetQueuePtr, FxFrameQueuePtr frameQueuePtr)
        : pPacketQueuePtr(packetQueuePtr)
        , pFrameQueuePtr(frameQueuePtr) {

        }

        FxDecodeThread::~FxDecodeThread()
        {

        }

        int FxDecodeThread::init(AVCodecParameters *par)
        {
            if (!par) {
                printf("%s, init AVCodecParameters is null");
                return -1;
            }

            // 通过解码器ID获取视频解码器（新版本返回值必须使用const）
            const AVCodec* codec = avcodec_find_decoder(par->codec_id);

            // 分配AVCodecContext并将其字段设置为默认值。
            pCodecCtx = avcodec_alloc_context3(codec);
            if(!pCodecCtx)
            {
                return -1;
            }

            // 使用视频流的codecpar为解码器上下文赋值
            int ret = avcodec_parameters_to_context(pCodecCtx, par);
            if(ret < 0)
            {

                return -1;
            }

            pCodecCtx->flags2 |= AV_CODEC_FLAG2_FAST;    // 允许不符合规范的加速技巧。
            pCodecCtx->thread_count = 8;                 // 使用8线程解码

            // 初始化解码器上下文，如果之前avcodec_alloc_context3传入了解码器，这里设置NULL就可以
            ret = avcodec_open2(pCodecCtx, nullptr, nullptr);
            if(ret < 0)
            {
                return -1;
            }
            return ret;
        }


        int FxDecodeThread::start() {
            mThread = std::thread(&FxDecodeThread::run, this);
            bThreadRunning = true;
            return 0;
        }

        int FxDecodeThread::stop() {
            if (bThreadRunning) {
                mThread.join();
            }
            if (pCodecCtx) {
                avcodec_close(pCodecCtx);
            }
            return 0;
        }

        void FxDecodeThread::run() {

            AVFrame *m_frame = av_frame_alloc();
            while(!bAbort) {
                if (pFrameQueuePtr->size() > 10) {
                    std::this_thread::sleep_for(std::chrono::seconds(10));
                    continue;
                }


                // int readRet = av_read_frame(mFmtCtx, m_packet);
                AVPacket *m_packet = pPacketQueuePtr->pop(10);
                int ret = avcodec_send_packet(pCodecCtx, m_packet);
                if(ret < 0)
                {
                    av_strerror(ret, err2str, sizeof(err2str));
                    printf("%s(), avcodec_send_packet failed, ret:%d, err2str:%s\n", __FUNCTION__, ret, err2str);
                    break;
                }

                if (m_packet->pos == 20088) {
                    int i = 0;
                }
                // 将读取到的原始数据包传入解码器
                av_packet_unref(m_packet);  // 释放数据包，引用计数-1，为0时释放空间
                printf("\n%s(), =============================\n", __FUNCTION__);
                while(true) {
                    ret = avcodec_receive_frame(pCodecCtx, m_frame);

                    printf("\n%s(), ++++++++avcodec_receive_frame+++++++++\n", __FUNCTION__);
                    if (ret == AVERROR(EAGAIN)) {
                        av_strerror(ret, err2str, sizeof(err2str));
                        printf("\n%s(), AVERROR(EAGAIN) failed, ret:%d, err2str:%s\n", __FUNCTION__, ret, err2str);
                        break;
                    } else if (ret < 0 ) {
                        if (ret == AVERROR_EOF) {
                            printf("\n%s(), avcodec_receive_frame (EOF reached)\n", __FUNCTION__);
                        } else {
                            av_strerror(ret, err2str, sizeof(err2str));
                            printf("\n%s(), avcodec_receive_frame failed, ret:%d, err2str:%s\n", __FUNCTION__, ret, err2str);
                        }
                        bAbort = true;
                        break;
                    } else {
                        printf("%s(), avcodec_receive_frame name:%s "
                               "width:%d, height:%d ,pict_type:%d, sample_aspect_ratio:%d ,sample_rate:%d, pts:%d ,key_frame:%d\n",
                               __FUNCTION__,
                               pCodecCtx->codec->name,
                               m_frame->width,
                               m_frame->height,
                               m_frame->pict_type,
                               m_frame->sample_aspect_ratio,
                               m_frame->sample_rate,
                               m_frame->pts,
                               m_frame->key_frame);
                        if (m_frame->pict_type == AV_PICTURE_TYPE_P) {
                            printf("%s(),帧类型:AV_PICTURE_TYPE_P", __FUNCTION__);
                        } else if (m_frame->pict_type == AV_PICTURE_TYPE_I) {
                            AVCodecInternal *internal = pCodecCtx->internal;

                            printf("%s(),帧类型:AV_PICTURE_TYPE_I", __FUNCTION__);
                        } else if (m_frame->pict_type == AV_PICTURE_TYPE_B) {
                            printf("%s(),帧类型:AV_PICTURE_TYPE_B", __FUNCTION__);
                        } else {
                            printf("%s(),帧类型:%s:", m_frame->pict_type, __FUNCTION__);
                        }
                    }

                }

            }
            av_frame_unref(m_frame);
        }

    }// namespace player
}// namespace fox
