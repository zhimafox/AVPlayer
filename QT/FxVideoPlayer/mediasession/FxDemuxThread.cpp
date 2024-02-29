#include "FxDemuxThread.h"

using namespace fox::player;

FxDemuxThread::FxDemuxThread(std::weak_ptr<IFxDemuxThreadCallback> callback)
    : mCallback(callback) {
}

int FxDemuxThread::open(const char *url) {
    if (url == NULL) {

        printf("%s mUrl is empty", __FUNCTION__);
        // return -1;
        mUrl = ":/resource/test.mp4";
    } else {
        mUrl = url;
    }
    printf("%s mUrl:%s", __FUNCTION__,  mUrl.c_str());
    int ret = avformat_open_input(&mFmtCtx, mUrl.c_str(), NULL, NULL);
    if (ret < 0) {
        av_strerror(ret, err2str, sizeof(err2str));
        printf("%s url:%s open failed, ret:%d, err2str:%s\n", __FUNCTION__, url, ret, err2str);
        return -1;
    }

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

FxDemuxThread::~FxDemuxThread() {
    mCallback.reset();
}
