module;
#include <ranges>
#include <vector>
export module gengine.render;
import gengine.doc;
import gengine.types.render;
import gengine.types.primitives;

export namespace geng::render
{
[[nodiscard]]
std::vector<geng::RenderUnit> query_draw_sequence(const geng::Doc& doc);
} // namespace geng::render



namespace geng::render
{
geng::RenderUnit create_render_unit(auto&& group)
{
    const auto& [entity, geom, style] = group;

    // п.56

    return geng::RenderUnit(geom, style);
}

std::vector<geng::RenderUnit> query_draw_sequence(const geng::Doc& doc)
{
    const auto& reg = doc.reg();

    // п.55
    const auto raw_component_view = reg.view<const geng::Geometry, const geng::Style>();

    auto render_unit_view = raw_component_view.each() | std::views::transform([](auto&& group) {
            return geng::render::create_render_unit(group);
            });

    std::vector<geng::RenderUnit> draw_sequence;
    draw_sequence.reserve(raw_component_view.size_hint());

    draw_sequence.append_range(render_unit_view);

    return draw_sequence;
}
} // namespace geng::render
