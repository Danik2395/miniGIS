#include <QMainWindow>
#include <new>
#include "gappwindow.h"
#include "ui_gappwindow.h"

GAppWindow::GAppWindow(QMainWindow* parent) : QMainWindow(parent), ui(new Ui::GAppWindow)
{
    ui->setupUi(this);
    ui->canvas->draw();
}

GAppWindow::~GAppWindow()
{
    delete ui;
}
