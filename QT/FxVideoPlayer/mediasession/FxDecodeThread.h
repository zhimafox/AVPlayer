#ifndef FXDECODETHREAD_H
#define FXDECODETHREAD_H
#include <string>
#include <thread>
#include "FxMediaUtils.h"

extern "C" {        // 用C规则编译指定的代码
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
//#include "libswscale/swscale.h"
//#include "libavutil/imgutils.h"*/
}

namespace fox
{
    namespace player
    {
        class FxDecodeThread
        {
        public:
            FxDecodeThread(FxPacketQueuePtr packetQueuePtr, FxFrameQueuePtr frameQueuePtr);
            virtual ~FxDecodeThread();

            int init(AVCodecParameters *par);
            int start();
            int stop();
            void run();
        private:
            char err2str[256]{ 0 };

            std::atomic<bool> bAbort{ false };
            std::thread mThread;
            std::atomic<bool> bThreadRunning{ false };

            AVCodecContext *pCodecCtx;
            FxPacketQueuePtr pPacketQueuePtr;
            FxFrameQueuePtr pFrameQueuePtr;
        };

    }// namespace player
}// namespace fox

#endif // FXDECODETHREAD_H
