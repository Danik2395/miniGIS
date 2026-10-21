module;
#include <gtest/gtest.h>
export module geotest:types;
import gengine.types;

TEST(TypesConstructors, PointConstructor)
{
    double x = 1, y = 5;

    geng::Point point_default;
    geng::Point point_args(x, y);
    geng::Point point_list = {x, y};
    geng::Point point_point(point_args);
    geng::Point point_point_list = {point_args};

    EXPECT_DOUBLE_EQ(point_default.x, 0);
    EXPECT_DOUBLE_EQ(point_default.y, 0);

    EXPECT_DOUBLE_EQ(point_args.x, x);
    EXPECT_DOUBLE_EQ(point_args.y, y);

    EXPECT_DOUBLE_EQ(point_list.x, x);
    EXPECT_DOUBLE_EQ(point_list.y, y);

    EXPECT_DOUBLE_EQ(point_point.x, x);
    EXPECT_DOUBLE_EQ(point_point.y, y);

    EXPECT_DOUBLE_EQ(point_point_list.x, x);
    EXPECT_DOUBLE_EQ(point_point_list.y, y);
}

TEST(TypesConstructors, Vec2Constructor)
{
    double x = 1, y = 5;

    geng::Point p0(0, 0);
    geng::Point p1(x, y);

    geng::Vec2 vec_default;
    geng::Vec2 vec_args(x, y);
    geng::Vec2 vec_list = {x, y};
    geng::Vec2 vec_vec(vec_args);
    geng::Vec2 vec_vec_list = {vec_args};
    geng::Vec2 vec_point(p0, p1);
    geng::Vec2 vec_point_list{p0, p1};

    EXPECT_DOUBLE_EQ(vec_default.x, 0);
    EXPECT_DOUBLE_EQ(vec_default.y, 0);

    EXPECT_DOUBLE_EQ(vec_args.x, x);
    EXPECT_DOUBLE_EQ(vec_args.y, y);

    EXPECT_DOUBLE_EQ(vec_list.x, x);
    EXPECT_DOUBLE_EQ(vec_list.y, y);

    EXPECT_DOUBLE_EQ(vec_vec.x, x);
    EXPECT_DOUBLE_EQ(vec_vec.y, y);

    EXPECT_DOUBLE_EQ(vec_vec_list.x, x);
    EXPECT_DOUBLE_EQ(vec_vec_list.y, y);
}

TEST(TypesConstructors, Matrix3Constructor)
{
    double m0 = 1, m1 = 2, m2 = 3;
    double m3 = 4, m4 = 5, m5 = 6;
    double m6 = 7, m7 = 8, m8 = 9;

    geng::Matrix3 matrix_default;
    geng::Matrix3 matrix_args(m0, m1, m2, m3, m4, m5, m6, m7, m8);
    geng::Matrix3 matrix_list = {m0, m1, m2, m3, m4, m5, m6, m7, m8};
    geng::Matrix3 matrix_matrix(matrix_args);
    geng::Matrix3 matrix_matrix_list = {matrix_args};
    geng::Matrix3 matrix_full(m0);
    geng::Matrix3 matrix_diagonal(m0, geng::Matrix3::InitType::Diagonal);

    geng::Vec2 vec0(1, 4);
    geng::Vec2 vec1(2, 5);
    geng::Vec2 vec2(3, 6);
    geng::Matrix3 matrix_vec(vec0, vec1, vec2);
    geng::Matrix3 matrix_vec_list = {vec0, vec1, vec2};

    const auto expect_matrix = [](const geng::Matrix3& matrix,
                                  double v0, double v1, double v2,
                                  double v3, double v4, double v5,
                                  double v6, double v7, double v8)
    {
        EXPECT_DOUBLE_EQ((matrix[0, 0]), v0);
        EXPECT_DOUBLE_EQ(matrix[1], v1);
        EXPECT_DOUBLE_EQ(matrix[2], v2);
        EXPECT_DOUBLE_EQ(matrix[3], v3);
        EXPECT_DOUBLE_EQ(matrix[4], v4);
        EXPECT_DOUBLE_EQ(matrix[5], v5);
        EXPECT_DOUBLE_EQ(matrix[6], v6);
        EXPECT_DOUBLE_EQ(matrix[7], v7);
        EXPECT_DOUBLE_EQ(matrix[8], v8);
    };

    expect_matrix(matrix_default, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    expect_matrix(matrix_args, m0, m1, m2, m3, m4, m5, m6, m7, m8);
    expect_matrix(matrix_list, m0, m1, m2, m3, m4, m5, m6, m7, m8);
    expect_matrix(matrix_matrix, m0, m1, m2, m3, m4, m5, m6, m7, m8);
    expect_matrix(matrix_matrix_list, m0, m1, m2, m3, m4, m5, m6, m7, m8);

    expect_matrix(matrix_full, m0, m0, m0, m0, m0, m0, m0, m0, m0);
    expect_matrix(matrix_diagonal, m0, 0, 0, 0, m0, 0, 0, 0, m0);

    expect_matrix(matrix_vec, 1, 2, 3,
                              4, 5, 6,
                              0, 0, 1);

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
    geng::Segment segment_args(p0, p1);
    geng::Segment segment_list = {p0, p1};

    EXPECT_DOUBLE_EQ(segment_default.p0.x, 0);
    EXPECT_DOUBLE_EQ(segment_default.p0.y, 0);
    EXPECT_DOUBLE_EQ(segment_default.p1.x, 0);
    EXPECT_DOUBLE_EQ(segment_default.p1.y, 0);

    EXPECT_DOUBLE_EQ(segment_args.p0.x, 0);
    EXPECT_DOUBLE_EQ(segment_args.p0.y, 0);
    EXPECT_DOUBLE_EQ(segment_args.p1.x, 1);
    EXPECT_DOUBLE_EQ(segment_args.p1.y, 5);

    EXPECT_DOUBLE_EQ(segment_list.p0.x, 0);
    EXPECT_DOUBLE_EQ(segment_list.p0.y, 0);
    EXPECT_DOUBLE_EQ(segment_list.p1.x, 1);
    EXPECT_DOUBLE_EQ(segment_list.p1.y, 5);
}
