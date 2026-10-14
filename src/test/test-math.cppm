module;
#include <gtest/gtest.h>
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
