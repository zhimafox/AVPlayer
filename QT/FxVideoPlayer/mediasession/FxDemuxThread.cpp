#include "FxDemuxThread.h"

extern "C" {        // 用C规则编译指定的代码
// #include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
//#include "libswscale/swscale.h"
//#include "libavutil/imgutils.h"*/
}
#include <unistd.h>
#include "FxPacketQueue.h"

using namespace fox::player;

FxDemuxThread::FxDemuxThread(std::weak_ptr<IFxDemuxThreadCallback> callback, FxPacketQueuePtr audioQueue, FxPacketQueuePtr videoQueue)
    : mCallback(callback)
    , pAudioQueue(audioQueue)
    , pVideoQueue(videoQueue) {
}

int FxDemuxThread::open(const char *url) {

    // 缓冲区大小
    const int bufferSize = 256;
    // 用于存储当前工作目录的缓冲区
    char buffer[bufferSize];

    // 获取当前工作目录
    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        // 输出到控制台
        printf("Current working directory: %s\n", buffer);
    } else {
        // 获取失败时输出错误信息
        perror("getcwd() error");
    }


    if (url == NULL) {

        printf("%s mUrl is empty", __FUNCTION__);
        // return -1;
        mUrl = "test.mp4";
    } else {
        mUrl = url;
    }
    printf("%s mUrl:%s", __FUNCTION__,  mUrl.c_str());
    int ret = avformat_open_input(&mFmtCtx, mUrl.c_str(), NULL, NULL);
    if (ret < 0) {
        av_strerror(ret, err2str, sizeof(err2str));
        printf("%s url:%s open failed, ret:%d, err2str:%s\n", __FUNCTION__, url, ret, err2str);
        return -1;
    }

    ret = avformat_find_stream_info(mFmtCtx, NULL);
    if (ret < 0)  //如果打开媒体文件失败，打印失败原因
    {
        char buf[1024] = { 0 };
        av_strerror(ret, buf, sizeof(buf) - 1);
        printf("avformat_find_stream_info %s failed:%s\n", mUrl.c_str(), buf);
        return -1;
    }


    //打开媒体文件成功
    printf("\n==== av_dump_format in_filename:%s ===\n", mUrl.c_str());
    av_dump_format(mFmtCtx, 0, mUrl.c_str(), 0);
    printf("\n==== av_dump_format finish =======\n\n");
    // url: 调用avformat_open_input读取到的媒体文件的路径/名字
    printf("media name:%s\n", mFmtCtx->url);
    // nb_streams: nb_streams媒体流数量
    printf("stream number:%d\n", mFmtCtx->nb_streams);
    // bit_rate: 媒体文件的码率,单位为bps
    printf("media average ratio:%lldkbps\n",(int64_t)(mFmtCtx->bit_rate/1024));
    // 时间
    int total_seconds, hour, minute, second;
    // duration: 媒体文件时长，单位微妙
    total_seconds = (mFmtCtx->duration) / AV_TIME_BASE;  // 1000us = 1ms, 1000ms = 1秒
    hour = total_seconds / 3600;
    minute = (total_seconds % 3600) / 60;
    second = (total_seconds % 60);
    //通过上述运算，可以得到媒体文件的总时长
    printf("total duration: %02d:%02d:%02d\n", hour, minute, second);
    printf("\n");


    nAudioIndex = av_find_best_stream(mFmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    nVideoIndex = av_find_best_stream(mFmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);

    if (nAudioIndex < 0 && nAudioIndex < 0) {
        printf("%s no any audio and video", __FUNCTION__);
        return -1;
    }
    printf("%s audioIndex:%d, videoIndex:%d", __FUNCTION__, nAudioIndex, nVideoIndex);

    return -1;
}

int FxDemuxThread::start() {
    mThread = std::thread(&FxDemuxThread::run, this);
    bThreadRunning = true;
    return 0;
}

int FxDemuxThread::stop() {
    if (bThreadRunning) {
        mThread.join();
    }
    avformat_close_input(&mFmtCtx);
    return 0;
}

int FxDemuxThread::run() {
    printf("%s av_read_frame start", __FUNCTION__);
    int ret = 0;
    AVPacket pkt;
    bThreadRunning = true;
    bool eofReached = false; // 添加一个标志表示是否已经读取到文件末尾
    while(!bAbort) {

        if (pAudioQueue->size() > 100 || pVideoQueue->size() > 100) {
            std::this_thread::sleep_for(std::chrono::seconds(10));
            continue;
        }

        ret = av_read_frame(mFmtCtx, &pkt);
        if (ret < 0) {
            if (ret == AVERROR_EOF) {
                eofReached = true; // 设置标志为 true 表示已经读取到文件末尾
            } else {
                av_strerror(ret, err2str, sizeof(err2str));
                printf("%s(), av_read_frame failed, ret:%d, err2str:%s\n", __FUNCTION__, ret, err2str);
            }
            bAbort = true;
        }

        if (pkt.stream_index == nAudioIndex) {
            pAudioQueue->push(&pkt);
            // printf("audio pts: %lld\n", pkt.pts);
            // printf("audio dts: %lld\n", pkt.dts);
            // printf("audio size: %d\n", pkt.size);
            // printf("audio pos: %lld\n", pkt.pos);
            //printf("audio duration: %lf\n\n", pkt.duration * av_q2d(mFmtCtx->streams[nAudioIndex]->time_base));

            auto size = pAudioQueue->size();
            //printf("audio pkt, size:%d\n", size);
        } else if (pkt.stream_index == nVideoIndex) {
            pVideoQueue->push(&pkt);
            // printf("video pts: %lld\n", pkt.pts);
            // printf("video dts: %lld\n", pkt.dts);
            // printf("video size: %d\n", pkt.size);
            // printf("video pos: %lld\n", pkt.pos);
            //printf("video duration: %lf\n\n", pkt.duration * av_q2d(mFmtCtx->streams[nVideoIndex]->time_base));
            auto size = pVideoQueue->size();
            //printf("video pkt, size:%d\n",size);
        } else {
            printf("unknown stream_index:\n", pkt.stream_index);
        }
        av_packet_unref(&pkt);
    }
    bThreadRunning = false;

    // 当读取到文件末尾时输出相应的消息
    if (eofReached) {
        printf("%s av_read_frame finished (EOF reached)", __FUNCTION__);
    } else {
        printf("%s av_read_frame finished", __FUNCTION__);
    }

    return 0;
}

