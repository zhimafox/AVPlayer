#ifndef IFXPLAYERSESSIONMGR_H
#define IFXPLAYERSESSIONMGR_H
#include <string>
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
        enum class MediaPlayState {
            STOPPED,
            PLAYING,
            PAUSED,
            SEEKING,
            DOWNLOADING,
            ERROR,
        };

        class IFxPlayerSessionMgrCallback {
            virtual void onPlayTimeChange(int progress, int playtime/*second*/) = 0;
            virtual void onPlayStateChange(const MediaPlayState state) = 0;
            virtual void onDeliverAudioFrames(FxFrameQueuePtr audioFrames) = 0;
            virtual void onDeliverVideoFrames(FxFrameQueuePtr videoFrames) = 0;
        };

        using IFxPlayerSessionMgrCallbackWeakPtr = std::weak_ptr<IFxPlayerSessionMgrCallback>;
        class IFxPlayerSessionMgr : public std::enable_shared_from_this<IFxPlayerSessionMgr>
        {
        public:
            virtual void init(const char *url) = 0;
            virtual void openMedia(const std::string& filePath) = 0;
            virtual void playMedia() = 0;
            virtual void pauseMedia() = 0;
            virtual void stopMedia() = 0 ;
            virtual void recoilMedia(int step = 15) = 0; //15s
            virtual void fastForwardMedia(int step = 15) = 0;//15s
            virtual void seekMedia(int progress) = 0;
            virtual void changeVolumn(int volumn) = 0;
            virtual void watchFrame(int progress) = 0;

            static std::shared_ptr<IFxPlayerSessionMgr> createPlaySessionMgr(IFxPlayerSessionMgrCallbackWeakPtr);
        };

        using IFxPlayerSessionMgrPtr = std::shared_ptr<IFxPlayerSessionMgr>;

    }// namespace player
}// namespace fox

#endif // IFXPLAYERSESSIONMGR_H
