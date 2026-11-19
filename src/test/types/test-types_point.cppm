module;
#include <array>
#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
export module geotest:types_point;
import gengine.types;

TEST(types_Point, PointsEqualNanAssert)
{
    const geng::Point nan_point(NAN, NAN);
    const geng::Point normal_point(0, 5.0);

    ASSERT_DEBUG_DEATH(std::ignore = (nan_point == normal_point), "NaN");
}

TEST(types_Point, SortTest)
{
    const std::array expected_sorted_points = {
        geng::Point(15.1, 5.0),
        geng::Point(15.1, 5.5),
        geng::Point(16.1, 5.5),
        geng::Point(16.1, 7.5),
    };
    std::array to_be_sorted_points = {
        expected_sorted_points[2],
        expected_sorted_points[0],
        expected_sorted_points[3],
        expected_sorted_points[1],
    };

    std::ranges::sort(to_be_sorted_points);

    EXPECT_EQ(to_be_sorted_points, expected_sorted_points);
}

TEST(types_Point, PointPlusVec2)
{
    const geng::Point p(5.0, 13.8);
    const geng::Vec2 vec(3.5, 4.0);
    const geng::Point expected_point(8.5, 17.8);

    const geng::Point result_point = p + vec;

    EXPECT_EQ(expected_point, result_point);
}

TEST(types_Point, PointMinusVec2)
{
    const geng::Point p(9.0, 9.8);
    const geng::Vec2 vec(-1.5, 8.0);
    const geng::Point expected_point(10.5, 1.8);

    const geng::Point result_point = p - vec;

    EXPECT_EQ(expected_point, result_point);
}
