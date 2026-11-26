module;
#include <gtest/gtest.h>
export module geotest:types_matrix3;
import gengine.types;

namespace test::matrix3
{
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
} // namespace test::matrix3

TEST(types_Matrix3, ConstructorFull)
{
    const double v = 9.4;

    const auto full_mtx = geng::Matrix3::Full(v);

    test::matrix3::expect_matrix(full_mtx, v, v, v, v, v, v, v, v, v);
}

TEST(types_Matrix3, ConstructorDiagonal)
{
    const double v = 9.4;

    const auto diagonal_mtx = geng::Matrix3::Diagonal(v);

    test::matrix3::expect_matrix(diagonal_mtx,
            v, 0, 0,
            0, v, 0,
            0, 0, v
            );
}

TEST(types_Matrix3, ConstructorListFromScalar)
{
    const double v0 = 0.0, v1 = 1.4, v2 = 2.3;
    const double v3 = 3.3, v4 = 4.3, v5 = 5.2;
    const double v6 = 6.1, v7 = 7.4, v8 = 8.4;

    const geng::Matrix3 mtx = {
        v0, v1, v2,
        v3, v4, v5,
        v6, v7, v8,
    };

    test::matrix3::expect_matrix(mtx, v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

TEST(types_Matrix3, ConstructorListFromScalarWrongSizeAssert)
{
    const double v = 4.9;

    EXPECT_DEBUG_DEATH(std::ignore = geng::Matrix3{v}, "must be 9 values");
}

TEST(types_Matrix3, ConstructorArgsFromVec2)
{
    const double v0 = 2.2, v1 = 0.4, v2 = 1.2;
    const double v3 = 3.3, v4 = 6.5, v5 = 3.2;
    const double v6 = 0.0, v7 = 0.0, v8 = 1.0;
    const geng::Vec2 vec1(v0, v3), vec2(v1, v4), vec3(v2, v5);

    const geng::Matrix3 mtx(vec1, vec2, vec3);

    test::matrix3::expect_matrix(mtx, v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

TEST(types_Matrix3, ConstructorListFromVec2)
{
    const double v0 = 4.2, v1 = 1.4, v2 = 0.2;
    const double v3 = 1.3, v4 = 7.5, v5 = 2.2;
    const double v6 = 0.0, v7 = 0.0, v8 = 1.0;
    const geng::Vec2 vec1(v0, v3), vec2(v1, v4), vec3(v2, v5);

    const geng::Matrix3 mtx = {vec1, vec2, vec3};

    test::matrix3::expect_matrix(mtx, v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

TEST(types_Matrix3, ConstructorListFromVec2WrongSizeAssert)
{
    const geng::Vec2 vec1;
    const geng::Vec2 vec2;
    const geng::Vec2 vec3;
    const geng::Vec2 vec4;

    EXPECT_DEBUG_DEATH((std::ignore = geng::Matrix3{vec1, vec2, vec3, vec4}), "too many arguments");
}

TEST(types_Matrix3, RandomAccessWithTwoArguments)
{
    const double v0 = 2.0, v1 = 3.4, v2 = 3.3;
    const double v3 = 1.3, v4 = 3.4, v5 = 6.2;
    const double v6 = 5.1, v7 = 6.4, v8 = 6.6;
    geng::Matrix3 mtx = {
        v0, v1, v2,
        v3, v4, v5,
        v6, v7, v8,
    };

    const double access_value = mtx[1, 2];

    EXPECT_DOUBLE_EQ(v5, access_value);
}



TEST(types_Matrix3, MultiplyMatrixOnMatrix)
{
    const geng::Matrix3 mtx1 = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
    };
    const geng::Matrix3 mtx2 = {
        8, 7, 6,
        5, 4, 3,
        2, 1, 0,
    };
    const geng::Matrix3 expected_mtx = {
         9,  6,  3,
        54, 42, 30,
        99, 78, 57
    };

    const geng::Matrix3 result_mtx = mtx1 * mtx2;

    test::matrix3::expect_matrix(result_mtx, expected_mtx);
}

TEST(types_Matrix3, MultiplyVec)
{
    const geng::Matrix3 mtx = {
        4, 0, 5,
        0, 4, 3,
        0, 0, 1
    };
    const geng::Vec2 vec = {5, 8};
    const geng::Vec2 vec_expected = {20 + 5, 32 + 3};

    const geng::Vec2 result_vec = mtx * vec;

    EXPECT_DOUBLE_EQ(result_vec.x, vec_expected.x);
    EXPECT_DOUBLE_EQ(result_vec.y, vec_expected.y);
}

TEST(types_Matrix3, MultiplyPoint)
{
    const geng::Matrix3 mtx = {
        4, 0, 5,
        0, 4, 3,
        0, 0, 1
    };
    const geng::Point point = {5, 8};
    const geng::Point point_expected = {20 + 5, 32 + 3};

    const geng::Point result_point = mtx * point;

    EXPECT_EQ(point_expected, result_point);
}

TEST(types_Matrix3, MultiplyScalar)
{
    const geng::Matrix3 mtx = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8
    };
    const double scalar = 3;
    const geng::Matrix3 expected_mtx = {
         0,  3,  6,
         9, 12, 15,
        18, 21, 24
    };

    const geng::Matrix3 result_mtx = mtx * scalar;

    test::matrix3::expect_matrix(result_mtx, expected_mtx);
}

TEST(types_Matrix3, Addition)
{
    const auto mtx1 = geng::Matrix3::Full(5);
    const auto mtx2 = geng::Matrix3::Full(1);
    const auto expected_mtx = geng::Matrix3::Full(6);

    const geng::Matrix3 result_mtx = mtx1 + mtx2;

    test::matrix3::expect_matrix(result_mtx, expected_mtx);
}

TEST(types_Matrix3, Substraction)
{
    const auto mtx1 = geng::Matrix3::Full(5);
    const auto mtx2 = geng::Matrix3::Full(1);
    const auto expected_mtx = geng::Matrix3::Full(4);

    const geng::Matrix3 result_mtx = mtx1 - mtx2;

    test::matrix3::expect_matrix(result_mtx, expected_mtx);
}


TEST(types_Matrix3, Determinant)
{
    const geng::Matrix3 mtx = {
        1, 1, 2,
        3, 4, 5,
        6, 7, 8
    };
    const double expected_det = -3;

    const double result_det = mtx.det();

    EXPECT_DOUBLE_EQ(result_det, expected_det);
}

TEST(types_Matrix3, Minor)
{
    const geng::Matrix3 mtx = {
        1, 1, 2,
        3, 4, 5,
        6, 7, 8
    };

    const double expected_minor00 = -3.0;
    const double expected_minor01 = -6.0;
    const double expected_minor02 = -3.0;
    const double expected_minor10 = -6.0;
    const double expected_minor11 = -4.0;
    const double expected_minor12 = 1.0;
    const double expected_minor20 = -3.0;
    const double expected_minor21 = -1.0;
    const double expected_minor22 = 1.0;

    const double result_minor00 = mtx.minor(0, 0);
    const double result_minor01 = mtx.minor(0, 1);
    const double result_minor02 = mtx.minor(0, 2);
    const double result_minor10 = mtx.minor(1, 0);
    const double result_minor11 = mtx.minor(1, 1);
    const double result_minor12 = mtx.minor(1, 2);
    const double result_minor20 = mtx.minor(2, 0);
    const double result_minor21 = mtx.minor(2, 1);
    const double result_minor22 = mtx.minor(2, 2);

    EXPECT_DOUBLE_EQ(result_minor00, expected_minor00);
    EXPECT_DOUBLE_EQ(result_minor01, expected_minor01);
    EXPECT_DOUBLE_EQ(result_minor02, expected_minor02);
    EXPECT_DOUBLE_EQ(result_minor10, expected_minor10);
    EXPECT_DOUBLE_EQ(result_minor11, expected_minor11);
    EXPECT_DOUBLE_EQ(result_minor12, expected_minor12);
    EXPECT_DOUBLE_EQ(result_minor20, expected_minor20);
    EXPECT_DOUBLE_EQ(result_minor21, expected_minor21);
    EXPECT_DOUBLE_EQ(result_minor22, expected_minor22);
}

TEST(types_Matrix3, Transpose)
{
    const geng::Matrix3 mtx = {
        1, 1, 2,
        3, 4, 5,
        6, 7, 8
    };
    const geng::Matrix3 expected_transposed = {
        1, 3, 6,
        1, 4, 7,
        2, 5, 8,
    };

    const geng::Matrix3 result_transposed = mtx.transposed();

    test::matrix3::expect_matrix(result_transposed, expected_transposed);
}


TEST(types_Matrix3, Inverse)
{
    const geng::Matrix3 mtx = {
        1, 1, 2,
        3, 4, 5,
        6, 7, 8
    };
    const geng::Matrix3 expected_inverse = {
         1.0, -2.0,      1.0,
        -2.0,  4.0/3.0, -1.0/3,
         1.0,  1.0/3.0, -1.0/3,
    };

    const geng::Matrix3 result_inverse = mtx.inverse();

    test::matrix3::expect_matrix(result_inverse, expected_inverse);
}

TEST(types_Matrix3, InverseZeroDeterminantAssert)
{
    const geng::Matrix3 mtx = {
        1, 1, 2,
        0, 0, 0,
        6, 7, 8
    };

    EXPECT_DEBUG_DEATH(std::ignore = mtx.inverse(), "determinant must be non-zero");
}
