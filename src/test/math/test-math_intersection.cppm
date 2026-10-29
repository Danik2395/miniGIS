module;
#include <gtest/gtest.h>
export module geotest:math_intersection;
import gengine.types;
import gengine.math;

TEST(Intersection, SinglePointNonCollinearSegmentIntersection)
{
    geng::Segment seg1 = {{1, 1}, {3, 5}};

    geng::Segment seg2 = {{1, 5}, {3, 1}};
    EXPECT_EQ(std::get<geng::Point>(geng::math::intersection(seg1, seg2)), geng::Point(2, 3));

    geng::Segment seg_horisontal = {{-4, 3}, {6, 3}};
    EXPECT_EQ(std::get<geng::Point>(geng::math::intersection(seg1, seg_horisontal)), geng::Point(2, 3));

    geng::Segment seg_vertical1 = {{2, -2}, {2, 8}};
    geng::Segment seg_vertical2 = {{3, 3},  {3, 7}};
    EXPECT_EQ(std::get<geng::Point>(geng::math::intersection(seg1, seg_vertical1)), geng::Point(2, 3));
    EXPECT_EQ(std::get<geng::Point>(geng::math::intersection(seg_vertical1, seg1)), geng::Point(2, 3));
    EXPECT_EQ(std::get<geng::Point>(geng::math::intersection(seg_vertical1, seg_horisontal)), geng::Point(2, 3));
}

TEST(Intersection, SinglePointCollinearSegmentIntersection)
{
    geng::Segment seg1 = {{1, 1}, {3, 5}};
    geng::Segment seg2 = {{3, 5}, {7, 13}};
    EXPECT_EQ(std::get<geng::Point>(geng::math::intersection(seg1, seg2)), geng::Point(3, 5));
}

TEST(Intersection, NoIntersectionSegmentIntersiction)
{
    geng::Segment seg1 = {{1, 1}, {3, 5}};
    geng::Segment seg2 = {{-3, -5}, {-7, -13}};
    EXPECT_EQ(std::get<std::monostate>(geng::math::intersection(seg1, seg2)), std::monostate());
}

TEST(Intersection, MultiplePointCollinearSegmentIntersection)
{
    geng::Segment seg1 = {{1, 1}, {3, 5}};
    EXPECT_EQ(std::get<geng::Segment>(geng::math::intersection(seg1, seg1)), seg1);

    geng::Segment seg_horisontal0 = {{-4, 3}, {9.884, 3}};
    geng::Segment seg_horisontal1 = {{5, 3},  {15, 3}};
    geng::Segment seg_horisontal2 = {{5, 3},  {6, 3}};
    EXPECT_EQ(std::get<geng::Segment>(geng::math::intersection(seg_horisontal0, seg_horisontal1)),
            geng::Segment({5, 3}, {9.884, 3}));
    EXPECT_EQ(std::get<geng::Segment>(geng::math::intersection(seg_horisontal0, seg_horisontal2)),
            geng::Segment({5, 3}, {6, 3}));
}

TEST(Intersection, IsSegmentsIntersect)
{
    geng::Segment seg_intersect1 = {{1, 1}, {3, 5}};
    geng::Segment seg_intersect2 = {{1, 5}, {3, 1}};
    EXPECT_TRUE(geng::math::is_intersect(seg_intersect1, seg_intersect2));

    geng::Segment seg_dont_intersect1 = {{1, 1}, {3, 5}};
    geng::Segment seg_dont_intersect2 = {{-1, -5}, {-3, -1}};
    EXPECT_FALSE(geng::math::is_intersect(seg_dont_intersect1, seg_dont_intersect2));
}
