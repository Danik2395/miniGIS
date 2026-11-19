module;
#include <cstdint>
#include <gtest/gtest.h>
export module geotest:types_render;
import gengine.types.render;

namespace test::render
{
void expect_color_eq(geng::Color color, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    EXPECT_EQ(color.r, r);
    EXPECT_EQ(color.g, g);
    EXPECT_EQ(color.b, b);
    EXPECT_EQ(color.a, a);
}
} // namespace test::render

TEST(types_Color, ConstructorRGBValidHex)
{
    uint32_t hex_rgb = 0x020406;

    auto color_rgb = geng::Color::RGB(hex_rgb);

    test::render::expect_color_eq(color_rgb, 2, 4, 6, 255);
}

TEST(types_Color, ConstructorRGBNarrowingHexAssert)
{
    uint32_t hex_rgba = 0x02040608;

    ASSERT_DEBUG_DEATH(std::ignore = geng::Color::RGB(hex_rgba), ".*must.*RGB");
}

TEST(types_Color, ConstructorRGBA)
{
    uint32_t hex_rgba = 0x09080706;

    auto color_rgba = geng::Color::RGBA(hex_rgba);

    test::render::expect_color_eq(color_rgba, 9, 8, 7, 6);
}
