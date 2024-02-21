#ifndef FOXAVWINDOW_H
#define FOXAVWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class FoxAVWindow;
}
QT_END_NAMESPACE

class FoxAVWindow : public QMainWindow
{
    Q_OBJECT

public:
    FoxAVWindow(QWidget *parent = nullptr);
    ~FoxAVWindow();

private:
    Ui::FoxAVWindow *ui;
};
#endif // FOXAVWINDOW_H
