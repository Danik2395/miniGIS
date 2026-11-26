module;
#include <QKeyEvent>
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
} // namespace ui::inputhandle



namespace ui::inputhandle
{
struct [[nodiscard]] KeyBinding
{
    int key;
    void (*action)(geng::Doc&);
};

// п.73(2026-11-25)
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
} // namespace ui::inputhandle
