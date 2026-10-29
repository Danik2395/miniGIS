module;
#include <gtest/gtest.h>
export module geotest:math_relations;
import gengine.types;
import gengine.math;

TEST(Relations, IsPointOnSegment)
{
    geng::Point seg_p0(1, 3);
    geng::Point seg_p1(5, 7);

    geng::Point point_on_segment(3, 5);
    EXPECT_TRUE(geng::math::is_point_on_segment(point_on_segment, seg_p0, seg_p1));

    geng::Point point_collinear_out_of_segment(6, 8);
    EXPECT_FALSE(geng::math::is_point_on_segment(point_collinear_out_of_segment, seg_p0, seg_p1));

    geng::Point deg_seg_p0(5, 5);
    geng::Point deg_seg_p1(5, 5);
    geng::Point point_on_deg_seg(5, 5);
    EXPECT_TRUE(geng::math::is_point_on_segment(point_on_deg_seg, deg_seg_p0, deg_seg_p1));
}

TEST(Relations, IsPointEndOfSegment)
{
    geng::Point seg_p0(1, 3);
    geng::Point seg_p1(5, 7);
    geng::Point p(3, 5);

    EXPECT_TRUE(geng::math::is_point_end_of_segment(seg_p0, seg_p0, seg_p1).first);
    EXPECT_FALSE(geng::math::is_point_end_of_segment(p, seg_p0, seg_p1).first);

    geng::Point deg_seg_p0(5, 5);
    geng::Point deg_seg_p1(5, 5);
    EXPECT_TRUE(geng::math::is_point_on_segment(deg_seg_p0, deg_seg_p0, deg_seg_p1));
}
