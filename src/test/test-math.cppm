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
            geng::math::distance(target_p, line_p0, line_p1),
            10.8
            );

    EXPECT_DOUBLE_EQ(
            geng::math::distance(target_p, line_p1, line_p0),
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
            geng::math::distance(target_p, line_p1, line_p0),
            5.8
            );

    target_p = {-5, 5};
    EXPECT_DOUBLE_EQ(
            geng::math::distance(target_p, line_p1, line_p0),
            10
            );

    EXPECT_THAT(
            8.8,
            Not(DoubleEq(geng::math::distance(target_p, line_p1, line_p0)))
            );
}

TEST(DistancePointToSegment, VerticalSegment)
{
    geng::Point target_p = {0, 15.8};
    geng::Point line_p0  = {0, 1};
    geng::Point line_p1  = {0, 10};

    EXPECT_DOUBLE_EQ(
            geng::math::distance(target_p, line_p0, line_p1),
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

    EXPECT_DOUBLE_EQ(geng::math::area(poly_only_outer), 100);
    EXPECT_DOUBLE_EQ(geng::math::area(poly_full), 75);
}

TEST(OrientationPointSegment, Test)
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

TEST(IntersectionPointOfSegments, CheckIntersection)
{
    geng::Segment seg1 = {{2, 3}, {12, 13}};

    geng::Segment seg_intersect          = {{2, 8}, {7, 4}};
    geng::Segment seg_intersect_vertical = {{7, 1}, {7, 41}};

    geng::Segment seg_nointersect          = {{1, 2}, {-3, -7}};
    geng::Segment seg_nointersect_parallel = {{seg1.p0.x + 2, seg1.p0.y},
                                               {seg1.p1.x + 2, seg1.p1.y}};

    EXPECT_EQ(geng::math::is_intersect(seg1, seg_intersect), true);
    EXPECT_EQ(geng::math::is_intersect(seg1, seg_intersect_vertical), true);

    EXPECT_EQ(geng::math::is_intersect(seg1, seg_nointersect), false);
    EXPECT_EQ(geng::math::is_intersect(seg1, seg_nointersect_parallel), false);

    EXPECT_EQ(geng::math::is_intersect(seg1, seg1), true);
}

TEST(IntersectionPointOfSegments, CalcIntersectionPoint)
{
    geng::Segment seg1           = {{1, 1}, {3, 5}};
    geng::Segment seg2           = {{1, 5}, {3, 1}};
    geng::Segment seg3           = {{3, 5}, {7, 13}};
    geng::Segment seg_horisontal = {{-4, 3}, {6, 3}};
    geng::Segment seg_vertical1  = {{2, -2}, {2, 8}};
    geng::Segment seg_vertical2  = {{3, 3}, {3, 7}};

    EXPECT_EQ(std::get<geng::Point>(geng::math::intersection(seg1, seg2)), geng::Point(2, 3));
    EXPECT_EQ(std::get<geng::Point>(geng::math::intersection(seg1, seg3)), geng::Point(3, 5));

    EXPECT_EQ(std::get<geng::Point>(geng::math::intersection(seg1, seg_horisontal)), geng::Point(2, 3));

    EXPECT_EQ(std::get<geng::Point>(geng::math::intersection(seg1, seg_vertical1)), geng::Point(2, 3));
    EXPECT_EQ(std::get<geng::Point>(geng::math::intersection(seg_vertical1, seg1)), geng::Point(2, 3));

    EXPECT_EQ(std::get<geng::Point>(geng::math::intersection(seg_vertical1, seg_horisontal)), geng::Point(2, 3));
    EXPECT_EQ(std::get<geng::Point>(geng::math::intersection(seg_horisontal, seg_vertical2)), geng::Point(3, 3));

    EXPECT_EQ(std::get<geng::Segment>(geng::math::intersection(seg1, seg1)), seg1);
}
