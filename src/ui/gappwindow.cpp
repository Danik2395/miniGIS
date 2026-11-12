#include <QMainWindow>
#include <new>
#include <memory>
#include "gappwindow.h"
#include "entt/entt.hpp"
#include "ui_gappwindow.h"
import gengine.render;
import gengine.types.precision;

GAppWindow::GAppWindow(QMainWindow* parent)
    : QMainWindow(parent)
    , ui(new Ui::GAppWindow)
    , app_state(std::make_unique<geng::AppState>())
{
    auto test_reg = entt::registry();
    test_reg.ctx().emplace<geng::QuantizePrecision>(1e-9, 1e+9);

    auto current_doc_id = app_state->add_doc(std::move(test_reg));

    app_state->set_current_doc_id(current_doc_id);

    ui->setupUi(this);
    update_canvas();
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
