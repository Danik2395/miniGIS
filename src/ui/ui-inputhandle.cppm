module;
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPointF>
#include <array>
#include <algorithm>
export module ui.inputhandle;
import gengine.types;
import gengine.doc;
import gengine.input;

export namespace ui::inputhandle
{
[[nodiscard]]
bool handle_keypress(geng::Doc& doc, QKeyEvent* key_event);

void handle_mouse(geng::Doc& doc, QMouseEvent* mouse_event);
} // namespace ui::inputhandle



namespace ui::inputhandle
{
struct [[nodiscard]] KeyBinding
{
    int key;
    void (*action)(geng::Doc&);
};

// п.77(2026-11-25)
constexpr std::array key_bindings = {
    ui::inputhandle::KeyBinding{Qt::Key_Up,    [](geng::Doc& d){ geng::input::pan(d,   0.0,  25.0); }},
    ui::inputhandle::KeyBinding{Qt::Key_Down,  [](geng::Doc& d){ geng::input::pan(d,   0.0, -25.0); }},
    ui::inputhandle::KeyBinding{Qt::Key_Left,  [](geng::Doc& d){ geng::input::pan(d, -25.0,   0.0); }},
    ui::inputhandle::KeyBinding{Qt::Key_Right, [](geng::Doc& d){ geng::input::pan(d,  25.0,   0.0); }},
};

bool handle_keypress(geng::Doc& doc, QKeyEvent* key_event)
{
    const auto key_bind = std::ranges::find(key_bindings, key_event->key(), &ui::inputhandle::KeyBinding::key);

    const bool has_action_on_key = key_bind != key_bindings.end();

    if (!has_action_on_key) return false;

    key_bind->action(doc);

    return true;
}

geng::MouseButtons get_mouse_buttons(QMouseEvent* mouse_event)
{
    const auto qbuttons = mouse_event->buttons();

    const bool b1_pressed = qbuttons & Qt::LeftButton;
    const bool b2_pressed = qbuttons & Qt::RightButton;
    const bool b3_pressed = qbuttons & Qt::MiddleButton;

    return {b1_pressed, b2_pressed, b3_pressed};
}

geng::Point get_mouse_pos(QMouseEvent* mouse_event)
{
    const auto qmouse_pos = mouse_event->position();

    return {qmouse_pos.x(), qmouse_pos.y()};
}

void handle_mouse(geng::Doc& doc, QMouseEvent* mouse_event)
{
    const auto mouse_buttons = ui::inputhandle::get_mouse_buttons(mouse_event);
    const auto mouse_pos = ui::inputhandle::get_mouse_pos(mouse_event);

    geng::input::update_mouse(doc, mouse_pos, mouse_buttons);
}
} // namespace ui::inputhandle
