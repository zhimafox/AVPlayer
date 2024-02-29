#include "player/FxPlayerWidget.h"
#include <memory>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::shared_ptr<FxPlayerWidget> w = std::make_shared<FxPlayerWidget>();
    w->initSessionMgr();
    w->show();
    return a.exec();
}
