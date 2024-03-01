#include "FxDecodeThread.h"
#include "FxPacketQueue.h"
#include "FxFrameQueue.h"
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
            pCodecCtx = avcodec_alloc_context3(NULL);
            int ret = avcodec_parameters_to_context(pCodecCtx, par);
            if (ret < 0) {

                av_strerror(ret, err2str, sizeof(err2str));
                printf("%s(), av_read_frame failed, ret:%d, err2str:%s\n", __FUNCTION__, ret, err2str);
                return -1;
            }

            auto codec = avcodec_find_decoder(pCodecCtx->codec_id);//如何制定硬件解码
            if (!codec) {
                printf("%s(), avcodec_find_decoder failed, ret:%d", __FUNCTION__, ret);
                return -1;
            }

            ret = avcodec_open2(pCodecCtx, codec, NULL);
            if (ret < 0) {

                av_strerror(ret, err2str, sizeof(err2str));
                printf("%s(), avcodec_open2 failed, ret:%d, err2str:%s\n", __FUNCTION__, ret, err2str);
                return -1;
            }

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

        void FxDecodeThread::run()
        {
            printf("%s(), start decode\n", __FUNCTION__);
            AVFrame *frame = av_frame_alloc();
            bool eofReached = false; // 添加一个标志表示是否已经读取到文件末尾
            while(!bAbort) {


                if (pFrameQueuePtr->size() > 10) {
                    std::this_thread::sleep_for(std::chrono::seconds(10));
                    continue;
                }

                AVPacket *pkt = pPacketQueuePtr->pop(10);
                if (pkt) {
                    int ret = avcodec_send_packet(pCodecCtx, pkt);
                    av_packet_free(&pkt);
                    if (ret < 0) {
                        av_strerror(ret, err2str, sizeof(err2str));
                        printf("\n%s(), avcodec_open2 failed, ret:%d, err2str:%s\n", __FUNCTION__, ret, err2str);
                        break;
                    }
                    //读取解码后的frame
                    while(true) {
                        ret = avcodec_receive_frame(pCodecCtx, frame);
                        if (ret == 0) {
                            pFrameQueuePtr->push(frame);
                            printf("%s(), avcodec_receive_frame name:%s "
                                   "width:%d, height:%d ,pict_type:%d, sample_aspect_ratio:%d ,sample_rate:%d, pts:%d ,key_frame:%d ,size:%d\n",
                                   __FUNCTION__,
                                   pCodecCtx->codec->name,
                                   frame->width,
                                   frame->height,
                                   frame->pict_type,
                                   frame->sample_aspect_ratio,
                                   frame->sample_rate,
                                   frame->pts,
                                   frame->key_frame,
                                   pFrameQueuePtr->size());
                            continue;
                        } else if (AVERROR(EAGAIN) == ret) {
                            break;
                        } else {
                            if (ret == AVERROR_EOF) {
                                eofReached = true;
                                printf("\n%s(), avcodec_receive_frame (EOF reached)\n", __FUNCTION__);
                            } else {
                                av_strerror(ret, err2str, sizeof(err2str));
                                printf("\n%s(), avcodec_receive_frame failed, ret:%d, err2str:%s\n", __FUNCTION__, ret, err2str);
                            }
                            bAbort = true;
                            break;
                        }
                    }
                } else {
                    printf("%s(), did get any packet\n", __FUNCTION__);
                }
            }
            // 当读取到文件末尾时输出相应的消息
            if (eofReached) {
                printf("%s finished (EOF reached)", __FUNCTION__);// 设置标志为 true 表示已经读取到文件末尾
            } else {
                printf("%s  finished", __FUNCTION__);
            }
        }

    }// namespace player
}// namespace fox
