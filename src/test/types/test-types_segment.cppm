module;
#include <gtest/gtest.h>
export module geotest:types_segment;
import gengine.types;

TEST(Segment, Constructors)
{
    double x = 1, y = 5;

    geng::Point p0(0, 0);
    geng::Point p1(x, y);

    geng::Segment segment_default;
    EXPECT_DOUBLE_EQ(segment_default.p0.x, 0);
    EXPECT_DOUBLE_EQ(segment_default.p0.y, 0);
    EXPECT_DOUBLE_EQ(segment_default.p1.x, 0);
    EXPECT_DOUBLE_EQ(segment_default.p1.y, 0);

    geng::Segment segment_args(p0, p1);
    EXPECT_DOUBLE_EQ(segment_args.p0.x, 0);
    EXPECT_DOUBLE_EQ(segment_args.p0.y, 0);
    EXPECT_DOUBLE_EQ(segment_args.p1.x, 1);
    EXPECT_DOUBLE_EQ(segment_args.p1.y, 5);

    geng::Segment segment_list = {p0, p1};
    EXPECT_DOUBLE_EQ(segment_list.p0.x, 0);
    EXPECT_DOUBLE_EQ(segment_list.p0.y, 0);
    EXPECT_DOUBLE_EQ(segment_list.p1.x, 1);
    EXPECT_DOUBLE_EQ(segment_list.p1.y, 5);
}
