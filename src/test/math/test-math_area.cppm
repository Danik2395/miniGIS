module;
#include <gtest/gtest.h>
export module geotest:math_area;
import gengine.types;
import gengine.math;

TEST(Area, PolygonWktCorrect)
{
    geng::Polygon poly_only_outer = {{
        {15, 5},
        {15, 15},
        {5, 15},
        {5, 5},
        {15, 5}
    }};
    EXPECT_DOUBLE_EQ(geng::math::area(poly_only_outer), 100);

    geng::Polygon poly_full = {{
        {15, 5},
        {15, 15},
        {5, 15},
        {5, 5},
        {15, 5}
    }, {
        {
            {5, 5},
            {5, 10},
            {10, 10},
            {10, 5},
            {5, 5}
        }
    }};
    EXPECT_DOUBLE_EQ(geng::math::area(poly_full), 75);
}
