module;
#include <gtest/gtest.h>
export module geotest:types;
import gengine.types;

TEST(TypesConstructors, PointConstructor)
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

TEST(TypesConstructors, Vec2Constructor)
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

TEST(TypesConstructors, Matrix3Constructor)
{
    const auto expect_matrix = [](const geng::Matrix3& matrix,
                                  double v0, double v1, double v2,
                                  double v3, double v4, double v5,
                                  double v6, double v7, double v8)
    {
        EXPECT_DOUBLE_EQ(matrix.m[0], v0);
        EXPECT_DOUBLE_EQ(matrix.m[1], v1);
        EXPECT_DOUBLE_EQ(matrix.m[2], v2);
        EXPECT_DOUBLE_EQ(matrix.m[3], v3);
        EXPECT_DOUBLE_EQ(matrix.m[4], v4);
        EXPECT_DOUBLE_EQ(matrix.m[5], v5);
        EXPECT_DOUBLE_EQ(matrix.m[6], v6);
        EXPECT_DOUBLE_EQ(matrix.m[7], v7);
        EXPECT_DOUBLE_EQ(matrix.m[8], v8);
    };

    double m0 = 0, m1 = 1, m2 = 2;
    double m3 = 3, m4 = 4, m5 = 5;
    double m6 = 6, m7 = 7, m8 = 8;

    geng::Matrix3 matrix_default;
    expect_matrix(matrix_default, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    geng::Matrix3 matrix_args(m0, m1, m2, m3, m4, m5, m6, m7, m8);
    expect_matrix(matrix_args, m0, m1, m2, m3, m4, m5, m6, m7, m8);

    geng::Matrix3 matrix_list = {m0, m1, m2, m3, m4, m5, m6, m7, m8};
    expect_matrix(matrix_list, m0, m1, m2, m3, m4, m5, m6, m7, m8);

    geng::Matrix3 matrix_matrix(matrix_args);
    expect_matrix(matrix_matrix, m0, m1, m2, m3, m4, m5, m6, m7, m8);

    geng::Matrix3 matrix_matrix_list = {matrix_args};
    expect_matrix(matrix_matrix_list, m0, m1, m2, m3, m4, m5, m6, m7, m8);

    geng::Matrix3 matrix_full = geng::Matrix3::Full(m0);
    expect_matrix(matrix_full, m0, m0, m0, m0, m0, m0, m0, m0, m0);

    geng::Matrix3 matrix_diagonal = geng::Matrix3::Diagonal(m0);
    expect_matrix(matrix_diagonal, m0, 0, 0, 0, m0, 0, 0, 0, m0);

    geng::Vec2 vec1(1, 4);
    geng::Vec2 vec2(2, 5);
    geng::Vec2 vec3(3, 6);

    geng::Matrix3 matrix_vec(vec1, vec2, vec3);
    expect_matrix(matrix_vec, 1, 2, 3,
                              4, 5, 6,
                              0, 0, 1);

    geng::Matrix3 matrix_vec_list = {vec1, vec2, vec3};
    expect_matrix(matrix_vec_list, 1, 2, 3,
                                   4, 5, 6,
                                   0, 0, 1);
}

TEST(TypesConstructors, SegmentConstructor)
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
