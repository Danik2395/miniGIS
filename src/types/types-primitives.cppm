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

    struct Vec2;

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

        static Point max(Point p0, Point p1)
        {
            return p0 > p1 ? p0 : p1;
        }

        static Point min(Point p0, Point p1)
        {
            return p0 < p1 ? p0 : p1;
        }

        Point operator+(Vec2 vec) const;

        Point operator-(Vec2 vec) const;

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

    struct Vec2
    {
        double x, y;

        Vec2() = default;

        Vec2(double x, double y) : x(x), y(y) {}

        explicit Vec2(geng::Point p0, geng::Point p1) :
            x(p1.x - p0.x),
            y(p1.y - p0.y)
        {}

        double operator*(Vec2 other_vec) const
        {
            return this->x * other_vec.x + this->y * other_vec.y;
        }

        Vec2 operator*(double scalar) const
        {
            return {this->x * scalar, this->y * scalar};
        }

        Vec2 operator+(Vec2 other_vec) const
        {
            return {this->x + other_vec.x, this->y + other_vec.y};
        }

        Vec2 operator-(Vec2 other_vec) const
        {
            return {this->x - other_vec.x, this->y - other_vec.y};
        }

        double projection(Vec2 vec_projected) const
        {
            return (*this * vec_projected) / (*this * *this);
        }

        static double abs(Vec2 vec)
        {
            return std::hypot(vec.x, vec.y);
        }
    };

    struct Matrix3
    {
        double m[3][3];

        Matrix3 operator*(const Matrix3& other) const;
    };
}

namespace geng
{
    inline Point Point::operator+(Vec2 vec) const
    {
        return {this->x + vec.x, this->y + vec.y};
    }

    inline Point Point::operator-(Vec2 vec) const
    {
        return {this->x - vec.x, this->y - vec.y};
    }
}
