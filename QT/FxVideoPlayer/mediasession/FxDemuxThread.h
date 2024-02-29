#ifndef FXDEMUXTHREAD_H
#define FXDEMUXTHREAD_H

#include <string>
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
            ~FxDemuxThread() = default;

        public:

            FxDemuxThread(std::weak_ptr<IFxDemuxThreadCallback> callback);
            int open(const char *url);
            int start();
            int stop();
            int run();

        private:
            std::string mUrl;
            std::weak_ptr<IFxDemuxThreadCallback> mCallback;
        };

    }// namespace player
}// namespace fox

#endif // FXDEMUXTHREAD_H
