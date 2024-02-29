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
    av_dump_format(mFmtCtx, 0, mUrl.c_str(), 0);

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
            auto size = pAudioQueue->size();
            printf("audio pkt, size:%d\n", size);
        } else if (pkt.stream_index == nVideoIndex) {
            pVideoQueue->push(&pkt);
            auto size = pVideoQueue->size();
            printf("video pkt, size:%d\n",size);
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

FxDemuxThread::~FxDemuxThread() {
    mCallback.reset();
    stop();
}