AVCodecParameters *FxDemuxThread::getAudioCodecParameters()
{
    if (nAudioIndex != -1) {
        AVCodecParameters* codecParams = mFmtCtx->streams[nAudioIndex]->codecpar;
        AVStream *in_stream = mFmtCtx->streams[nAudioIndex];// 音频流、视频流、字幕流
        printf("\n");
        printf("----- Audio info:\n");
        // index: 每个流成分在ffmpeg解复用分析后都有唯一的index作为标识
        printf("index:%d\n", in_stream->index);
        // sample_rate: 音频编解码器的采样率，单位为Hz
        printf("samplerate:%dHz\n", in_stream->codecpar->sample_rate);
        // codecpar->format: 音频采样格式
        if (AV_SAMPLE_FMT_FLTP == in_stream->codecpar->format)
        {
            printf("sampleformat:AV_SAMPLE_FMT_FLTP\n");
        }
        else if (AV_SAMPLE_FMT_S16P == in_stream->codecpar->format)
        {
            printf("sampleformat:AV_SAMPLE_FMT_S16P\n");
        }
        // channels: 音频信道数目
        printf("channel number:%d\n", in_stream->codecpar->channels);
        // codec_id: 音频压缩编码格式
        if (AV_CODEC_ID_AAC == in_stream->codecpar->codec_id)
        {
            printf("audio codec:AAC\n");
        }
        else if (AV_CODEC_ID_MP3 == in_stream->codecpar->codec_id)
        {
            printf("audio codec:MP3\n");
        }
        else
        {
            printf("audio codec_id:%d\n", in_stream->codecpar->codec_id);
        }
        // 音频总时长，单位为秒。注意如果把单位放大为毫秒或者微妙，音频总时长跟视频总时长不一定相等的
        if(in_stream->duration != AV_NOPTS_VALUE)
        {
            int duration_audio = (in_stream->duration) * av_q2d(in_stream->time_base);
            //将音频总时长转换为时分秒的格式打印到控制台上
            printf("audio duration: %02d:%02d:%02d\n",
                   duration_audio / 3600, (duration_audio % 3600) / 60, (duration_audio % 60));
        }
        else
        {
            printf("audio duration unknown");
        }

        printf("\n");
        return codecParams;
    } else {
        printf("nAudioIndex == -1\n");
        return nullptr;
    }
}

AVCodecParameters *FxDemuxThread::getVideoCodecParameters()
{
    if (nVideoIndex != -1) {
        AVCodecParameters* codecParams = mFmtCtx->streams[nVideoIndex]->codecpar;
        AVStream *in_stream = mFmtCtx->streams[nVideoIndex];// 音频流、视频流、字幕流
        printf("\n");
        printf("----- Video info:\n");
        printf("index:%d\n", in_stream->index);
        // avg_frame_rate: 视频帧率,单位为fps，表示每秒出现多少帧
        printf("fps:%lffps\n", av_q2d(in_stream->avg_frame_rate));
        if (AV_CODEC_ID_MPEG4 == in_stream->codecpar->codec_id) //视频压缩编码格式
        {
            printf("video codec:MPEG4\n");
        }
        else if (AV_CODEC_ID_H264 == in_stream->codecpar->codec_id) //视频压缩编码格式
        {
            printf("video codec:H264\n");
        }
        else
        {
            printf("video codec_id:%d\n", in_stream->codecpar->codec_id);
        }
        // 视频帧宽度和帧高度
        printf("width:%d height:%d\n", in_stream->codecpar->width,
               in_stream->codecpar->height);
        //视频总时长，单位为秒。注意如果把单位放大为毫秒或者微妙，音频总时长跟视频总时长不一定相等的
        if(in_stream->duration != AV_NOPTS_VALUE)
        {
            int duration_video = (in_stream->duration) * av_q2d(in_stream->time_base);
            printf("video duration: %02d:%02d:%02d\n",
                   duration_video / 3600,
                   (duration_video % 3600) / 60,
                   (duration_video % 60)); //将视频总时长转换为时分秒的格式打印到控制台上
        }
        else
        {
            printf("video duration unknown");
        }

        printf("\n");
        return codecParams;
    } else {
        printf("nVideoIndex == -1\n");
        return nullptr;
    }
}

FxDemuxThread::~FxDemuxThread() {
    mCallback.reset();
    stop();
}
