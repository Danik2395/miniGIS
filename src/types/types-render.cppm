module;
#include <variant>
#include <cstdint>
export module gengine.types.render;
import gengine.types.primitives;

export namespace geng
{
using Geometry = std::variant<geng::Point,
                              geng::Segment,
                              geng::LineString,
                              geng::Polygon>;

struct [[nodiscard]] Color;

struct [[nodiscard]] RenderUnit;
} // namespace geng



namespace geng
{
struct Color
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 255;

    constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

    static constexpr Color RGBA(uint32_t hex)
    {
        return Color(
                static_cast<uint8_t>(hex >> 24 & 0x000000FF),
                static_cast<uint8_t>(hex >> 16 & 0x000000FF),
                static_cast<uint8_t>(hex >> 8  & 0x000000FF),
                static_cast<uint8_t>(hex       & 0x000000FF)
                );
    }

    static constexpr Color RGB(uint32_t hex)
    {
        return RGBA(hex & 0xFFFFFF00 + 0x000000FF);
    }
};

struct RenderUnit
{
    geng::Geometry geometry;
    geng::Color main_color;
    geng::Color fill_color;
    float thickness;
};
}
