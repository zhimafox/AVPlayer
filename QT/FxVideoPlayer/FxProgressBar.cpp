#include "FxProgressBar.h"
#include <QVBoxLayout>

FxProgressBar::FxProgressBar(QWidget *parent)
    : QWidget{parent}
{
    // 创建播放进度条
    mPlayProgress = new QProgressBar(this);
    mPlayProgress->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mPlayProgress->setTextVisible(false); // 不显示文本
    mPlayProgress->setRange(0, 100);
    mPlayProgress->setFixedHeight(5);
    mPlayProgress->setStyleSheet("QProgressBar {"
                                 "background-color: lightgrey;"//transparent
                                 "border: 1px solid grey;"
                                 "border-radius: 5px;"
                                 "}"
                                 "QProgressBar::chunk {"
                                 "background-color: #4673CB;" // 播放进度条颜色
                                 "}");

    // 创建下载进度条
    mDownloadProgress = new QProgressBar(this);
    mDownloadProgress->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mDownloadProgress->setTextVisible(false); // 不显示文本
    mDownloadProgress->setRange(0, 100);
    mDownloadProgress->setFixedHeight(5);
    mDownloadProgress->setStyleSheet("QProgressBar {"
                                     "background-color: lightgrey;"
                                     "border: 1px solid grey;"
                                     "border-radius: 5px;"
                                     "}"
                                     "QProgressBar::chunk {"
                                     "background-color: #FF6347;" // 下载进度条颜色
                                     "}");

    // 垂直布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mPlayProgress);
    layout->addWidget(mDownloadProgress);
    layout->setContentsMargins(0, 0, 0, 0);

    // 安装事件过滤器
    this->setAttribute( Qt::WA_Hover,true);
}

// 设置播放进度
void FxProgressBar::setPlayProgress(int value) {
    nCurrentPlayValue = value;

    // qDebug() << __FUNCTION__ << nCurrentPlayValue;
    mPlayProgress->setValue(nCurrentPlayValue);
}

// 设置下载进度
void FxProgressBar::setDownloadProgress(int value) {
    mDownloadProgress->setValue(value);
}

int FxProgressBar::getProgressRatio(QMouseEvent *event) {
    double x = event->position().x();
    int width = this->width();
    int ratio = int ((static_cast<double>(x) / width) * 100);
    return qMin(ratio, 100);
}

// // 重写事件过滤器函数
bool FxProgressBar::event(QEvent *event)
{
    if (event->type() == QEvent::HoverEnter || event->type() == QEvent::HoverLeave
        || event->type() == QEvent::HoverMove)
    {
        QHoverEvent* pHoverEvent = static_cast<QHoverEvent *>(event);

        emit shouldUpdateThumbnailPosition(pHoverEvent->position());
    }
    return QWidget::event(event);
}

void FxProgressBar::mouseReleaseEvent(QMouseEvent *event) {
    // 获取鼠标当前位置
    int ratio = getProgressRatio(event);
    emit shouldSeekProgress(ratio);
}

void FxProgressBar::mouseMoveEvent(QMouseEvent *event) {
    // 获取鼠标当前位置
    int ratio = getProgressRatio(event);
    emit shouldWatchProgress(ratio);
}

void FxProgressBar::enterEvent(QEnterEvent *event) {
    // 当鼠标进入小部件时，获取鼠标位置
    emit shouldShowThumbnail();
}

void FxProgressBar::leaveEvent(QEvent *event) {
    // 鼠标离开事件的处理代码
    emit shouldHideThumbnail();
}
