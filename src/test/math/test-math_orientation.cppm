module;
#include <gtest/gtest.h>
export module geotest:math_orientation;
import gengine.types;
import gengine.math;

TEST(Orientation, PointToSegment)
{
    geng::Point seg_p0(5, 5);
    geng::Point seg_p1(20, 10);

    geng::Point to_left_point(8, 10);
    geng::Point to_right_point(8, -10);
    geng::Point collinear_point(11, 7);

    EXPECT_EQ(geng::math::orientation(to_left_point, seg_p0, seg_p1), geng::math::Orientation::LEFT);
    EXPECT_EQ(geng::math::orientation(to_right_point, seg_p0, seg_p1), geng::math::Orientation::RIGHT);
    EXPECT_EQ(geng::math::orientation(collinear_point, seg_p0, seg_p1), geng::math::Orientation::COLLINEAR);
}
