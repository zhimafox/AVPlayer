#include "FxPlayerSessionMgr.h"
#include <memory>

using namespace std;
using namespace fox::player;

FxPlayerSessionMgr::FxPlayerSessionMgr(IFxPlayerSessionMgrCallbackWeakPtr callback)
    : mCallback(callback) {
}

std::shared_ptr<IFxPlayerSessionMgr> IFxPlayerSessionMgr::createPlaySessionMgr(IFxPlayerSessionMgrCallbackWeakPtr callback)
{
    return std::make_shared<FxPlayerSessionMgr>(callback);
}

void FxPlayerSessionMgr::init(const char *url) {
    auto callback = std::dynamic_pointer_cast<IFxDemuxThreadCallback>(shared_from_this());
    mDemuxThread = std::make_unique<FxDemuxThread>(callback);
    mDemuxThread->open(url);
}

void FxPlayerSessionMgr::openMedia(const std::string& filePath) {
    printf("progress:%s", filePath.c_str());
}

void FxPlayerSessionMgr::playMedia() {

}

void FxPlayerSessionMgr::pauseMedia() {

}

void FxPlayerSessionMgr::stopMedia() {

}

void FxPlayerSessionMgr::recoilMedia(int step) {
    printf("progress:%d", step);
}

void FxPlayerSessionMgr::fastForwardMedia(int step) {
    printf("progress:%d", step);

}

void FxPlayerSessionMgr::seekMedia(int progress) {
    printf("progress:%d", progress);
}

void FxPlayerSessionMgr::changeVolumn(int volumn) {
    printf("progress:%d", volumn);

}

void FxPlayerSessionMgr::watchFrame(int progress) {

    printf("progress:%d", progress);
}

FxPlayerSessionMgr::~FxPlayerSessionMgr() {
    mDemuxThread = nullptr;
}
