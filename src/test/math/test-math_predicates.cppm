module;
#include <vector>
#include <gtest/gtest.h>
export module geotest:math_predicates;
import :table;
import gengine.types;
import gengine.math;
import gengine.compare;

TEST(math_Predicates, IsDegeneratedSegReturnTrue)
{
    const geng::Segment deg_seg({6.8, 6.8}, {6.8, 6.8});

    const bool result_deg_seg = geng::math::is_degenerated(deg_seg);

    EXPECT_TRUE(result_deg_seg);
}

TEST(math_Predicates, IsDegeneratedSegReturnFalse)
{
    const geng::Segment seg({8.8, 3.8}, {9.1, 4.9});

    const bool result_deg_seg = geng::math::is_degenerated(seg);

    EXPECT_FALSE(result_deg_seg);
}

TEST(math_Predicates, IsPointOnSegmentFuncOverloadsEqual)
{
    const geng::Point seg_p0(1, 3);
    const geng::Point seg_p1(5, 7);
    const geng::Segment seg(seg_p0, seg_p1);
    const geng::Point point_on_segment(3, 5);

    const bool result_points = geng::math::is_point_on_segment(point_on_segment, seg_p0, seg_p1);
    const bool result_point_seg = geng::math::is_point_on_segment(point_on_segment, seg);

    EXPECT_EQ(result_points, result_point_seg);
}

namespace test::ispointonsegment
{
struct IsPointOnSegmentArrange
{
    const char* name;
    geng::Point seg_p0;
    geng::Point seg_p1;
    geng::Point target_p;
    bool expected_result;
};
} // test::ispointonsegment

TEST(math_Predicates, IsPointOnSegmentValidPoints)
{
    using test::ispointonsegment::IsPointOnSegmentArrange;

    const std::vector<IsPointOnSegmentArrange> is_point_on_segment_table = {
        {
            .name = "IsPointOnSegmentReturnTruePointOnTheSegment",
            .seg_p0 = {1.0, 3.0},
            .seg_p1 = {5.0, 7.0},
            .target_p = {3.0, 5.0},
            .expected_result = true,
        },
        {
            .name = "IsPointOnSegmentReturnTruePointOnDegSeg",
            .seg_p0 = {5.0, 5.0},
            .seg_p1 = {5.0, 5.0},
            .target_p = {5.0, 5.0},
            .expected_result = true,
        },
        {
            .name = "IsPointOnSegmentReturnFalsePointNotOnDegSeg",
            .seg_p0 = {5.0, 5.0},
            .seg_p1 = {5.0, 5.0},
            .target_p = {8.3, 2.0},
            .expected_result = false,
        },
        {
            .name = "IsPointOnSegmentReturnFalsePointCollinearWithSegPointOutsideOfSeg",
            .seg_p0 = {1.0, 3.0},
            .seg_p1 = {5.0, 7.0},
            .target_p = {6.0, 8.0},
            .expected_result = false,
        },
        {
            .name = "IsPointOnSegmentReturnFalsePointNotCollinearWithSeg",
            .seg_p0 = {1.0, 3.0},
            .seg_p1 = {5.0, 7.0},
            .target_p = {4.3, 3.8},
            .expected_result = false,
        },
        {
            .name = "IsPointOnSegmentReturnTruePointOnTheStartOfSeg",
            .seg_p0 = {1.0, 3.0},
            .seg_p1 = {5.0, 7.0},
            .target_p = {1.0, 3.0},
            .expected_result = true,
        },
        {
            .name = "IsPointOnSegmentReturnTruePointOnTheEndOfSeg",
            .seg_p0 = {1.0, 3.0},
            .seg_p1 = {5.0, 7.0},
            .target_p = {5.0, 7.0},
            .expected_result = true,
        },
    };

    test::table::run_test_table(is_point_on_segment_table, [](const IsPointOnSegmentArrange& c){
            const bool actual_result = geng::math::is_point_on_segment(c.target_p, c.seg_p0, c.seg_p1);

            EXPECT_EQ(actual_result, c.expected_result);
            });
}

TEST(math_Predicates, IsPointEndOfSegmentFuncOverloadsEqual)
{
    const geng::Point seg_p0(1.0, 3.0);
    const geng::Point seg_p1(5.0, 7.0);
    const geng::Segment seg(seg_p0, seg_p1);

    const auto result_end_point_points = geng::math::is_point_end_of_segment(seg_p0, seg_p0, seg_p1);
    const auto result_end_point_seg = geng::math::is_point_end_of_segment(seg_p0, seg);

    EXPECT_EQ(result_end_point_points, result_end_point_seg);
}

TEST(math_Predicates, IsPointEndOfSegmentReturnTrueOnLeftEnd)
{
    const geng::Point seg_p0(1.0, 3.0);
    const geng::Point seg_p1(5.0, 7.0);
    const geng::Segment seg(seg_p0, seg_p1);

    const auto result_end_point = geng::math::is_point_end_of_segment(seg_p0, seg);

    EXPECT_TRUE(result_end_point.first);
    EXPECT_EQ(result_end_point.second, seg_p0);
}

TEST(math_Predicates, IsPointEndOfSegmentReturnTrueOnRightEnd)
{
    const geng::Point seg_p0(1.0, 3.0);
    const geng::Point seg_p1(5.0, 7.0);
    const geng::Segment seg(seg_p0, seg_p1);

    const auto result_end_point = geng::math::is_point_end_of_segment(seg_p1, seg);

    EXPECT_TRUE(result_end_point.first);
    EXPECT_EQ(result_end_point.second, seg_p1);
}

TEST(math_Predicates, IsPointEndOfSegmentReturnFalse)
{
    const geng::Point seg_p0(1.0, 3.0);
    const geng::Point seg_p1(5.0, 7.0);
    const geng::Point p_not_on_seg(7.7,5.2);
    const geng::Segment seg(seg_p0, seg_p1);

    const auto result_end_point = geng::math::is_point_end_of_segment(p_not_on_seg, seg);

    EXPECT_FALSE(result_end_point.first);
    EXPECT_EQ(result_end_point.second, geng::Point());
}
