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
} // namespace geng::input



namespace geng::input
{
void pan(geng::Doc& doc, double dx, double dy)
{
    auto& camera = doc.reg().ctx().get<geng::Camera>();

    camera.x_offset += dx;
    camera.y_offset += dy;
}
} // namespace geng::input
