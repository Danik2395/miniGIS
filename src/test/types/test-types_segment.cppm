module;
#include <gtest/gtest.h>
export module geotest:types_segment;
import gengine.types;

TEST(types_Segment, ConstructorListFromPoints)
{
    const geng::Point p0(4.0, 3.0);
    const geng::Point p1(6.8, 6.8);
    const geng::Segment expected_seg(p0, p1);

    const geng::Segment seg = {p0, p1};

    EXPECT_EQ(seg.p0, expected_seg.p0);
    EXPECT_EQ(seg.p1, expected_seg.p1);
}

TEST(types_Segment, ConstructorListWrongSizeAssert)
{
    ASSERT_DEBUG_DEATH(std::ignore = geng::Segment{geng::Point{}}, "must be 2 points");
}

TEST(types_Segment, SegmentsEqualReturnTrue)
{
    // п.64
    const geng::Point p0(4.0, 3.0);
    const geng::Point p1(6.8, 6.8);
    const geng::Segment seg1(p0, p1);
    const geng::Segment seg2(p0, p1);

    const bool seg_equal = seg1 == seg2;

    EXPECT_TRUE(seg_equal);
}
