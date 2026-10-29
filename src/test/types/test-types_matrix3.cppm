module;
#include <gtest/gtest.h>
export module geotest:types_matrix3;
import gengine.types;

TEST(Matrix3, Constructors)
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
