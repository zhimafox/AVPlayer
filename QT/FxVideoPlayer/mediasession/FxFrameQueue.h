#ifndef FXFRAMEQUEUE_H
#define FXFRAMEQUEUE_H
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
        class FxFrameQueue
        {
        public:
            FxFrameQueue();
            virtual ~FxFrameQueue();

            void abort();
            void release();
            int size();
            int push(AVFrame *frame);
            AVFrame *pop(const int timeout=10);
            AVFrame *front();
            bool isEmpty();

        private:
            FxQueue<AVFrame *> mQueue;
        };

    }// namespace player
}// namespace fox

#endif // FXFRAMEQUEUE_H
