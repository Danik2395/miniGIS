module;
#include <vector>
#include <gtest/gtest.h>
export module geotest:math_intersection;
import :table;
import gengine.types;
import gengine.math;

namespace test::segmentintersection
{
struct SegmentIntersectionArrange
{
    const char* name;
    geng::Segment seg1;
    geng::Segment seg2;
    geng::math::SegmentsIntersection expected_intersect;
};

template<typename IntersectionType>
void compare_segment_intersection(const SegmentIntersectionArrange& c)
{
    const auto result_intersect_in_variant = geng::math::intersection(c.seg1, c.seg2);
    const auto result_intersect = std::get<IntersectionType>(result_intersect_in_variant);
    const bool result_is_intersecting = geng::math::is_intersect(c.seg1, c.seg2);
    constexpr bool expected_is_intersecting = !std::same_as<IntersectionType, std::monostate>;

    EXPECT_EQ(result_intersect, std::get<IntersectionType>(c.expected_intersect));
    EXPECT_EQ(result_is_intersecting, expected_is_intersecting);
};
} // namespace test::intersectionsegments

TEST(math_Intersection, SegmentWithSegmentOnePointIntersection)
{
    using test::segmentintersection::SegmentIntersectionArrange;

    const std::vector<SegmentIntersectionArrange> segment_intersection_table = {
        {
            .name = "SinglePointNonCollinearSegmentsIntersection",
            .seg1 = {{1.0, 1.0}, {3.0, 5.0}},
            .seg2 = {{1.0, 5.0}, {3.0, 1.0}},
            .expected_intersect = geng::Point{2.0, 3.0},
        },
        {
            .name = "SinglePointNonCollinearSegmentIntersectionWithHorisontalSeg",
            .seg1 = {{1.0, 1.0}, {3.0, 5.0}},
            .seg2 = {{-4.0, 3.0}, {6.0, 3.0}},
            .expected_intersect = geng::Point{2.0, 3.0},
        },
        {
            .name = "SinglePointNonCollinearSegmentIntersectionWithVerticalSeg",
            .seg1 = {{1.0, 1.0}, {3.0, 5.0}},
            .seg2 = {{2.0, -2.0}, {2.0, 8.0}},
            .expected_intersect = geng::Point{2.0, 3.0},
        },
        {
            .name = "SinglePointCollinearSegmentsIntersection",
            .seg1 = {{1.0, 1.0}, {3.0, 5.0}},
            .seg2 = {{3.0, 5.0}, {7.0, 13.0}},
            .expected_intersect = geng::Point{3.0, 5.0},
        },
        {
            .name = "SinglePointNonCollinearSegmentsIntersectionOnTheEndOfOneSegment",
            .seg1 = {{1.0, 1.0}, {3.0, 5.0}},
            .seg2 = {{1.0, 6.0}, {5.0, 4.0}},
            .expected_intersect = geng::Point{3.0, 5.0},
        },
        {
            .name = "SinglePointHorisontalSegWithVerticalSegIntersectionOnTheEndOfOneSegment",
            .seg1 = {{-4.0, 3.0}, {6.0, 3.0}},
            .seg2 = {{3.0, 3.0}, {3.0, 7.0}},
            .expected_intersect = geng::Point{3.0, 3.0},
        },
        {
            .name = "SinglePointNonCollinearSegmentsIntersectionSwappedArgs",
            .seg1 = {{1.0, 5.0}, {3.0, 1.0}},
            .seg2 = {{1.0, 1.0}, {3.0, 5.0}},
            .expected_intersect = geng::Point{2.0, 3.0},
        },
    };

    test::table::run_test_table(segment_intersection_table, [](const SegmentIntersectionArrange& c){
            test::segmentintersection::compare_segment_intersection<geng::Point>(c);
            });
}

TEST(math_Intersection, SegmentWithSegmentMultiplePointIntersection)
{
    using test::segmentintersection::SegmentIntersectionArrange;

    const std::vector<SegmentIntersectionArrange> collinear_segment_intersection_table = {
        {
            .name = "MultiplePointCollinearArbitrarySegmentsIntersection",
            .seg1 = {{1.0, 1.0}, {3.0, 5.0}},
            .seg2 = {{1.0, 1.0}, {3.0, 5.0}},
            .expected_intersect = geng::Segment{{1.0, 1.0}, {3.0, 5.0}},
        },
        {
            .name = "MultiplePointCollinearVerticalSegmentsIntersection",
            .seg1 = {{3.0, -4.0}, {3.0, 9.884}},
            .seg2 = {{3.0, 5.0}, {3.0, 15.0}},
            .expected_intersect = geng::Segment{{3.0, 5.0}, {3.0, 9.884}},
        },
        {
            .name = "MultiplePointCollinearHorysontalSegmentsIntersection",
            .seg1 = {{-4.0, 3.0}, {9.884, 3.0}},
            .seg2 = {{5.0, 3.0}, {15.0, 3.0}},
            .expected_intersect = geng::Segment{{5.0, 3.0}, {9.884, 3.0}},
        },
    };

    test::table::run_test_table(collinear_segment_intersection_table, [](const SegmentIntersectionArrange& c){
            test::segmentintersection::compare_segment_intersection<geng::Segment>(c);
            });
}

