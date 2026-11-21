module;
#include <gtest/gtest.h>
export module geotest:math_area;
import gengine.types;
import gengine.math;

TEST(math_Area, PolygonWktCorrectWithoutInner)
{
    const geng::Polygon poly_only_outer = {{
        {15, 5},
        {15, 15},
        {5, 15},
        {5, 5},
        {15, 5}
    },
        {}
    };
    const double expected_area = 100;

    const double result_area = geng::math::area(poly_only_outer);

    EXPECT_DOUBLE_EQ(result_area, expected_area);
}

TEST(math_Area, PolygonWktCorrectFullPoly)
{
    const geng::Polygon poly_full = {
        {
            {15, 5},
            {15, 15},
            {5, 15},
            {5, 5},
            {15, 5}
        },
        {
            {
                {5, 5},
                {5, 10},
                {10, 10},
                {10, 5},
                {5, 5}
            }
        }
    };
    const double expected_area = 75;

    const double result_area = geng::math::area(poly_full);

    EXPECT_DOUBLE_EQ(result_area, expected_area);
}

// п.66
// TEST(math_Area, PolygonWktCorrectInitialAndTranslatedPolyAreasEqual)
// {
// }
