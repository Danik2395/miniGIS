module;
#include <gtest/gtest.h>
export module geotest:types_vec2;
import gengine.types;

TEST(Vec2, Constructors)
{
    double x = 1, y = 5;

    geng::Point p0(0, 0);
    geng::Point p1(x, y);

    geng::Vec2 vec_default;
    EXPECT_DOUBLE_EQ(vec_default.x, 0);
    EXPECT_DOUBLE_EQ(vec_default.y, 0);

    geng::Vec2 vec_args(x, y);
    EXPECT_DOUBLE_EQ(vec_args.x, x);
    EXPECT_DOUBLE_EQ(vec_args.y, y);

    geng::Vec2 vec_list = {x, y};
    EXPECT_DOUBLE_EQ(vec_list.x, x);
    EXPECT_DOUBLE_EQ(vec_list.y, y);

    geng::Vec2 vec_vec(vec_args);
    EXPECT_DOUBLE_EQ(vec_vec.x, x);
    EXPECT_DOUBLE_EQ(vec_vec.y, y);

    geng::Vec2 vec_vec_list = {vec_args};
    EXPECT_DOUBLE_EQ(vec_vec_list.x, x);
    EXPECT_DOUBLE_EQ(vec_vec_list.y, y);

    geng::Vec2 vec_point(p0, p1);
    EXPECT_DOUBLE_EQ(vec_point.x, x);
    EXPECT_DOUBLE_EQ(vec_point.y, y);

    geng::Vec2 vec_point_list = {p0, p1};
    EXPECT_DOUBLE_EQ(vec_point_list.x, x);
    EXPECT_DOUBLE_EQ(vec_point_list.y, y);
}
