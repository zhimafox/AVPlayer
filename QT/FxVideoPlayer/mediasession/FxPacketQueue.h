#ifndef FXPACKETQUEUE_H
#define FXPACKETQUEUE_H
#include "FxQueue.h"
extern "C" {        // 用C规则编译指定的代码
// #include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
//#include "libswscale/swscale.h"
//#include "libavutil/imgutils.h"*/
}
using namespace fox::player;

namespace fox
{
    namespace player
    {
        class FxPacketQueue
        {
        public:
            FxPacketQueue();
            virtual ~FxPacketQueue();

            void abort();
            void release();
            int size();
            int push(AVPacket *pkt);
            AVPacket *pop(const int timeout);
            AVPacket *front();
        private:
            FxQueue<AVPacket *> mQueue;
        };
    }// namespace player
}// namespace fox
#endif // FXPACKETQUEUE_H
