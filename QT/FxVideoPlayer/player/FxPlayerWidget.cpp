#include "FxPlayerWidget.h"
#include <QtWidgets>
#include <QObject>
#include <QEvent>
#include <QDebug>
#include "mediasession/FxFrameQueue.h"

#include "mediasession/FxFrameQueue.h"
extern "C" {        // 用C规则编译指定的代码
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
//#include "libswscale/swscale.h"
//#include "libavutil/imgutils.h"*/
}

FxPlayerWidget::FxPlayerWidget(QWidget *parent)
    : QWidget(parent)
{
    initSubviews();
}

void FxPlayerWidget::initSubviews() {

    initWindowsStyle();
    QBoxLayout *rootLayout = createRootLayout();
    createVideoWidget(rootLayout);
    QBoxLayout *ctrlBarLayout = createCtrlBarLayout(rootLayout);

    createProgressBar(ctrlBarLayout);
    createButtonsBar(ctrlBarLayout);

    createThumbnailWidget();
}

void FxPlayerWidget::initSessionMgr(const char *url) {
    auto callback = std::dynamic_pointer_cast<IFxPlayerSessionMgrCallback>(shared_from_this());
    pPlayerSessionMgr = IFxPlayerSessionMgr::createPlaySessionMgr(callback);
    pPlayerSessionMgr->init(url);
}
void FxPlayerWidget::initWindowsStyle() {
    // 设置窗口标题
    updateWindowTitle("Fox AV Player");
    // 设置主窗口的初始大小为800x600像素
    this->resize(800, 600);
    this->setStyleSheet("background-color: #2A282B;");


}

QBoxLayout* FxPlayerWidget::createRootLayout() {
    mVideoImageWidget = new FxVideoWidget();
    QVBoxLayout *rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(10, 0, 10, 0);
    mVideoImageWidget->setStyleSheet("background-color: #066781;");

    return rootLayout;
}

void FxPlayerWidget::createVideoWidget(QBoxLayout *parent) {
    parent->addWidget(mVideoImageWidget);
}

void FxPlayerWidget::createThumbnailWidget()
{
    // 创建一个浮动的小部件
    mThumbnailWidget = new QWidget();
    // 设置浮动小部件的样式，使其没有边框
    mThumbnailWidget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    // 设置浮动小部件的位置
    mThumbnailWidget->resize(200, 120);
    mThumbnailWidget->setStyleSheet("background-color:white;"); // 设置背景颜色为红色
    // 将浮动小部件添加到当前 QWidget 上
    mThumbnailWidget->setParent(this); // parentWidget 是当前 QWidget 的指针
    mThumbnailWidget->move(0, 10000);
}

QBoxLayout* FxPlayerWidget::createCtrlBarLayout(QBoxLayout *parent)
{
    return createLayoutFrame(parent, 60, "", false);
}

void FxPlayerWidget::createProgressBar(QBoxLayout *parent) {
    QBoxLayout *processBarLayout = createLayoutFrame(parent, 12, "#2A282B");

    // 创建 QLabel 和 QProgressBar
    mCurrentTime = new QLabel("00:00:00");
    mProgressBar = new FxProgressBar();

    // 连接 CustomProgressBar 的信号
    connect(mProgressBar, &FxProgressBar::shouldShowThumbnail, this, &FxPlayerWidget::handleShowThumbnail);
    connect(mProgressBar, &FxProgressBar::shouldHideThumbnail, this, &FxPlayerWidget::handleHideThumbnail);
    connect(mProgressBar, &FxProgressBar::shouldSeekProgress, this, &FxPlayerWidget::handleSeekProgress);
    connect(mProgressBar, &FxProgressBar::shouldWatchProgress, this, &FxPlayerWidget::handleWatchProgress);
    connect(mProgressBar, &FxProgressBar::shouldUpdateThumbnailPosition, this, &FxPlayerWidget::handleUpdateThumbnailPosition);

    mTotalTime = new QLabel("00:00:00");

    // 设置 QLabel 的样式
    mCurrentTime->setFixedWidth(60);
    mCurrentTime->setFixedHeight(10);
    mCurrentTime->setAlignment(Qt::AlignCenter);
    mCurrentTime->setStyleSheet("color: white;");

    mTotalTime->setFixedWidth(60);
    mTotalTime->setFixedHeight(10);
    mTotalTime->setAlignment(Qt::AlignCenter);
    mTotalTime->setStyleSheet("color: white;");

    mTotalTime = new QLabel("00:00:00");
    mTotalTime->setFixedWidth(60);
    mTotalTime->setFixedHeight(10);
    mTotalTime->setAlignment(Qt::AlignCenter);
    mTotalTime->setStyleSheet("color: white;");

    // 设置 QProgressBar 的样式
    mProgressBar->setFixedHeight(5);

    // 设置 QProgressBar 的范围和当前值
    mProgressBar->setPlayProgress(10);
    mProgressBar->setDownloadProgress(60);

    processBarLayout->addWidget(mCurrentTime);
    processBarLayout->addWidget(mProgressBar);
    processBarLayout->addWidget(mTotalTime);

    processBarLayout->setStretchFactor(mProgressBar, 1);
    processBarLayout->setAlignment(Qt::AlignVCenter);
}

