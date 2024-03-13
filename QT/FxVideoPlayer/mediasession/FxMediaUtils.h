#ifndef FXMEDIAUTILS_H
#define FXMEDIAUTILS_H
#include <string>
#include "FxQueue.h"

namespace fox
{
    namespace player
    {
        enum class FxFrameFormat {
            Format_Invalid,
            Format_Mono,
            Format_MonoLSB,
            Format_Indexed8,
            Format_RGB32,
            Format_ARGB32,
            Format_ARGB32_Premultiplied,
            Format_RGB16,
            Format_ARGB8565_Premultiplied,
            Format_RGB666,
            Format_ARGB6666_Premultiplied,
            Format_RGB555,
            Format_ARGB8555_Premultiplied,
            Format_RGB888,
            Format_RGB444,
            Format_ARGB4444_Premultiplied,
            Format_RGBX8888,
            Format_RGBA8888,
            Format_RGBA8888_Premultiplied,
            Format_BGR30,
            Format_A2BGR30_Premultiplied,
            Format_RGB30,
            Format_A2RGB30_Premultiplied,
            Format_Alpha8,
            Format_Grayscale8,
            Format_RGBX64,
            Format_RGBA64,
            Format_RGBA64_Premultiplied,
            Format_Grayscale16,
            Format_BGR888,
            Format_RGBX16FPx4,
            Format_RGBA16FPx4,
            Format_RGBA16FPx4_Premultiplied,
            Format_RGBX32FPx4,
            Format_RGBA32FPx4,
            Format_RGBA32FPx4_Premultiplied,
        };

        struct FxFrameData {
            int buffer;
            int width;
            int height;
            FxFrameFormat format;
        };

        class FxPacketQueue;
        using FxPacketQueuePtr = std::shared_ptr<FxPacketQueue>;

        class FxFrameQueue;
        using FxFrameQueuePtr = std::shared_ptr<FxFrameQueue>;

        using FxFrameDataPtr = std::shared_ptr<FxFrameData>;
        using FxFrameDataQueue = FxQueue<FxFrameDataPtr>;

        using FxFrameDataQueuePtr = std::shared_ptr<FxFrameDataQueue>;

    }// namespace player
}// namespace fox

#endif // FXMEDIAUTILS_H
