#include "FxDemuxThread.h"

using namespace fox::player;

FxDemuxThread::FxDemuxThread(std::weak_ptr<IFxDemuxThreadCallback> callback)
    : mCallback(callback) {
}

int FxDemuxThread::open(const char *url) {

    printf("url:%s", url);
    return -1;
}

int FxDemuxThread::start() {

    return -1;
}

int FxDemuxThread::stop() {

    return -1;
}

int FxDemuxThread::run() {

    return -1;
}
