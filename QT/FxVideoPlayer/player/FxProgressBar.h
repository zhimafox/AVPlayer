#ifndef FXPROGRESSBAR_H
#define FXPROGRESSBAR_H

#include <QWidget>
#include <QProgressBar>
#include <QEnterEvent>
#include <QEvent>

class FxProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit FxProgressBar(QWidget *parent = nullptr);
    void setPlayProgress(int value);
    void setDownloadProgress(int value);

private:
    bool event(QEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

    int getProgressRatio(QMouseEvent *event);

signals:
    void shouldShowThumbnail();
    void shouldHideThumbnail();
    //鼠标seek,需要从这个点开始播放: ratio *totalTime
    void shouldSeekProgress(int ratio);
    //鼠标mouse over,需要显示thumbnail: ratio *totalTime
    void shouldWatchProgress(int ratio);
    void shouldUpdateThumbnailPosition(QPointF point);

private:
        QProgressBar *mPlayProgress;
        QProgressBar *mDownloadProgress;
        int nCurrentPlayValue{ 0 };

signals:
};

#endif // FXPROGRESSBAR_H
