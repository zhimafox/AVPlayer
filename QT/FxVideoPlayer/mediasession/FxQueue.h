#ifndef FXQUEUE_H
#define FXQUEUE_H
#include <mutex>
#include <queue>
#include <chrono>
#include <condition_variable>

namespace fox
{
    namespace player
    {
template<typename T>
        class FxQueue {
            public:
                FxQueue() {};
                ~FxQueue() {};

                void abort() {
                    bAbort = true;
                    mCond.notify_all();
                }

                int size() {
                    std::lock_guard<std::mutex> lock(mMutex);
                    return mQueue.size();
                }

                int push(T obj) {
                    std::lock_guard<std::mutex> lock(mMutex);
                    if (bAbort) {
                        return -1;
                    }
                    mQueue.push(obj);
                    mCond.notify_one();
                    return 0;
                }

                int pop(T &obj, const int timeout = 0) {
                    std::unique_lock<std::mutex> unique(mMutex);
                    if (mQueue.empty()) {
                        // mCond.wait_for(lock, std::chrono::seconds(timeout), [this] {
                        //      return !mQueue.empty() | bAbort;
                        // });
                        mCond.wait(unique);
                    }
                    // if (mQueue.empty()) {
                    //     mCond.wait_for(lock, std::chrono::seconds(timeout), [this] {
                    //         return !mQueue.empty() | bAbort;
                    //     });
                    // }
                    if (bAbort) {
                        return -1;
                    }

                    if (mQueue.empty()) {
                        return -2;
                    }

                    obj = mQueue.front();
                    mQueue.pop();

                    return 0;
                }

                T popDirectly() {
                    std::unique_lock<std::mutex> unique(mMutex);
                    if (mQueue.empty()) {
                        return nullptr;
                    }

                    if (bAbort) {
                        return nullptr;
                    }

                    auto obj = mQueue.front();
                    mQueue.pop();

                    return obj;
                }

                int front(T &obj) {
                    std::lock_guard<std::mutex> lock(mMutex);
                    if (bAbort) {
                        return -1;
                    }

                    if (mQueue.empty()) {
                        return -2;
                    }

                    obj = mQueue.front();

                    return 0;
                }

                bool isEmpty() {
                    std::lock_guard<std::mutex> lock(mMutex);
                    return mQueue.empty();
                }

            private:
                std::atomic<bool> bAbort{ false };
                std::mutex mMutex;
                std::condition_variable mCond;
                std::queue<T> mQueue;
        };
    }// namespace player
}// namespace fox
#endif // FXQUEUE_H
