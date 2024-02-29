#ifndef FXDEMUXTHREAD_H
#define FXDEMUXTHREAD_H

#include <string>
#include <thread>
extern "C" {        // 用C规则编译指定的代码
// #include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
// #include "libavutil/avutil.h"/*
//#include "libswscale/swscale.h"
//#include "libavutil/imgutils.h"*/
}

namespace fox
{
    namespace player
    {
        class FxPacketQueue;
        using FxPacketQueuePtr = std::shared_ptr<FxPacketQueue>;
        class FxFrameQueue;
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

        private:
            std::string mUrl;
            std::weak_ptr<IFxDemuxThreadCallback> mCallback;

            char err2str[256]{ 0 };
            AVFormatContext *mFmtCtx = nullptr;

            int nAudioIndex{ -1 };
            int nVideoIndex{ -1 };

            std::atomic<bool> bAbort{ false };
            std::thread mThread;
            std::atomic<bool> bThreadRunning{ false };


            FxPacketQueuePtr pAudioQueue;
            FxPacketQueuePtr pVideoQueue;
        };

    }// namespace player
}// namespace fox

#endif // FXDEMUXTHREAD_H
