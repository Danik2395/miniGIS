module;
#include <gtest/gtest.h>
export module geotest:types_segment;
import gengine.types;

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
