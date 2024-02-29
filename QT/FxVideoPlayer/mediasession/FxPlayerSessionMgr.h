#ifndef FXPLAYERSESSIONMGR_H
#define FXPLAYERSESSIONMGR_H

#include <string>
#include "IFxPlayerSessionMgr.h"
#include "FxDemuxThread.h"

namespace fox
{
    namespace player
    {
        class FxPacketQueue;
        using FxPacketQueuePtr = std::shared_ptr<FxPacketQueue>;
        class FxPlayerSessionMgr : public IFxPlayerSessionMgr, public IFxDemuxThreadCallback
        {
        public:
            FxPlayerSessionMgr(IFxPlayerSessionMgrCallbackWeakPtr callback);
            virtual ~FxPlayerSessionMgr();

        public:
            virtual void init(const char *url) override;
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

            FxPacketQueuePtr pAudioQueue;
            FxPacketQueuePtr pVideoQueue;
        };

    }// namespace player
}// namespace fox

#endif // FXPLAYERSESSIONMGR_H
