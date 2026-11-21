module;
#include <gtest/gtest.h>
export module geotest:math_vectorops;
import gengine.types;
import gengine.math;

TEST(math_ProjCoeff, ValidVectors)
{
    const geng::Vec2 vec_projecting(2.648, 0.0);
    const geng::Vec2 vec_projected(1.324, 9.8);
    const double expected_coeff = 0.5;

    const double result_coeff = geng::math::proj_coeff(vec_projecting, vec_projected);

    EXPECT_DOUBLE_EQ(expected_coeff, result_coeff);
}

TEST(math_ProjCoeff, DegeneratedProjectingVectorAssert)
{
    const geng::Vec2 vec_projecting(0.0, 0.0);
    const geng::Vec2 vec_projected(2.648, 0.0);

    ASSERT_DEBUG_DEATH(std::ignore = geng::math::proj_coeff(vec_projecting, vec_projected), "projecting must be non-zero");
}

TEST(math_CrossProduct, ValidVectors)
{
    const geng::Vec2 vec1(2.648, 4.0);
    const geng::Vec2 vec2(1.324, 9.8);
    const double expected_cross = 20.6544;

    const double result_cross = geng::math::cross(vec1, vec2);

    EXPECT_DOUBLE_EQ(result_cross, expected_cross);
}
