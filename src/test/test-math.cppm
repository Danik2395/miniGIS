module;
#include <gtest/gtest.h>
#include <gmock/gmock.h>
export module geotest:math;
import gengine.types;
import gengine.math;

TEST(DistancePointToSegment, CorrectPoint)
{
    geng::Point target_p = {7.7, 15.8};
    geng::Point line_p0  = {5, 5};
    geng::Point line_p1  = {10, 5};

    EXPECT_DOUBLE_EQ(
            geng::math::calc_distance_point_to_segment(target_p, line_p0, line_p1),
            10.8
            );

    EXPECT_DOUBLE_EQ(
            geng::math::calc_distance_point_to_segment(target_p, line_p1, line_p0),
            10.8
            );
}

TEST(DistancePointToSegment, PointOutOfProjection)
{
    using namespace testing;

    geng::Point target_p = {15.8, 5};
    geng::Point line_p0  = {5, 5};
    geng::Point line_p1  = {10, 5};

    EXPECT_DOUBLE_EQ(
            geng::math::calc_distance_point_to_segment(target_p, line_p1, line_p0),
            5.8
            );

    target_p = {-5, 5};
    EXPECT_DOUBLE_EQ(
            geng::math::calc_distance_point_to_segment(target_p, line_p1, line_p0),
            10
            );

    EXPECT_THAT(
            8.8,
            Not(DoubleEq(geng::math::calc_distance_point_to_segment(target_p, line_p1, line_p0)))
            );
}

TEST(DistancePointToSegment, VerticalSegment)
{
    geng::Point target_p = {0, 15.8};
    geng::Point line_p0  = {0, 1};
    geng::Point line_p1  = {0, 10};

    EXPECT_DOUBLE_EQ(
            geng::math::calc_distance_point_to_segment(target_p, line_p0, line_p1),
            5.8
            );
}

TEST(AreaPolygon, NormalPolygon)
{
    geng::Polygon poly_only_outer = {{
        {10, 0},
        {10, 10},
        {0, 10},
        {0, 0}
    }};
    geng::Polygon poly_full = {{
        {10, 0},
        {10, 10},
        {0, 10},
        {0, 0}
    }, {{
        {0, 0},
        {0, 5},
        {5, 5},
        {5, 0}}
    }};

    EXPECT_DOUBLE_EQ(geng::math::calc_area_polygon(poly_only_outer), 100);
    EXPECT_DOUBLE_EQ(geng::math::calc_area_polygon(poly_full), 75);
}