TEST(math_Intersection, SegmentWithSegmentNoIntersection)
{
    using test::segmentintersection::SegmentIntersectionArrange;

    const std::vector<SegmentIntersectionArrange> segment_no_intersection_table = {
        {
            .name = "NoIntersectionWithInfiniteLineIntersectionPointNotOnAnyOfSegments",
            .seg1 = {{12.0, 9.0}, {21.0, 15.0}},
            .seg2 = {{7.0, 7.0}, {9.0, 11.0}},
            .expected_intersect = std::monostate(),
        },
        {
            .name = "NoIntersectionWithInfiniteLineIntersectionPointOnFirstSeg",
            .seg1 = {{3.0, 3.0}, {12.0, 9.0}},
            .seg2 = {{8.0, 9.0}, {10.0, 13.0}},
            .expected_intersect = std::monostate(),
        },
        {
            .name = "NoIntersectionWithInfiniteLineIntersectionPointOnSecondSeg",
            .seg1 = {{8.0, 9.0}, {10.0, 13.0}},
            .seg2 = {{3.0, 3.0}, {12.0, 9.0}},
            .expected_intersect = std::monostate(),
        },
        {
            .name = "NoIntersectionSegmentsCollinear",
            .seg1 = {{2.0, 3.0}, {4.0, 5.0}},
            .seg2 = {{6.0, 7.0}, {8.0, 9.0}},
            .expected_intersect = std::monostate(),
        },
        {
            .name = "NoIntersectionSegmentsParallel",
            .seg1 = {{2.0, 3.0}, {4.0, 5.0}},
            .seg2 = {{2.0, 4.0}, {4.0, 6.0}},
            .expected_intersect = std::monostate(),
        },
    };

    test::table::run_test_table(segment_no_intersection_table, [](const SegmentIntersectionArrange& c){
            test::segmentintersection::compare_segment_intersection<std::monostate>(c);
            });
}

TEST(math_Intersection, DegeneratedSegmentsNoIntersection)
{
    using test::segmentintersection::SegmentIntersectionArrange;

    const std::vector<SegmentIntersectionArrange> deg_seg_no_intersection_table = {
        {
            .name = "NoIntersectionFirstSegmentDegenerated",
            .seg1 = {{3.0, 9.0}, {3.0, 9.0}},
            .seg2 = {{2.0, 1.0}, {8.0, 5.0}},
            .expected_intersect = std::monostate(),
        },
        {
            .name = "NoIntersectionSecondSegmentDegenerated",
            .seg1 = {{2.0, 1.0}, {8.0, 5.0}},
            .seg2 = {{3.0, 9.0}, {3.0, 9.0}},
            .expected_intersect = std::monostate(),
        },
        {
            .name = "NoIntersectionBothSegmentsDegenerated",
            .seg1 = {{1.0, 2.0}, {1.0, 2.0}},
            .seg2 = {{3.0, 9.0}, {3.0, 9.0}},
            .expected_intersect = std::monostate(),
        },
    };

    test::table::run_test_table(deg_seg_no_intersection_table, [](const SegmentIntersectionArrange& c){
            test::segmentintersection::compare_segment_intersection<std::monostate>(c);
            });
}

TEST(math_Intersection, DegeneratedSegmentsOnePointIntersection)
{
    using test::segmentintersection::SegmentIntersectionArrange;

    const std::vector<SegmentIntersectionArrange> deg_seg_one_point_intersection_table = {
        {
            .name = "SinglePointFirstSegmentDegeneratedIntersection",
            .seg1 = {{5.0, 3.0}, {5.0, 3.0}},
            .seg2 = {{2.0, 1.0}, {8.0, 5.0}},
            .expected_intersect = geng::Point{5.0, 3.0},
        },
        {
            .name = "SinglePointSecondSegmentDegeneratedIntersection",
            .seg1 = {{2.0, 1.0}, {8.0, 5.0}},
            .seg2 = {{5.0, 3.0}, {5.0, 3.0}},
            .expected_intersect = geng::Point{5.0, 3.0},
        },
        {
            .name = "SinglePointBothSegmentsDegeneratedIntersection",
            .seg1 = {{5.0, 3.0}, {5.0, 3.0}},
            .seg2 = {{5.0, 3.0}, {5.0, 3.0}},
            .expected_intersect = geng::Point{5.0, 3.0},
        },
    };

    test::table::run_test_table(deg_seg_one_point_intersection_table, [](const SegmentIntersectionArrange& c){
            test::segmentintersection::compare_segment_intersection<geng::Point>(c);
            });
}
