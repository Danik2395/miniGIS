module;
#include <cmath>
#include <algorithm>
#include <cstdint>
export module gengine.compare.doubles;
import gengine.types.precision;

export namespace geng
{
[[nodiscard]]
int64_t quantize(double val);

[[nodiscard]]
bool is_zero(double val);

[[nodiscard]]
bool is_equal(double val1, double val2);

[[nodiscard]]
bool is_within(double val, double min, double max);
} // namespace geng

export namespace geng::compare
{
class [[nodiscard]] CacheQuantizePrecision;
} // namespace geng::compare



namespace geng
{
constexpr geng::Precision quantize_default_precision = {1e-9, 1e+9};
thread_local geng::Precision quantize_precision = quantize_default_precision;

int64_t quantize(double val)
{
    return static_cast<int64_t>(std::round(val * quantize_precision.inverted_eps));
}

bool is_zero(double val)
{
    return geng::quantize(val) == 0;
}

bool is_equal(double val1, double val2)
{
    return geng::quantize(val1) == geng::quantize(val2);
}

bool is_within(double val, double min, double max)
{
    const auto [actual_min, actual_max] = std::minmax(min, max);

    auto qval = geng::quantize(val);
    auto qmin = geng::quantize(actual_min);
    auto qmax = geng::quantize(actual_max);

    return qmin <= qval && qval <= qmax;
}
} // namespace geng

namespace geng::compare
{
class CacheQuantizePrecision
{
    geng::Precision previous_precision;

public:
    explicit CacheQuantizePrecision(geng::Precision prec)
    {
        previous_precision = quantize_precision;
        quantize_precision = prec;
    }

    CacheQuantizePrecision(const CacheQuantizePrecision&) = delete;
    CacheQuantizePrecision(CacheQuantizePrecision&&)      = delete;

    CacheQuantizePrecision& operator=(const CacheQuantizePrecision&) = delete;
    CacheQuantizePrecision& operator=(CacheQuantizePrecision&&)      = delete;

    ~CacheQuantizePrecision()
    {
        quantize_precision = previous_precision;
    }
};
} // namespace geng::compare
