module;
#include <cassert>
#include <cmath>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <vector>
#include <compare>
#include <algorithm>
#include <ranges>
export module gengine.types:primitives;

export
namespace geng
{
    constexpr double EPSILON_COMPUTE = 1e-9;

    struct Vec2;

    struct Point
    {
        double x = 0, y = 0;

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

        Point operator+(Vec2 vec) const;

        Point operator-(Vec2 vec) const;

    private:
        int64_t quantize_(double v) const
        {
            return static_cast<int64_t>(std::round(v / EPSILON_COMPUTE));
        }
    };

    struct Segment
    {
        geng::Point p0;
        geng::Point p1;

        Segment() = default;

        explicit Segment(geng::Point p0, geng::Point p1) : p0(p0), p1(p1) {}

        Segment(std::initializer_list<geng::Point> list) :
            Segment(
                    list.size() > 0 ?  *list.begin()      : geng::Point{},
                    list.size() > 1 ? *(list.begin() + 1) : geng::Point{}
                   )
        {
            assert(list.size() <= 2 && "Segment: too many arguments in initialization list.");
        }
    };

    struct LineString
    {
        std::vector<Point> points;
    };

    struct Polygon
    {
        std::vector<Point> outer;
        std::vector<std::vector<Point>> inner;
    };

    struct Vec2
    {
        double x = 0, y = 0;

        Vec2() = default;

        Vec2(double x, double y) : x(x), y(y) {}

        explicit Vec2(geng::Point p0, geng::Point p1) :
            x(p1.x - p0.x),
            y(p1.y - p0.y)
        {}

        // добавить лист для по точкам

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

        double length() const
        {
            return std::hypot(this->x, this->y);
        }

        double projection(Vec2 vec_projected) const
        {
            return (*this * vec_projected) / this->length();
        }
    };

    struct Matrix3
    {
        enum class InitType
        {
            Full,
            Diagonal
        };

        std::array<double, 9> m{};

        Matrix3() = default;

        Matrix3(double m0, double m1, double m2,
                double m3, double m4, double m5,
                double m6, double m7, double m8)
            : m{m0, m1, m2, m3, m4, m5, m6, m7, m8}
        {}

        explicit Matrix3(double val, InitType init_type = InitType::Full)
        {
            if (init_type == InitType::Diagonal)
            {
                m[0] = val;
                m[4] = val;
                m[8] = val;
            }
            else if (init_type == InitType::Full)
            {
                m.fill(val);
            }
            else { assert(false && "Matrix3: non valid init_type."); }
        }

        Matrix3(std::initializer_list<double> list)
        {
            std::ranges::copy(list | std::views::take(9), m.begin());
            assert(list.size() <= 9 && "Matrix3: too many arguments in inidializion list.");
        }

        explicit Matrix3(geng::Vec2 vec0, geng::Vec2 vec1 = {}, geng::Vec2 vec2 = {})
        {
            m = {
                vec0.x, vec1.x, vec2.x,
                vec0.y, vec1.y, vec2.y,
                0,      0,      1
            };
        }


        Matrix3(std::initializer_list<geng::Vec2> list) :
            Matrix3(
                    list.size() > 0 ?  *list.begin()      : geng::Vec2{},
                    list.size() > 1 ? *(list.begin() + 1) : geng::Vec2{},
                    list.size() > 2 ? *(list.begin() + 2) : geng::Vec2{}
                   )
        {
            assert(list.size() <= 3 && "Matrix3: too many arguments in inidializion list.");
        }

        const double& operator[](size_t i, size_t j) const { return m[i * 3 + j]; }
              double& operator[](size_t i, size_t j)       { return m[i * 3 + j]; }

        const double& operator[](size_t n) const { return m[n]; }
              double& operator[](size_t n)       { return m[n]; }

        auto begin() const { return m.begin(); }
        auto end()   const { return m.end(); }
        auto begin()       { return m.begin(); }
        auto end()         { return m.end(); }

        Matrix3 operator*(const Matrix3& other) const
        {
            Matrix3 res;
            for (size_t i = 0; i < 3; ++i)
            {
                for (size_t j = 0; j < 3; ++j)
                {
                    res[i, j] = (*this)[i, 0] * other[0, j] +
                                (*this)[i, 1] * other[1, j] +
                                (*this)[i, 2] * other[2, j];
                }
            }
            return res;
        }

        Vec2 operator*(const Vec2& vec) const
        {
            return {
                (*this)[0, 0] * vec.x + (*this)[0, 1] * vec.y + (*this)[0, 2],
                (*this)[1, 0] * vec.x + (*this)[1, 1] * vec.y + (*this)[1, 2]
            };
        }

        Matrix3 operator*(double scalar) const
        {
            Matrix3 scalar_matrix(scalar);
            return binary_for_each_op_(scalar_matrix, std::multiplies{});
        }

        Matrix3 operator+(const Matrix3& other) const { return binary_for_each_op_(other, std::plus{}); }
        Matrix3 operator-(const Matrix3& other) const { return binary_for_each_op_(other, std::minus{}); }

        double det() const
        {
            // On the third row
            return m[6] * (m[1] * m[5] - m[2] * m[4])
                 - m[7] * (m[0] * m[5] - m[2] * m[3])
                 + m[8] * (m[0] * m[4] - m[1] * m[3]);
        }

    private:
        Matrix3 binary_for_each_op_(const Matrix3& other_matrix, std::regular_invocable<double, double> auto op) const
        {
            Matrix3 result_matrix;
            std::transform(this->begin(), this->end(), other_matrix.begin(), result_matrix.begin(), op);
            return result_matrix;
        }
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
