module;
#include <entt/entt.hpp>
export module gengine.input:hid;
import gengine.types.input;
import gengine.types.primitives;
import gengine.doc;
import gengine.camera;

export namespace geng::input
{
void update_viewport(geng::Doc& doc, double vh, double vw);

void update_mouse(geng::Doc& doc, geng::Point pos, geng::MouseButtons buttons);
} // namespace geng::input



namespace geng::input
{
void update_viewport(geng::Doc& doc, double vh, double vw)
{
    auto& viewport = doc.reg().ctx().get<geng::Viewport>();

    viewport.height = vh;
    viewport.width  = vw;
}

void update_mouse(geng::Doc& doc, geng::Point pos, geng::MouseButtons buttons)
{
    auto& mouse = doc.reg().ctx().get<geng::Mouse>();

    mouse.last_pos = mouse.pos;
    mouse.pos = pos;
    mouse.buttons = buttons;

    geng::camera::update_camera_on_mouse_move(doc);
}
} // namespace geng::input
