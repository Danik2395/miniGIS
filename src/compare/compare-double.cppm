module;
#include <cmath>
#include <algorithm>
#include <cstdint>
export module gengine.compare.doubles;

export
namespace geng
{
    constexpr double EPSILON_COMPUTE = 1e-9;
    constexpr double EPSILON_COMPUTE_INVERTED = 1e+9;

    int64_t quantize(double val)
    {
        return static_cast<int64_t>(std::round(val * EPSILON_COMPUTE_INVERTED));
    }

    [[nodiscard]]
    bool is_zero(double val)
    {
        // нужно ли тут abs. напиши тест, чтобы узнать
        return std::abs(geng::quantize(val)) == 0;
    }

    [[nodiscard]]
    bool is_equal(double val1, double val2)
    {
        return geng::quantize(val1) == geng::quantize(val2);
    }

    [[nodiscard]]
    bool is_within(double val, double min, double max)
    {
        const auto [actual_min, actual_max] = std::minmax(min, max);

        auto qval = geng::quantize(val);
        auto qmin = geng::quantize(actual_min);
        auto qmax = geng::quantize(actual_max);

        return qmin <= qval && qval <= qmax;
    }
}
