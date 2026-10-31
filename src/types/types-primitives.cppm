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
#include <array>
#include <concepts>
#include <cstddef>
export module gengine.types:primitives;

export
namespace geng
{
    constexpr double EPSILON_COMPUTE = 1e-9;

    struct Vec2;

    struct [[nodiscard]] Point
    {
        double x = 0, y = 0;

        [[nodiscard]]
        std::strong_ordering operator<=>(const Point& other_p) const
        {
            assert(!std::isnan(x) && !std::isnan(other_p.x) &&
                   !std::isnan(y) && !std::isnan(other_p.y) &&
                    "operator<=>: NaN is not allowed.");

            if (auto cmp = quantize(x) <=> quantize(other_p.x);
                    cmp != 0)
                return cmp;

            return quantize(y) <=> quantize(other_p.y);
        }

        [[nodiscard]]
        bool operator==(const Point& other_p) const
        {
            return (*this <=> other_p) == 0;
        }

        Point operator+(Vec2 vec) const;

        Point operator-(Vec2 vec) const;

    private:
        int64_t quantize(double v) const
        {
            return static_cast<int64_t>(std::round(v / EPSILON_COMPUTE));
        }
    };

    struct [[nodiscard]] Segment
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
            assert(list.size() == 2 && "Segment: must be 2 points in initialization list.");
        }

        [[nodiscard]]
        bool operator==(const Segment& other_seg) const
        {
            return p0 == other_seg.p0 && p1 == other_seg.p1;
        }
    };

    struct [[nodiscard]] LineString
    {
        std::vector<Point> points;
    };

    struct [[nodiscard]] Polygon
    {
        std::vector<Point> outer;
        std::vector<std::vector<Point>> inner;
    };

    struct [[nodiscard]] Vec2
    {
        double x = 0, y = 0;

        Vec2() = default;

        Vec2(double x, double y) : x(x), y(y) {}

        explicit Vec2(geng::Point p0, geng::Point p1) :
            x(p1.x - p0.x),
            y(p1.y - p0.y)
        {}

        Vec2(std::initializer_list<geng::Point> point_sequence) :
            Vec2(
                    point_sequence.size() > 0 ? *point_sequence.begin()       : geng::Point{},
                    point_sequence.size() > 1 ? *(point_sequence.begin() + 1) : geng::Point{}
                )
        {
            assert(point_sequence.size() == 2 && "Vec2: must be 2 points in initialization list.");
        }

        [[nodiscard]]
        double operator*(Vec2 other_vec) const
        {
            return x * other_vec.x + y * other_vec.y;
        }

        Vec2 operator*(double scalar) const
        {
            return {x * scalar, y * scalar};
        }

        Vec2 operator+(Vec2 other_vec) const
        {
            return {x + other_vec.x, y + other_vec.y};
        }

        Vec2 operator-(Vec2 other_vec) const
        {
            return {x - other_vec.x, y - other_vec.y};
        }

        [[nodiscard]]
        double length() const
        {
            return std::hypot(x, y);
        }

        [[nodiscard]]
        double projection(Vec2 vec_projected) const
        {
            return (*this * vec_projected) / length();
        }
    };

    struct [[nodiscard]] Matrix3
    {
    private:
        enum class InitType
        {
            FULL,
            DIAGONAL
        };

        explicit Matrix3(double val, InitType init_type)
        {
            if (init_type == InitType::DIAGONAL)
            {
                m[0] = val;
                m[4] = val;
                m[8] = val;
            }
            else if (init_type == InitType::FULL)
            {
                m.fill(val);
            }
            else { assert(false && "Matrix3: non valid init_type."); }
        }

    public:

        std::array<double, 9> m{};

        Matrix3() = default;

        Matrix3(double m0, double m1, double m2,
                double m3, double m4, double m5,
                double m6, double m7, double m8)
            : m{m0, m1, m2, m3, m4, m5, m6, m7, m8}
        {}

        static Matrix3 Full(double val)
        {
            return Matrix3(val, geng::Matrix3::InitType::FULL);
        }

        static Matrix3 Diagonal(double val)
        {
            return Matrix3(val, geng::Matrix3::InitType::DIAGONAL);
        }

        Matrix3(std::initializer_list<double> double_sequence)
        {
            std::ranges::copy(double_sequence | std::views::take(9), m.begin());
            assert(double_sequence.size() == 9 && "Matrix3: must be 9 values in initialization list.");
        }

        explicit Matrix3(geng::Vec2 vec1, geng::Vec2 vec2 = {}, geng::Vec2 vec3 = {})
        {
            m = {
                vec1.x, vec2.x, vec3.x,
                vec1.y, vec2.y, vec3.y,
                0,      0,      1
            };
        }


        Matrix3(std::initializer_list<geng::Vec2> vec_sequense) :
            Matrix3(
                    vec_sequense.size() > 0 ?  *vec_sequense.begin()      : geng::Vec2{},
                    vec_sequense.size() > 1 ? *(vec_sequense.begin() + 1) : geng::Vec2{},
                    vec_sequense.size() > 2 ? *(vec_sequense.begin() + 2) : geng::Vec2{}
                   )
        {
            assert(vec_sequense.size() <= 3 && "Matrix3: too many arguments in inidializion list.");
        }

        [[nodiscard]] const double& operator[](size_t i, size_t j) const { return m[i * 3 + j]; }
        [[nodiscard]]       double& operator[](size_t i, size_t j)       { return m[i * 3 + j]; }

        [[nodiscard]] auto begin() const { return m.begin(); }
        [[nodiscard]] auto end()   const { return m.end(); }
        [[nodiscard]] auto begin()       { return m.begin(); }
        [[nodiscard]] auto end()         { return m.end(); }

        [[nodiscard]]
        Matrix3 operator*(const Matrix3& other_mtx) const
        {
            Matrix3 res;
            for (size_t i = 0; i < 3; ++i)
            {
                for (size_t j = 0; j < 3; ++j)
                {
                    res[i, j] = (*this)[i, 0] * other_mtx[0, j] +
                                (*this)[i, 1] * other_mtx[1, j] +
                                (*this)[i, 2] * other_mtx[2, j];
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
            Matrix3 matrix_out_of_scalars = geng::Matrix3::Full(scalar);
            return zip_with_predicate(matrix_out_of_scalars, std::multiplies{});
        }

        Matrix3 operator+(const Matrix3& other_mtx) const { return zip_with_predicate(other_mtx, std::plus{}); }
        Matrix3 operator-(const Matrix3& other_mtx) const { return zip_with_predicate(other_mtx, std::minus{}); }

        [[nodiscard]]
        double det() const
        {
            // On the third row
            return m[6] * (m[1] * m[5] - m[2] * m[4])
                 - m[7] * (m[0] * m[5] - m[2] * m[3])
                 + m[8] * (m[0] * m[4] - m[1] * m[3]);
        }

    private:
        Matrix3 zip_with_predicate(const Matrix3& other_mtx, std::regular_invocable<double, double> auto pred) const
        {
            Matrix3 result_mtx;
            std::transform(begin(), end(), other_mtx.begin(), result_mtx.begin(), pred);
            return result_mtx;
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
