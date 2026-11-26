#include <QMainWindow>
#include <QEvent>
#include <QKeyEvent>
#include <new>
#include <memory>
#include <filesystem>
#include "gappwindow.h"
#include "entt/entt.hpp"
#include "ui_gappwindow.h"
import ui.inputhandle;
import gengine.looprunner;
import gengine.types.precision;
import gengine.serialization;
import gengine.input;
import gengine.doc;

GAppWindow::GAppWindow(QMainWindow* parent)
    : QMainWindow(parent)
    , ui(new Ui::GAppWindow)
    , app(std::make_unique<geng::AppState>())
{
    ui->setupUi(this);

    ui->canvas->installEventFilter(this);
    ui->canvas->setFocusPolicy(Qt::StrongFocus);

    // on_open_file()
    // {
    // call some file selector

    open_file("");

    // set up canvas for this file
    // set this canvas as top widget

    update_canvas();
    // }
}

void GAppWindow::open_file(const std::filesystem::path& path)
{
    auto new_file_reg = geng::serial::reg_from_file(path);

    auto current_doc_id = app->add_doc(std::move(new_file_reg));

    app->set_current_doc_id(current_doc_id);
}

void GAppWindow::update_canvas()
{
    auto doc = app->get_current_doc();

    auto render_sequence = geng::looprunner::run_frame(doc);

    ui->canvas->draw(std::move(render_sequence));
}

GAppWindow::~GAppWindow()
{
    delete ui;
}

bool GAppWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (app->id_current_doc() == geng::docIdGuard || watched != ui->canvas)
    {
        return QWidget::eventFilter(watched, event);
    }

    auto doc = app->get_current_doc();

    bool action_occurred = action_on_filtered_event(doc, event);

    if (action_occurred)
    {
        update_canvas();
    }

    return action_occurred || QWidget::eventFilter(watched, event);
}

bool GAppWindow::action_on_filtered_event(geng::Doc& doc, QEvent* event)
{
    bool action_occurred = false;

    switch (event->type())
    {
        case QEvent::Resize:
            geng::input::update_viewport(doc, ui->canvas->height(), ui->canvas->width());
            break;

        case QEvent::KeyPress:
            action_occurred = ui::inputhandle::handle_keypress(doc, static_cast<QKeyEvent*>(event));
            break;

        default:
            break;
    }

    return action_occurred;
}
