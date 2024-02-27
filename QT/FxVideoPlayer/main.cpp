#include "FvPlayerWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FvPlayerWidget w;
    w.show();
    return a.exec();
}
