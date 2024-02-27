#ifndef FVPLAYERWIDGET_H
#define FVPLAYERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QSlider>
#include <QBoxLayout>
#include <QObject>
#include "FxProgressBar.h"
class FvPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    FvPlayerWidget(QWidget *parent = nullptr);
    ~FvPlayerWidget();
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

    void handleSeekProgress(int ratio);
    void handleWatchProgress(int ratio);
    void handleShowThumbnail();
    void handleHideThumbnail();
    void handleUpdateThumbnailPosition(QPointF point);

private slots:
    void updateDurationLabel();
    void updateWindowTitle(QString title);

private:
    QWidget *mVideoImageWidget;
    FxProgressBar *mProgressBar;
    QWidget *mThumbnailWidget;

    QPushButton *mPlayButton;
    QPushButton *mStopButton;
    QPushButton *mPreviousButton;
    QPushButton *mNextButton;
    QPushButton *mFullScreenButton;
    QPushButton *mSettingsButton;
    QPushButton *mVolumnButton;
    QSlider *mVolumnSlider;

    QLabel *mCurrentTime;
    QLabel *mTotalTime;

    QTimer *mTimer;
    int mMediaDuration = 0;
};
#endif // FVPLAYERWIDGET_H
