module;
#include <gtest/gtest.h>
export module geotest:math_distance;
import gengine.types;
import gengine.math;

TEST(Distance, PointToSegmentPointHasProjectionOnSegment)
{
    geng::Point target_p = {7.7, 15.8};
    geng::Point line_p0  = {5, 5};
    geng::Point line_p1  = {10, 5};

    EXPECT_DOUBLE_EQ(
            geng::math::distance(target_p, line_p0, line_p1),
            10.8
            );

    EXPECT_DOUBLE_EQ(
            geng::math::distance(target_p, line_p1, line_p0),
            10.8
            );
}

TEST(Distance, PointToSegmentPointOutOfProjection)
{
    geng::Point target_p = {15.8, 5};
    geng::Point line_p0  = {5, 5};
    geng::Point line_p1  = {10, 5};

    EXPECT_DOUBLE_EQ(
            geng::math::distance(target_p, line_p1, line_p0),
            5.8
            );

    target_p = {-5, 5};
    EXPECT_DOUBLE_EQ(
            geng::math::distance(target_p, line_p1, line_p0),
            10
            );
}

TEST(Distance, PointToVerticalSegment)
{
    geng::Point target_p = {0, 15.8};
    geng::Point line_p0  = {0, 1};
    geng::Point line_p1  = {0, 10};

    EXPECT_DOUBLE_EQ(
            geng::math::distance(target_p, line_p0, line_p1),
            5.8
            );
}
