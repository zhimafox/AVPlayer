#include "FxPacketQueue.h"

namespace fox
{
    namespace player
    {
FxPacketQueue::FxPacketQueue() {
}

FxPacketQueue::~FxPacketQueue()
{

}

        void FxPacketQueue::abort()
        {

        }

        void FxPacketQueue::release()
        {
            while(true) {
                AVPacket *pkt = nullptr;
                int ret = mQueue.pop(pkt, 1);
                if (ret > 0) {
                    av_packet_free(&pkt);
                    continue;
                } else {
                    break;
                }
            }
        }

        int FxPacketQueue::size()
        {
            return mQueue.size();
        }

        int FxPacketQueue::push(AVPacket *pkt)
        {
            AVPacket *temp_pkt = av_packet_alloc();
            av_packet_move_ref(temp_pkt, pkt);
            return mQueue.push(temp_pkt);
        }

        AVPacket *FxPacketQueue::pop(const int timeout)
        {
            AVPacket *temp_pkt = nullptr;
            int ret = mQueue.pop(temp_pkt, timeout);
            if (ret < 0) {
                if (ret == -1) {
                    printf("%s, mQueue.pop failed", __FUNCTION__);
                } else if (ret == -2) {
                    printf("%s, mQueue.pop failed, queue is empty", __FUNCTION__);
                }
            }
            return temp_pkt;
        }

        AVPacket *FxPacketQueue::front()
        {
            AVPacket *temp_pkt = nullptr;
            int ret = mQueue.pop(temp_pkt);
            if (ret < 0) {
                if (ret == -1) {
                    printf("%s, mQueue.pop failed", __FUNCTION__);
                } else if (ret == -2) {
                    printf("%s, mQueue.pop failed, queue is empty", __FUNCTION__);
                }
            }
            return temp_pkt;
        }
    }// namespace player
}// namespace fox
