module;
#include <gtest/gtest.h>
export module geotest:math_orientation;
import gengine.types;
import gengine.math;

TEST(Orientation, PointToSegmentPointNotOnSegment)
{
    geng::Point seg_p0(5, 5);
    geng::Point seg_p1(20, 10);

    geng::Point to_left_point(8, 10);
    geng::Point to_right_point(8, -10);
    geng::Point collinear_point(11, 7);

    EXPECT_EQ(geng::math::orientation(to_left_point, seg_p0, seg_p1),   geng::math::Orientation::LEFT);
    EXPECT_EQ(geng::math::orientation(to_right_point, seg_p0, seg_p1),  geng::math::Orientation::RIGHT);
    EXPECT_EQ(geng::math::orientation(collinear_point, seg_p0, seg_p1), geng::math::Orientation::COLLINEAR);
}

TEST(Orientation, PointOnSegmentToThatSegment)
{
    geng::Point seg_p0(1, 3);
    geng::Point seg_p1(5, 7);

    geng::Point point_on_segment(3, 5);
    geng::Point point_on_the_end_of_segment(5, 7);

    EXPECT_EQ(geng::math::orientation(point_on_segment, seg_p0, seg_p1),            geng::math::Orientation::COLLINEAR);
    EXPECT_EQ(geng::math::orientation(point_on_the_end_of_segment, seg_p0, seg_p1), geng::math::Orientation::COLLINEAR);
}
