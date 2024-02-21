#include "foxavwindow.h"
#include "ui_foxavwindow.h"

FoxAVWindow::FoxAVWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FoxAVWindow)
{
    ui->setupUi(this);
}

FoxAVWindow::~FoxAVWindow()
{
    delete ui;
}
