module;
#include <gtest/gtest.h>
export module geotest:compare;
import gengine.types;
import gengine.compare;

TEST(Compare, IsZeroScalar)
{
    double zero = 0.0;
    EXPECT_TRUE(geng::is_zero(zero));
}

TEST(Compare, IsZeroVec)
{
    geng::Vec2 zero_vec = {0.0, 0.0};
    EXPECT_TRUE(geng::is_zero(zero_vec));
}

TEST(Compare, IsEqualScalar)
{
    double v1 = 5.000844;

    EXPECT_TRUE(geng::is_equal(v1, v1));

    double v2 = v1 + 1e-10;
    EXPECT_TRUE(geng::is_equal(v1, v2));
}

TEST(Compare, IsWithinScalar)
{
    double min = 5.000844;
    double max = 5.000744;
    double target_val = 5.00075;

    EXPECT_TRUE(geng::is_within(target_val, min, max));
    EXPECT_TRUE(geng::is_within(target_val, max, min));
}

TEST(Compare, CustomQuantizePrecisionIsEqualScalar)
{
    double v1 = 5.000844;
    double v2 = 5.000811;
    double v3 = 5.000899;

    {
        auto q_prec1 = geng::compare::CacheQuantizePrecision({1e-4, 1e+4});

        EXPECT_TRUE(geng::is_equal(v1, v2));
        EXPECT_FALSE(geng::is_equal(v1, v3));

        auto q_prec2 = geng::compare::CacheQuantizePrecision({1e-3, 1e+3});

        EXPECT_TRUE(geng::is_equal(v1, v2));
        EXPECT_TRUE(geng::is_equal(v1, v3));
    }

    EXPECT_FALSE(geng::is_equal(v1, v2));
    EXPECT_FALSE(geng::is_equal(v1, v3));
}
