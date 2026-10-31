module;
#include "gtest/gtest.h"
#include <gtest/gtest.h>
export module geotest:types_matrix3;
import gengine.types;

void expect_matrix(const geng::Matrix3& mtx,
                   double v0, double v1, double v2,
                   double v3, double v4, double v5,
                   double v6, double v7, double v8)
{
    EXPECT_DOUBLE_EQ(mtx.m[0], v0);
    EXPECT_DOUBLE_EQ(mtx.m[1], v1);
    EXPECT_DOUBLE_EQ(mtx.m[2], v2);
    EXPECT_DOUBLE_EQ(mtx.m[3], v3);
    EXPECT_DOUBLE_EQ(mtx.m[4], v4);
    EXPECT_DOUBLE_EQ(mtx.m[5], v5);
    EXPECT_DOUBLE_EQ(mtx.m[6], v6);
    EXPECT_DOUBLE_EQ(mtx.m[7], v7);
    EXPECT_DOUBLE_EQ(mtx.m[8], v8);
};

void expect_matrix(const geng::Matrix3& mtx, const geng::Matrix3& other_mtx)
{
    expect_matrix(mtx,
                  other_mtx.m[0], other_mtx.m[1], other_mtx.m[2],
                  other_mtx.m[3], other_mtx.m[4], other_mtx.m[5],
                  other_mtx.m[6], other_mtx.m[7], other_mtx.m[8]);
}

TEST(Matrix3, Constructors)
{
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

TEST(Matrix3, MultiplyMatrix)
{
    geng::Matrix3 mtx1 = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8
    };

    geng::Matrix3 mtx2 = {
        8, 7, 6,
        5, 4, 3,
        2, 1, 0
    };

    geng::Matrix3 result_multiplication_mtx1_mtx2 = {
         9,  6,  3,
        54, 42, 30,
        99, 78, 57
    };
    expect_matrix(mtx1 * mtx2, result_multiplication_mtx1_mtx2);

    geng::Matrix3 result_multiplication_mtx2_mtx1 = {
        57, 78, 99,
        30, 42, 54,
         3,  6,  9
    };
    expect_matrix(mtx2 * mtx1, result_multiplication_mtx2_mtx1);
}

TEST(Matrix3, MultiplyVec)
{
    geng::Matrix3 mtx = {
        4, 0, 5,
        0, 4, 3,
        0, 0, 1
    };

    geng::Vec2 vec = {5, 8};

    geng::Vec2 result_vec = mtx * vec;
    geng::Vec2 result_vec_expected = {20 + 5, 32 + 3};

    EXPECT_DOUBLE_EQ(result_vec.x, result_vec_expected.x);
    EXPECT_DOUBLE_EQ(result_vec.y, result_vec_expected.y);
}

TEST(Matrix3, MultiplyScalar)
{
    geng::Matrix3 mtx = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8
    };

    double scalar = 3;

    geng::Matrix3 result_mtx = {
         0,  3,  6,
         9, 12, 15,
        18, 21, 24
    };

    expect_matrix(mtx * scalar, result_mtx);
}

TEST(Matrix3, Addition)
{
    geng::Matrix3 mtx1 = geng::Matrix3::Full(5);
    geng::Matrix3 mtx2 = geng::Matrix3::Full(1);

    geng::Matrix3 result_mtx = geng::Matrix3::Full(6);

    expect_matrix(mtx1 + mtx2, result_mtx);
}

TEST(Matrix3, Substraction)
{
    geng::Matrix3 mtx1 = geng::Matrix3::Full(5);
    geng::Matrix3 mtx2 = geng::Matrix3::Full(1);

    geng::Matrix3 result_mtx = geng::Matrix3::Full(4);

    expect_matrix(mtx1 - mtx2, result_mtx);
}


TEST(Matrix3, Determinant)
{
    geng::Matrix3 mtx = {
        1, 1, 2,
        3, 4, 5,
        6, 7, 8
    };

    EXPECT_DOUBLE_EQ(mtx.det(), -3);
}
