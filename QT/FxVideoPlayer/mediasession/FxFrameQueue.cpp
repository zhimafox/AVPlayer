#include "FxFrameQueue.h"
using namespace fox::player;

FxFrameQueue::FxFrameQueue() {}

FxFrameQueue::~FxFrameQueue()
{

}

void FxFrameQueue::abort()
{
    mQueue.abort();
}

void FxFrameQueue::release()
{
    while(true) {
        AVFrame *frame = nullptr;
        int ret = mQueue.pop(frame, 1);
        if (ret > 0) {
            av_frame_free(&frame);
            continue;
        } else {
            break;
        }
    }
}

int FxFrameQueue::size()
{
    return mQueue.size();
}

int FxFrameQueue::push(AVFrame *frame)
{
    AVFrame *temp_frame = av_frame_alloc();
    av_frame_move_ref(temp_frame, frame);
    return mQueue.push(frame);
}

AVFrame *FxFrameQueue::pop(const int timeout)
{
    AVFrame *temp_frame = nullptr;
    int ret = mQueue.pop(temp_frame, timeout);
    if (ret < 0) {
        if (ret == -1) {
            printf("mQueue.pop failed");
        } else if (ret == -2) {
            printf("mQueue.pop failed, queue is empty");
        }
    }
    return temp_frame;
}

AVFrame *FxFrameQueue::front()
{
    AVFrame *temp_frame = nullptr;
    int ret = mQueue.front(temp_frame);
    if (ret < 0) {
        if (ret == -1) {
            printf("mQueue.pop failed");
        } else if (ret == -2) {
            printf("mQueue.pop failed, queue is empty");
        }
    }
    return temp_frame;
}
