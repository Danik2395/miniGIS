module;
#include <cassert>
#include <cmath>
#include <cstdint>
#include <vector>
#include <compare>
export module gengine.types:primitives;

export
namespace geng
{
    constexpr double EPSILON_COMPUTE = 1e-9;

    struct Point
    {
        double x, y;

        std::strong_ordering operator<=>(const Point& other_point) const
        {
            assert(!std::isnan(this->x) && !std::isnan(other_point.x) &&
                   !std::isnan(this->y) && !std::isnan(other_point.y) &&
                    "operator<=>: NaN is not allowed.");

            if (auto cmp = quantize_(this->x) <=> quantize_(other_point.x);
                    cmp != 0)
                return cmp;

            return quantize_(this->y) <=> quantize_(other_point.y);
        }

        bool operator==(const Point& other_point) const
        {
            return (*this <=> other_point) == 0;
        }

    private:
        int64_t quantize_(double v) const
        {
            return static_cast<int64_t>(std::round(v / EPSILON_COMPUTE));
        }
    };

    struct LineString
    {
        std::vector<Point> points;
    };

    struct Poligon
    {
        std::vector<Point> outer;
        std::vector<std::vector<Point>> inner;
    };
}
