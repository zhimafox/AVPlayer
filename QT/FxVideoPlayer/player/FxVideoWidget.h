#ifndef FXVIDEOWIDGET_H
#define FXVIDEOWIDGET_H

#include <QWidget>
#include <qmutex.h>

class FxVideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FxVideoWidget(QWidget *parent = nullptr);

    void updateImage(const QImage& image);
    void updatePixmap(const QPixmap& pixmap);

signals:

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_pixmap;
    QMutex m_mutex;
};

#endif // FXVIDEOWIDGET_H
