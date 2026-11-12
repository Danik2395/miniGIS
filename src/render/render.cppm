module;
#include <vector>
export module gengine.render;
import gengine.doc;
import gengine.types.render;
import gengine.types.primitives;

export namespace geng::render
{
[[nodiscard]]
std::vector<geng::RenderUnit> query_draw_sequence(const geng::Doc& doc);
} // namespace geng



namespace geng::render
{
std::vector<geng::RenderUnit> query_draw_sequence(const geng::Doc& doc)
{
    std::vector<geng::RenderUnit> sequence;

    sequence.emplace_back(
                geng::LineString({{50, 50}, {150, 150}}),
                geng::Color::RGBA(0xFFC0CBFF),
                geng::Color::RGBA(0),
                5.0
                );
    sequence.emplace_back(
                geng::LineString({{150, 150}, {200, 50}}),
                geng::Color::RGB(0x00FF00),
                geng::Color::RGBA(0),
                5.0
                );

    return sequence;
}
} // namespace geng
