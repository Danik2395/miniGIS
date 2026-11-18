module;
#include <cstdint>
#include <string>
#include <gtest/gtest.h>
export module geotest:compare;
import gengine.types;
import gengine.compare;

namespace test::quantize
{
struct [[nodiscard]] QuantizeAssert
{
    const std::string name;
    const double raw_num;
    const int64_t expected_quantized;
};
} // test::quantize

TEST(compare_Quantize, ValidNumbers)
{
    using test::quantize::QuantizeAssert;

    const std::vector<QuantizeAssert> cases = {
        {"Positive",             59.123456,     59123456000},
        {"QuantizeToUpperDigit", 59.9876543215, 59987654322},
        {"QuantizeToLowerDigit", 59.9876543214, 59987654321},
        {"Negative",            -74.9876,      -74987600000},
    };

    for (const auto& c : cases) {
        SCOPED_TRACE(testing::Message() << "Case: " << c.name);

        const int64_t actual_quantize = geng::quantize(c.raw_num);

        EXPECT_EQ(c.expected_quantized, actual_quantize);
    }
}

TEST(compare_Predicates, IsZeroScalarReturnTrue)
{
    const double zero_pos = 0.0;

    const bool result_zero_pos = geng::is_zero(zero_pos);

    EXPECT_TRUE(result_zero_pos);
}

TEST(compare_Predicates, IsZeroScalarReturnFalse)
{
    const double non_zero = 1.0;

    const bool result_non_zero = geng::is_zero(non_zero);

    EXPECT_FALSE(result_non_zero);
}

TEST(compare_Predicates, IsZeroVecReturnTrue)
{
    const geng::Vec2 zero_vec = {0.0, 0.0};

    const bool result_zero_vec = geng::is_zero(zero_vec);

    EXPECT_TRUE(result_zero_vec);
}

TEST(compare_Predicates, IsZeroVecReturnFalse)
{
    const geng::Vec2 non_zero_vec = {1.0, 1.0};

    const bool result_non_zero_vec = geng::is_zero(non_zero_vec);

    EXPECT_FALSE(result_non_zero_vec);
}

TEST(compare_Predicates, IsEqualScalarReturnTrueActualEqual)
{
    const double v1 = 5.005844;

    const bool result_equal = geng::is_equal(v1, v1);

    EXPECT_TRUE(result_equal);
}

TEST(compare_Predicates, IsEqualScalarReturnTrueDifferentDigitsAfterDefaultPrecision)
{
    const double v1 = 5.000844 + 0.123e-9;
    const double v2 = 5.000844 + 0.321e-9;

    const bool result_equal = geng::is_equal(v1, v2);

    EXPECT_TRUE(result_equal);
}

TEST(compare_Predicates, IsEqualScalarReturnFalse)
{
    const double v1 = 5.000844000;
    const double v2 = 5.000844005;

    const bool result_not_equal = geng::is_equal(v1, v2);

    EXPECT_FALSE(result_not_equal);
}

TEST(compare_Predicates, IsWithinScalarReturnTrueCorrectOrder)
{
    double min = 5.000744;
    double max = 5.000844;
    double val_within = 5.00075;

    bool result_within = geng::is_within(val_within, min, max);

    EXPECT_TRUE(result_within);
}

TEST(compare_Predicates, IsWithinScalarReturnTrueSwapOrder)
{
    double min = 5.000744;
    double max = 5.000844;
    double val_within = 5.00075;

    bool result_within = geng::is_within(val_within, max, min);

    EXPECT_TRUE(result_within);
}

TEST(compare_Predicates, IsWithinScalarReturnFalseCorrectOrderValGreater)
{
    double min = 5.000744;
    double max = 5.000844;
    double val_not_within = 6.0;

    bool result_not_within = geng::is_within(val_not_within, min, max);

    EXPECT_FALSE(result_not_within);
}

TEST(compare_Predicates, IsWithinScalarReturnFalseSwapOrderValLess)
{
    double min = 5.000744;
    double max = 5.000844;
    double val_not_within = 3.0;

    bool result_not_within = geng::is_within(val_not_within, max, min);

    EXPECT_FALSE(result_not_within);
}

TEST(compare_Predicates, CustomQuantizePrecisionIsEqualScalar)
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
