module;
#include <cassert>
#include <cstdint>
export module gengine.types.render;
import gengine.types.primitives;

export namespace geng
{
struct [[nodiscard]] Color;

struct [[nodiscard]] Style;

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

    static constexpr Color RGBA(uint32_t hex)
    {
        return Color{
            static_cast<uint8_t>(hex >> 24 & 0x000000FF),
            static_cast<uint8_t>(hex >> 16 & 0x000000FF),
            static_cast<uint8_t>(hex >> 8  & 0x000000FF),
            static_cast<uint8_t>(hex       & 0x000000FF)
        };
    }

    static constexpr Color RGB(uint32_t hex)
    {
        assert(hex <= 0xFFFFFF &&  "Color::RGB: hex must be in RGB format.");

        return RGBA((hex << 8) | 0x000000FF);
    }
};

struct Style
{
    geng::Color main_color;
    geng::Color fill_color;
    float thickness = 0;
};

struct RenderUnit
{
    geng::Geometry geometry;
    geng::Style style;
};
} // namespace geng
