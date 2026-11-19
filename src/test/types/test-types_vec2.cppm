module;
#include <gtest/gtest.h>
export module geotest:types_vec2;
import gengine.types;

namespace test::vec2
{
void expect_vec_eq(const geng::Vec2 vec, double x, double y)
{
    EXPECT_DOUBLE_EQ(vec.x, x);
    EXPECT_DOUBLE_EQ(vec.y, y);
}

void expect_vec_eq(const geng::Vec2 vec1, const geng::Vec2 vec2)
{
    expect_vec_eq(vec1, vec2.x, vec2.y);
}
} // namespace test::vec2

TEST(types_Vec2, ConstructorArgsFromPoints)
{
    const geng::Point p0(3.0, 2.0);
    const geng::Point p1(5.8, 5.8);
    const geng::Vec2 expected_vec(2.8, 3.8);

    const geng::Vec2 vec(p0, p1);

    test::vec2::expect_vec_eq(vec, expected_vec);
}

TEST(types_Vec2, ConstructorListFromPoints)
{
    const geng::Point p0(4.0, 3.0);
    const geng::Point p1(6.8, 6.8);
    const geng::Vec2 expected_vec(2.8, 3.8);

    const geng::Vec2 vec = {p0, p1};

    test::vec2::expect_vec_eq(vec, expected_vec);
}

TEST(types_Vec2, ConstructorListWrongSizeAssert)
{
    ASSERT_DEBUG_DEATH(std::ignore = geng::Vec2{geng::Point{}}, "must be 2 points");
}

TEST(types_Vec2, DotProduct)
{
    const geng::Vec2 v1(1.0, 2.0);
    const geng::Vec2 v2(3.0, 4.0);

    const double dot_product = v1 * v2;
    const double dot_product_swap_order = v1 * v2;

    EXPECT_DOUBLE_EQ(dot_product, 11.0);
    EXPECT_DOUBLE_EQ(dot_product_swap_order, 11.0);
}

TEST(types_Vec2, MultiplyScalar)
{
    const geng::Vec2 vec(1.0, -2.0);
    const double scalar = 3.0;

    const geng::Vec2 result_vec = vec * scalar;

    test::vec2::expect_vec_eq(result_vec, 3.0, -6.0);
}

TEST(types_Vec2, Addition)
{
    const geng::Vec2 v1(1.0, 2.0);
    const geng::Vec2 v2(3.0, 4.0);

    const geng::Vec2 result_vec = v1 + v2;

    test::vec2::expect_vec_eq(result_vec, 4.0, 6.0);
}

TEST(types_Vec2, Subtraction)
{
    const geng::Vec2 v1(5.0, 8.0);
    const geng::Vec2 v2(3.0, 4.0);

    const geng::Vec2 result_vec = v1 - v2;

     test::vec2::expect_vec_eq(result_vec, 2.0, 4.0);
}

TEST(types_Vec2, Length)
{
    const geng::Vec2 vec(3.0, 4.0);
    const double expected_length = 5.0;

    const double vec_length = vec.length();

    EXPECT_DOUBLE_EQ(vec_length, expected_length);
}

TEST(types_Vec2, Projection)
{
    const geng::Vec2 vec_projecting(2.0, 0.0);
    const geng::Vec2 vec_projected(5.0, 9.0);
    const double expected_projection = 5.0;

    const double projection = vec_projecting.projection(vec_projected);

    EXPECT_DOUBLE_EQ(projection, expected_projection);
}