void FxPlayerWidget::createButtonsBar(QBoxLayout *parent) {
    QBoxLayout *buttonsBarLayout = createLayoutFrame(parent, 45, "#2A282B");
    QHBoxLayout *leftButtonsBarLayout = new QHBoxLayout();


    QHBoxLayout *centerVolumnLayout = new QHBoxLayout();
    leftButtonsBarLayout->addLayout(centerVolumnLayout);
    leftButtonsBarLayout->setStretchFactor(centerVolumnLayout, 1);

    mVolumnButton = createButton("icon_volumn", 20, 20);


    mVolumnSlider = new QSlider(Qt::Horizontal);
    mVolumnSlider->setFixedWidth(100); // 设置宽度为 200 像素
    QSize handleSize(10, 10); // 设置拖动的圆点大小为 10x10 像素
    mVolumnSlider->setStyleSheet("QSlider::handle {"
                                 "    width: " + QString::number(handleSize.width()) + "px;"
                                                                         "    height: " + QString::number(handleSize.height()) + "px;"
                                                                          "}");

    centerVolumnLayout->addWidget(mVolumnButton);
    centerVolumnLayout->addWidget(mVolumnSlider);
    buttonsBarLayout->addLayout(leftButtonsBarLayout);

    QHBoxLayout *centerButtonsBarLayout = new QHBoxLayout();
    buttonsBarLayout->addLayout(centerButtonsBarLayout);
    buttonsBarLayout->setStretchFactor(centerButtonsBarLayout, 1);

    QWidget *leftSpacer = new QWidget();
    leftSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QWidget *rightSpacer = new QWidget();
    rightSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    mPlayButton = createButton("icon_play", 35, 35);
    mRecoilButton = createButton("icon_recoil");
    mFastForwardButton = createButton("icon_fastforward");
    mStopButton = createButton("icon_stop", 25, 25);
    mSettingsButton = createButton("icon_settings", 22, 22);

    centerButtonsBarLayout->addWidget(leftSpacer);
    centerButtonsBarLayout->addWidget(mStopButton);

    centerButtonsBarLayout->addWidget(mRecoilButton);
    centerButtonsBarLayout->addWidget(mPlayButton);
    centerButtonsBarLayout->addWidget(mFastForwardButton);
    centerButtonsBarLayout->addWidget(mSettingsButton);
    centerButtonsBarLayout->addWidget(rightSpacer);

    QHBoxLayout *rightButtonsBarLayout = new QHBoxLayout();
    buttonsBarLayout->addLayout(rightButtonsBarLayout);
    mFullScreenButton = createButton("icon_fullscreen");
    rightButtonsBarLayout->addWidget(mFullScreenButton);
}

void FxPlayerWidget::updateDurationLabel() {

}

void FxPlayerWidget::updateWindowTitle(QString title){
    // 设置窗口标题
    setWindowTitle(title);
}

QBoxLayout* FxPlayerWidget::createLayoutFrame(QBoxLayout *parent, int height, QString colorString, bool isHorizontal) {
    QFrame *frame = new QFrame();
    frame->setFixedHeight(height);
    parent->addWidget(frame);
    if (!colorString.isEmpty()) {
        frame->setStyleSheet("QFrame {background-color:" + colorString + ";}"); // 设置背景颜色为红色
    }

    QBoxLayout *layout = nullptr;
    if (isHorizontal) {
        layout = new QHBoxLayout();
    } else {
        layout = new QVBoxLayout();
    }
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    frame->setLayout(layout);

    return layout;
}

QPushButton* FxPlayerWidget::createButton(QString iconName,  int width, int height) {
    QString normalIconPath = ":/resources/" + iconName + ".png";
    QString pressedIconPath = ":/resources/" + iconName + "_press.png";

    QPushButton *button = new QPushButton();

    // 获取标准图标并设置为按钮的图标
    QPixmap normalPixmap(normalIconPath);
    QPixmap pressedPixmap(pressedIconPath);

    button->setIcon(QIcon(normalPixmap));
    button->setIconSize(QSize(width, height));

    // 设置按钮透明
    button->setFlat(true);

    // 设置按钮样式表
    button->setStyleSheet(
        "QPushButton {"
        "    border: 0px;"
        "}"
        );

    // 保存按下图标路径，以便在按钮按下时更改图标
    button->setProperty("pressedIconPath", pressedIconPath);

    // 监听按钮的 pressed 信号，并在按钮按下时更改图标
    connect(button, &QPushButton::pressed, [=]() {
        QPixmap pressedPixmap(pressedIconPath);
        button->setIcon(QIcon(pressedPixmap));
    });

    // 监听按钮的 released 信号，并在按钮释放时恢复原始图标
    connect(button, &QPushButton::released, [=]() {
        QPixmap normalPixmap(normalIconPath);
        button->setIcon(QIcon(normalPixmap));
    });

    return button;
}

