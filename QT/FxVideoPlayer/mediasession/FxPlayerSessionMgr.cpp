#include "FxPlayerSessionMgr.h"
#include <memory>
#include "FxPacketQueue.h"
#include "FxFrameQueue.h"

using namespace std;
using namespace fox::player;

FxPlayerSessionMgr::FxPlayerSessionMgr(IFxPlayerSessionMgrCallbackWeakPtr callback)
    : pCallback(callback) {
}

std::shared_ptr<IFxPlayerSessionMgr> IFxPlayerSessionMgr::createPlaySessionMgr(IFxPlayerSessionMgrCallbackWeakPtr callback)
{
    return std::make_shared<FxPlayerSessionMgr>(callback);
}

void FxPlayerSessionMgr::init(const char *url) {
    auto callback = std::dynamic_pointer_cast<IFxDemuxThreadCallback>(shared_from_this());

    pAudioPacketQueue = std::make_shared<FxPacketQueue>();
    pVideoPacketQueue = std::make_shared<FxPacketQueue>();


    pDemuxThread = std::make_unique<FxDemuxThread>(callback, pAudioPacketQueue, pVideoPacketQueue);
    int ret = pDemuxThread->open(url);
    if (ret < 0) {
        printf("mDemuxThread->open failed url:%s", url);
    }

    ret = pDemuxThread->start();
    if (ret < 0) {
        printf("mDemuxThread->start failed url:%s", url);
    }
    pAudioFrameQueue = std::make_shared<FxFrameQueue>();
    pVideoFrameQueue = std::make_shared<FxFrameQueue>();

    // pAudioDecodeThread = std::make_unique<FxDecodeThread>(pAudioPacketQueue, pAudioFrameQueue);
    // ret = pAudioDecodeThread->init(pDemuxThread->getAudioCodecParameters());
    // if (ret < 0) {
    //     printf("pAudioDecodeThread->init failed url:%s", url);
    // }
    // pAudioDecodeThread->start();

    pVideoDecodeThread = std::make_unique<FxDecodeThread>(pVideoPacketQueue, pVideoFrameQueue);
    ret = pVideoDecodeThread->init(pDemuxThread->getVideoCodecParameters());
    if (ret < 0) {
        printf("pVideoDecodeThread->init failed url:%s", url);
    }
    pVideoDecodeThread->start();

    pDemuxThread->stop();
    pAudioDecodeThread->stop();
    pVideoDecodeThread->stop();

    std::this_thread::sleep_for(std::chrono::seconds(2));
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
    pAudioDecodeThread.reset();
    pVideoDecodeThread.reset();
    pDemuxThread.reset();

    pAudioPacketQueue.reset();
    pVideoPacketQueue.reset();
    pAudioFrameQueue.reset();
    pVideoFrameQueue.reset();
}
