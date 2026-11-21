module;
#include <vector>
#include <gtest/gtest.h>
export module geotest:math_orientation;
import :table;
import gengine.types;
import gengine.math;

TEST(math_Orientation, FuncOverloadsEqual)
{
    const geng::Point p(4.3, 2.1);
    const geng::Point seg_p0(3.9, 4.1);
    const geng::Point seg_p1(10.2, 15.4);
    const geng::Segment seg(seg_p0, seg_p1);

    const auto orient_points = geng::math::orientation(p, seg_p0, seg_p1);
    const auto orient_seg = geng::math::orientation(p, seg);

    EXPECT_EQ(orient_points, orient_seg);
}

namespace test::orientation
{
struct OrientationArrange
{
    const char* name;
    geng::Point p;
    geng::Point seg_p0;
    geng::Point seg_p1;
    geng::math::Orientation expected_orient;
};
} // namespace test::orientation

TEST(math_Orientation, ValidPoints)
{
    using test::orientation::OrientationArrange;
    using Orient = geng::math::Orientation;

    const std::vector<OrientationArrange> orientation_table = {
        {
            .name = "PointAndSegmentPointPointToRight",
            .p = {9.8, 3.2},
            .seg_p0 = {1.0, 3.0},
            .seg_p1 = {5.0, 7.0},
            .expected_orient = Orient::RIGHT,
        },
        {
            .name = "PointAndSegmentPointToLeft",
            .p = {-1.4, 5.4},
            .seg_p0 = {1.0, 3.0},
            .seg_p1 = {5.0, 7.0},
            .expected_orient = Orient::LEFT,
        },
        {
            .name = "PointAndSegmentPointCollinearOnSeg",
            .p = {3.0, 5.0},
            .seg_p0 = {1.0, 3.0},
            .seg_p1 = {5.0, 7.0},
            .expected_orient = Orient::COLLINEAR,
        },
        {
            .name = "PointAndSegmentCollinearNotOnSeg",
            .p = {6.0, 8.0},
            .seg_p0 = {1.0, 3.0},
            .seg_p1 = {5.0, 7.0},
            .expected_orient = Orient::COLLINEAR,
        },
    };

    test::table::run_test_table(orientation_table, [](const OrientationArrange& c){
            const auto result_orient = geng::math::orientation(c.p, c.seg_p0, c.seg_p1);

            EXPECT_EQ(result_orient, c.expected_orient);
            });
}
