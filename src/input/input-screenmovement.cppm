module;
#include <entt/entt.hpp>
export module gengine.input:screenmovement;
import gengine.types.input;
import gengine.types.camera;
import gengine.types.primitives;
import gengine.doc;

export namespace geng::input
{
void pan(geng::Doc& doc, double dx, double dy);

void zoom_by(geng::Doc& doc, double scale_delta);

void zoom_to(geng::Doc& doc, double percent);
} // namespace geng::input



namespace geng::input
{
void pan(geng::Doc& doc, double dx, double dy)
{
    auto& camera = doc.reg().ctx().get<geng::Camera>();

    camera.x_offset += dx;
    camera.y_offset += dy;
}

void recalculate_offset_for_zoom_to_cursor(geng::Doc& doc, double scale_delta)
{
    auto& camera = doc.reg().ctx().get<geng::Camera>();
    const auto& mouse = doc.reg().ctx().get<geng::Mouse>();
    const auto& viewport = doc.reg().ctx().get<geng::Viewport>();

    const double screen_anchor_x = mouse.pos.x;
    const double screen_anchor_y = viewport.height - mouse.pos.y; // from client coordinates to screen normalized

    // screen_point = world_point * scale - offset
    // screen_point = world_point * scale_new - offset_new
    // solve system relative to offset_new. (scale_new = scale * scale_delta)
    camera.x_offset = scale_delta * camera.x_offset + (scale_delta - 1.0) * screen_anchor_x;
    camera.y_offset = scale_delta * camera.y_offset + (scale_delta - 1.0) * screen_anchor_y;
}

void zoom_by(geng::Doc& doc, double scale_delta)
{
    assert(scale_delta > 0 && "zoom_by: delta must be above zero.");

    recalculate_offset_for_zoom_to_cursor(doc, scale_delta);

    auto& camera = doc.reg().ctx().get<geng::Camera>();

    camera.scale *= scale_delta;
}

void zoom_to(geng::Doc& doc, double percent)
{
    assert(percent > 0 && "zoom_to: fraction must be above zero.");

    auto& camera = doc.reg().ctx().get<geng::Camera>();

    const double scale_delta = percent / camera.scale;

    zoom_by(doc, scale_delta);
}
} // namespace geng::input
