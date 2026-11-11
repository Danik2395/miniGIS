#pragma once
#include <QMainWindow>
#include <QObject>

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
    explicit GAppWindow(QMainWindow* parent = nullptr);

    ~GAppWindow();
};
