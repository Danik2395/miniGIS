module;
#include <entt/entt.hpp>
export module gengine.input;
import gengine.types.input;
import gengine.doc;

export namespace geng::input
{
void update_viewport(geng::Doc& doc, double vh, double vw);
} // namespace geng::input



namespace geng::input
{
void update_viewport(geng::Doc& doc, double vh, double vw)
{
    auto& viewport = doc.reg().ctx().get<geng::Viewport>();

    viewport.height = vh;
    viewport.width  = vw;
}
} // namespace geng::input
