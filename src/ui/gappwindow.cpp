#include <QMainWindow>
#include <new>
#include <memory>
#include <filesystem>
#include "gappwindow.h"
#include "entt/entt.hpp"
#include "ui_gappwindow.h"
import gengine.render;
import gengine.types.precision;
import gengine.serialization;

GAppWindow::GAppWindow(QMainWindow* parent)
    : QMainWindow(parent)
    , ui(new Ui::GAppWindow)
    , app_state(std::make_unique<geng::AppState>())
{
    ui->setupUi(this);

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

    auto current_doc_id = app_state->add_doc(std::move(new_file_reg));

    app_state->set_current_doc_id(current_doc_id);
}

void GAppWindow::update_canvas()
{
    auto doc = app_state->current_doc();

    auto render_sequence = geng::render::query_draw_sequence(doc);

    ui->canvas->draw(std::move(render_sequence));
}

GAppWindow::~GAppWindow()
{
    delete ui;
}
