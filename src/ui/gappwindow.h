#pragma once
#include <QMainWindow>
#include <QObject>
#include <memory>
#include <filesystem>

namespace geng
{
class AppState;
} // namespace geng

namespace Ui
{
class GAppWindow;
} // namespace Ui

class GAppWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::GAppWindow* ui = nullptr;
    std::unique_ptr<geng::AppState> app;

public:
    explicit GAppWindow(QMainWindow* parent = nullptr);

    void open_file(const std::filesystem::path& path);

    void update_canvas();

    ~GAppWindow() override;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
};
