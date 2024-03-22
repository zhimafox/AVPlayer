#ifndef FXMEDIAUTILS_H
#define FXMEDIAUTILS_H
#include <string>
#include "FxQueue.h"

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

        class FxPacketQueue;
        using FxPacketQueuePtr = std::shared_ptr<FxPacketQueue>;

        class FxFrameQueue;
        using FxFrameQueuePtr = std::shared_ptr<FxFrameQueue>;

    }// namespace player
}// namespace fox

#endif // FXMEDIAUTILS_H
