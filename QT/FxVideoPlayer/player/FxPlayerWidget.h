#ifndef FXPLAYERWIDGET_H
#define FXPLAYERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QSlider>
#include <QBoxLayout>
#include <QObject>
#include "FxProgressBar.h"
#include "QtCore/qtimer.h"
#include "mediasession/IFxPlayerSessionMgr.h"
#include "mediasession/FxMediaUtils.h"
#include "FxVideoWidget.h""
using namespace fox::player;

class FxPlayerWidget : public QWidget, public IFxPlayerSessionMgrCallback, public std::enable_shared_from_this<FxPlayerWidget>
{
    Q_OBJECT

public:
    FxPlayerWidget(QWidget *parent = nullptr);
    ~FxPlayerWidget();

public: //IFxPlayerSessionMgrCallback
    void initSessionMgr(const char *url);

    virtual void onPlayTimeChange(int progress, int playtime/*second*/) override;
    virtual void onPlayStateChange(const MediaPlayState state) override;

    virtual void onDeliverAudioFrames(FxFrameQueuePtr audioFrameQueue) override;
    virtual void onDeliverVideoFrames(FxFrameQueuePtr videoFrameQueue) override;

private:
    void initSubviews();

    void initWindowsStyle();
    QBoxLayout* createRootLayout();
    QBoxLayout* createCtrlBarLayout(QBoxLayout *parent);

    void createVideoWidget(QBoxLayout *parent);
    void createThumbnailWidget();
    void createCtrlBar(QBoxLayout *parent);
    void createProgressBar(QBoxLayout *parent);
    void createButtonsBar(QBoxLayout *parent);

    QBoxLayout* createLayoutFrame(QBoxLayout *parent, int height, QString colorString, bool isHorizontal = true);
    QPushButton *createButton(QString iconName, int width = 30, int height = 30);

    void initPlayer();
    void handleSeekProgress(int ratio);
    void handleWatchProgress(int ratio);
    void handleShowThumbnail();
    void handleHideThumbnail();
    void handleUpdateThumbnailPosition(QPointF point);

    void showNextAudioFrame();
    void showNextVideoFrame();

public slots:
    void updateDurationLabel();
    void updateWindowTitle(QString title);
    void start();
    void pause();
    void stop();
    void seek(int positionMs);


signals:
    void updateImage(const QImage& image);      // 将读取到的视频图像发送出去
    void playState(MediaPlayState state);       // 视频播放状态发送改变时触发

private:
    FxVideoWidget *mVideoImageWidget;
    FxProgressBar *mProgressBar;
    QWidget *mThumbnailWidget;

    QPushButton *mPlayButton;
    QPushButton *mStopButton;

    QPushButton *mRecoilButton;
    QPushButton *mFastForwardButton;

    QPushButton *mFullScreenButton;
    QPushButton *mSettingsButton;
    QPushButton *mVolumnButton;
    QSlider *mVolumnSlider;

    QLabel *mCurrentTime;
    QLabel *mTotalTime;

    QTimer *mTimer;
    int mMediaDuration = 0;

    std::shared_ptr<fox::player::IFxPlayerSessionMgr> pPlayerSessionMgr;
    FxFrameQueuePtr pAudioFrameQueue;
    FxFrameQueuePtr pVideoFrameQueue;

    QLabel *mVideoLabel;
};
#endif // FXPLAYERWIDGET_H