void FxPlayerWidget::initPlayer() {
    // connect(m_readThread, &ReadThread::updateImage, ui->playImage, &PlayImage::updateImage, Qt::DirectConnection);
    // connect(m_readThread, &ReadThread::playState, this, &Widget::on_playState);
}
//鼠标seek,需要从这个点开始播放: ratio *totalTime
void FxPlayerWidget::handleSeekProgress(int ratio){
    // qDebug() << "handleSeekProgress" << ratio;
    mProgressBar->setPlayProgress(ratio);

}

//鼠标mouse over,需要显示thumbnail: ratio *totalTime
void FxPlayerWidget::handleWatchProgress(int ratio) {
    // qDebug() << "handleWatchProgress" << ratio;
    mProgressBar->setPlayProgress(ratio);

}

void FxPlayerWidget::handleShowThumbnail(){
    mThumbnailWidget->show();
}

void FxPlayerWidget::handleHideThumbnail(){
    mThumbnailWidget->hide();
}

void FxPlayerWidget::handleUpdateThumbnailPosition(QPointF point){
    // QPointF globalPos = mapToGlobal(point);
    double y = this->size().height() - 60 - mThumbnailWidget->height() - 10;
    mThumbnailWidget->move(point.x(), y);
}

//#IFxPlayerSessionMgrCallback implement start
void FxPlayerWidget::onPlayTimeChange(int progress, int playtime/*second*/) {
    qDebug() << "progress:" << progress << "playtime:" << playtime;
}

void FxPlayerWidget::onPlayStateChange(const MediaPlayState state) {
    qDebug() << "state:" << static_cast<int>(state);
}

void FxPlayerWidget::onDeliverAudioFrames(FxFrameQueuePtr audioFrameQueue) {
    qDebug() << "audioFrames.size:" << audioFrameQueue->size();
    pAudioFrameQueue = audioFrameQueue;

    // while(audioFrameDataQueue->size() > 0) {
    //     if (auto frameData = audioFrameDataQueue->popDirectly()) {
    //         qDebug() << "frameData->width:" << frameData->width;
    //     }
    // }
}

void FxPlayerWidget::onDeliverVideoFrames(FxFrameQueuePtr videoFrameQueue) {
    pVideoFrameQueue = videoFrameQueue;
    // qDebug() << " videoFrames.size:" << videoFrameQueue->size();

    // while(videoFrameDataQueue->size() > 0) {
    //     if (auto frameData = videoFrameDataQueue->popDirectly()) {
    //         qDebug() << "frameData->width:" << frameData->width;
    //     }
    // }
}
//
// connect(&m_timer, &QTimer::timeout, this, &VideoPlayer::showNextFrame);

void FxPlayerWidget::showNextAudioFrame() {
    // Check if there's a frame available in the queue
    if (!pAudioFrameQueue->isEmpty()) {
        AVFrame *frame = pAudioFrameQueue->pop();
        // Convert AVFrame to QImage (assuming RGB format)
        QImage image(frame->data[0], frame->width, frame->height, QImage::Format_RGB888);
        // Display the image on QLabel
        // m_videoLabel->setPixmap(QPixmap::fromImage(image));
        // Release the frame
        av_frame_unref(frame);
    }
}

void FxPlayerWidget::showNextVideoFrame() {
    // Check if there's a frame available in the queue
    if (!pVideoFrameQueue->isEmpty()) {
        AVFrame *frame = pVideoFrameQueue->pop();
        // Convert AVFrame to QImage (assuming RGB format)
        QImage image(frame->data[0], frame->width, frame->height, QImage::Format_RGB888);
        // Display the image on QLabel
        // m_videoLabel->setPixmap(QPixmap::fromImage(image));
        // Release the frame
        av_frame_unref(frame);
    }
}



void FxPlayerWidget::start() {
    mTimer->start(33); // 30 frames per second
}

void FxPlayerWidget::pause() {
    mTimer->stop();
}

void FxPlayerWidget::stop() {
    mTimer->stop();
    // 清空帧队列
    // while (!pVideoFrameQueue->isEmpty()) {
    //     auto frame = pVideoFrameQueue->pop(10);
    //     av_frame_free(frame);
    // }
}

void FxPlayerWidget::seek(int positionMs) {
    // 执行跳转操作
    // 例如：av_seek_frame(...)
}
//#IFxPlayerSessionMgrCallback implement end

FxPlayerWidget::~FxPlayerWidget() {}
