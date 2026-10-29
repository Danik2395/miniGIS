module;
#include <gtest/gtest.h>
export module geotest:types_point;
import gengine.types;

TEST(Point, Constructors)
{
    double x = 1, y = 5;

    geng::Point point_default;
    EXPECT_DOUBLE_EQ(point_default.x, 0);
    EXPECT_DOUBLE_EQ(point_default.y, 0);

    geng::Point point_args(x, y);
    EXPECT_DOUBLE_EQ(point_args.x, x);
    EXPECT_DOUBLE_EQ(point_args.y, y);

    geng::Point point_list = {x, y};
    EXPECT_DOUBLE_EQ(point_list.x, x);
    EXPECT_DOUBLE_EQ(point_list.y, y);

    geng::Point point_point(point_args);
    EXPECT_DOUBLE_EQ(point_point.x, x);
    EXPECT_DOUBLE_EQ(point_point.y, y);

    geng::Point point_point_list = {point_args};
    EXPECT_DOUBLE_EQ(point_point_list.x, x);
    EXPECT_DOUBLE_EQ(point_point_list.y, y);
}
