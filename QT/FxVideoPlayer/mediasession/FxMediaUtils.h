#ifndef FXMEDIAUTILS_H
#define FXMEDIAUTILS_H
#include <string>
namespace fox
{
    namespace player
    {
        class FxPacketQueue;
        using FxPacketQueuePtr = std::shared_ptr<FxPacketQueue>;
        class FxFrameQueue;
        using FxFrameQueuePtr = std::shared_ptr<FxFrameQueue>;

    }// namespace player
}// namespace fox

#endif // FXMEDIAUTILS_H
