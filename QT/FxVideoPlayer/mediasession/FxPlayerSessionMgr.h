#ifndef FXPLAYERSESSIONMGR_H
#define FXPLAYERSESSIONMGR_H

#include <string>
#include "IFxPlayerSessionMgr.h"
#include "FxDemuxThread.h"

namespace fox
{
    namespace player
    {
        class FxPlayerSessionMgr : public IFxPlayerSessionMgr, public IFxDemuxThreadCallback
        {
        public:
            FxPlayerSessionMgr(IFxPlayerSessionMgrCallbackWeakPtr callback);
            ~FxPlayerSessionMgr() = default;

        public:
            virtual void init() override;
            virtual void openMedia(const std::string& filePath) override;
            virtual void playMedia() override;
            virtual void pauseMedia() override;
            virtual void stopMedia() override;
            virtual void recoilMedia(int step = 15) override; //15s
            virtual void fastForwardMedia(int step = 15) override;//15s
            virtual void seekMedia(int progress) override;
            virtual void changeVolumn(int volumn) override;
            virtual void watchFrame(int progress) override;
        private:
            std::unique_ptr<FxDemuxThread> mDemuxThread;
            IFxPlayerSessionMgrCallbackWeakPtr mCallback;
        };

    }// namespace player
}// namespace fox

#endif // FXPLAYERSESSIONMGR_H
