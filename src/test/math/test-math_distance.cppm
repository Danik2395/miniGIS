module;
#include <vector>
#include <gtest/gtest.h>
export module geotest:math_distance;
import :table;
import gengine.types;
import gengine.math;

TEST(math_Distance, Euclidean)
{
    const geng::Point p1(6.2, 14.3);
    const geng::Point p2(3.2, 18.3);
    const double expected_distance = 5.0;

    const double result_distance = geng::math::distance_euclidean(p1, p2);

    EXPECT_DOUBLE_EQ(result_distance, expected_distance);
}

TEST(math_Distance, PointToSegmentFuncOverloadsEqual)
{
    const geng::Point p = {7.7, 15.8};
    const geng::Point seg_p0  = {5, 5};
    const geng::Point seg_p1  = {10, 5};
    const geng::Segment seg(seg_p0, seg_p1);

    const double distance_point_points = geng::math::distance(p, seg_p0, seg_p1);
    const double distance_point_seg = geng::math::distance(p, seg);

    EXPECT_DOUBLE_EQ(distance_point_points, distance_point_seg);
}

TEST(math_Distance, PointToDegeneratedSegment)
{
    const geng::Point p = {3.2, 2};
    const geng::Point seg_p0  = {4.0, 15.0};
    const geng::Point seg_p1  = {4.0, 15.0};
    const double expected_distance = geng::math::distance_euclidean(p, seg_p0);

    const double result_distance = geng::math::distance(p, seg_p0, seg_p1);

    EXPECT_DOUBLE_EQ(result_distance, expected_distance);
}

namespace test::distance
{
struct [[nodiscard]] DistanceArrange
{
    const char* name;
    geng::Point p;
    geng::Point seg_p0;
    geng::Point seg_p1;
    double expected_distance;
};
} // namespace test::distance

TEST(math_Distance, ValidCases)
{
    using test::distance::DistanceArrange;

    const std::vector<DistanceArrange> distance_table = {
        {
            .name = "PointToSegmentPointHasProjectionOnSegment",
            .p = {7.7, 15.8},
            .seg_p0 = {5.0, 5.0},
            .seg_p1 = {10.0, 5.0},
            .expected_distance = 10.8,
        },
        {
            .name = "PointToSegmentPointOutOfProjectionToRight",
            .p = {15.8, 5.0},
            .seg_p0 = {5.0, 5.0},
            .seg_p1 = {10.0, 5.0},
            .expected_distance = 5.8,
        },
        {
            .name = "PointToSegmentPointOutOfProjectionToLeft",
            .p = {-5.0, 5.0},
            .seg_p0 = {5.0, 5.0},
            .seg_p1 = {10.0, 5.0},
            .expected_distance = 10.0,
        },
        {
            .name = "PointToVerticalSegment",
            .p = {0.0, 15.8},
            .seg_p0 = {0.0, 1.0},
            .seg_p1 = {0.0, 10.0},
            .expected_distance = 5.8,
        },
        {
            .name = "PointToSegmentPointOnTheSegment",
            .p = {3.0, 2.0},
            .seg_p0 = {5.0, 4.0},
            .seg_p1 = {1.0, 0.0},
            .expected_distance = 0.0,
        },
        {
            .name = "PointToSegmentPointOnTheEndOfSegment",
            .p = {5.0, 4.0},
            .seg_p0 = {5.0, 4.0},
            .seg_p1 = {1.0, 0.0},
            .expected_distance = 0.0,
        },
    };

    test::table::run_test_table(distance_table, [](const DistanceArrange& c){
            const double result_distance = geng::math::distance(c.p, c.seg_p0, c.seg_p1);

            EXPECT_DOUBLE_EQ(result_distance, c.expected_distance);
            });
}
