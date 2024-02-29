#ifndef FXDEMUXTHREAD_H
#define FXDEMUXTHREAD_H

#include <string>
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
        class IFxDemuxThreadCallback {
        public:
            virtual void onPlayCompleted() {};
        };

        class FxDemuxThread
        {
        public:
            FxDemuxThread() = default;
            ~FxDemuxThread();

        public:

            FxDemuxThread(std::weak_ptr<IFxDemuxThreadCallback> callback);
            int open(const char *url);
            int start();
            int stop();
            int run();

        private:
            std::string mUrl;
            std::weak_ptr<IFxDemuxThreadCallback> mCallback;

            char err2str[256]{ 0 };
            AVFormatContext *mFmtCtx = nullptr;
        };

    }// namespace player
}// namespace fox

#endif // FXDEMUXTHREAD_H
