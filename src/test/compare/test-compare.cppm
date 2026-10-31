module;
#include <gtest/gtest.h>
export module geotest:compare;
import gengine.types;
import gengine.compare;

TEST(Compare, IsZeroScalar)
{
    double zero = 0.0;
    EXPECT_TRUE(geng::is_zero(zero));

    // p.35
    EXPECT_TRUE(geng::is_zero(geng::EPSILON_COMPUTE / 2.5));

    EXPECT_FALSE(geng::is_zero(geng::EPSILON_COMPUTE * 2));
}

TEST(Compare, IsZeroVec)
{
    geng::Vec2 zero_vec = {0.0, 0.0};
    EXPECT_TRUE(geng::is_zero(zero_vec));

    // p.35
    geng::Vec2 zero_vec_from_esp_halfed = {geng::EPSILON_COMPUTE / 2.5, 0.0};
    EXPECT_TRUE(geng::is_zero(zero_vec_from_esp_halfed));

    geng::Vec2 zero_vec_from_esp_doubled = {geng::EPSILON_COMPUTE * 2, 0.0};
    EXPECT_FALSE(geng::is_zero(zero_vec_from_esp_doubled));
}

TEST(Compare, IsEqualScalar)
{
    double v1 = 5.000844;
    // p.35
    double v2 = v1 + geng::EPSILON_COMPUTE / 2.5;

    EXPECT_TRUE(geng::is_equal(v1, v2));
    EXPECT_TRUE(geng::is_equal(v2, v1));
}

TEST(Compare, IsWithinScalar)
{
    double min = 5.000844;
    double max = 5.000744;
    double target_val = 5.00075;

    EXPECT_TRUE(geng::is_within(target_val, min, max));
    EXPECT_TRUE(geng::is_within(target_val, max, min));
}
