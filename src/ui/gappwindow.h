#pragma once
#include <QMainWindow>
#include <QObject>
#include <new>
#include "ui_gappwindow.h"

namespace Ui
{
class GAppWindow;
} // namespace Ui

class GAppWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::GAppWindow* ui = nullptr;

public:
    explicit GAppWindow(QMainWindow* parent = nullptr) : QMainWindow(parent), ui(new Ui::GAppWindow)
    {
        ui->setupUi(this);
        ui->canvas->draw();
    }

    ~GAppWindow()
    {
        delete ui;
    }
};
