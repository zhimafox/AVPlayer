#ifndef FXDEMUXTHREAD_H
#define FXDEMUXTHREAD_H

#include <string>
#include <thread>
#include "FxMediaUtils.h"

extern "C" {        // 用C规则编译指定的代码
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
// #include "libavutil/avutil.h"/*
//#include "libswscale/swscale.h"
//#include "libavutil/imgutils.h"*/
}

namespace fox
{
    namespace player
    {
        class IFxDemuxThreadCallback {
        public:
            virtual void onPlayCompleted() {};
        };

        class FxDemuxThread
        {
        public:
            FxDemuxThread() = default;
            virtual ~FxDemuxThread();

        public:

            FxDemuxThread(std::weak_ptr<IFxDemuxThreadCallback> callback, FxPacketQueuePtr audioQueue, FxPacketQueuePtr videoQueue);
            int open(const char *url);
            int start();
            int stop();
            int run();
            AVFormatContext *getFormatContext() {
                return mFmtCtx;
            }

            AVCodecParameters *getAudioCodecParameters();
            AVCodecParameters *getVideoCodecParameters();

        private:
            std::string mUrl;
            std::weak_ptr<IFxDemuxThreadCallback> mCallback;

            char err2str[256]{ 0 };
            AVFormatContext *mFmtCtx;
            AVCodecContext*  m_codecContext  = nullptr;   // 解码器上下文

            int nAudioIndex{ -1 };
            int nVideoIndex{ -1 };
            int nTotalFrames{ 0 };
            int nTotalTime{ 0 }; //ms
            int mObtainFrames{ 0 };

            int nWidth{ 0 };
            int nHeight { 0 };

            std::atomic<bool> bAbort{ false };
            std::thread mThread;
            std::atomic<bool> bThreadRunning{ false };

            FxPacketQueuePtr pAudioQueue;
            FxPacketQueuePtr pVideoQueue;
        };

    }// namespace player
}// namespace fox

#endif // FXDEMUXTHREAD_H
