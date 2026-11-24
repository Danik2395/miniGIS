module;
#include <cassert>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <utility>
#include <vector>
#include <compare>
#include <variant>
#include <algorithm>
#include <ranges>
#include <array>
#include <concepts>
#include <cstddef>
#include <tuple>
export module gengine.types.primitives;
import gengine.compare.doubles;

export namespace geng
{
struct [[nodiscard]] Point;

struct [[nodiscard]] Segment;

struct [[nodiscard]] LineString;

struct [[nodiscard]] Polygon;

struct [[nodiscard]] Vec2;

struct [[nodiscard]] Matrix3;

using Geometry = std::variant<geng::Point,
                              geng::LineString,
                              geng::Polygon>;
} // namespace geng



namespace geng
{
struct Point
{
    double x = 0, y = 0;

    [[nodiscard]]
    std::strong_ordering operator<=>(const Point& other_p) const
    {
        assert(!std::isnan(x) && !std::isnan(other_p.x) &&
               !std::isnan(y) && !std::isnan(other_p.y) &&
                "Point::operator<=>: NaN is not allowed.");

        if (auto cmp = geng::quantize(x) <=> geng::quantize(other_p.x); cmp != 0)
        {
            return cmp;
        }

        return geng::quantize(y) <=> geng::quantize(other_p.y);
    }

    [[nodiscard]]
    bool operator==(const Point& other_p) const
    {
        return (*this <=> other_p) == 0;
    }

    Point operator+(geng::Vec2 vec) const;

    Point operator-(geng::Vec2 vec) const;
};

struct Segment
{
    geng::Point p0;
    geng::Point p1;

    [[nodiscard]]
    bool operator==(const Segment& other_seg) const
    {
        return p0 == other_seg.p0 && p1 == other_seg.p1;
    }
};

struct LineString
{
    std::vector<geng::Point> points;

    [[nodiscard]]
    bool operator==(const LineString& other_line) const
    {
        return points == other_line.points;
    }
};

struct Polygon
{
    std::vector<geng::Point> outer;
    std::vector<std::vector<geng::Point>> inner;

    [[nodiscard]]
    bool operator==(const Polygon& other_poly) const
    {
        return outer == other_poly.outer && inner == other_poly.inner;
    }
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

template<typename Fn>
concept ZipMatrixOper = std::invocable<Fn, double, double>;

struct Matrix3
{
private:
    enum class InitType
    {
        FULL,
        DIAGONAL
    };

    explicit Matrix3(double val, InitType init_type) : m{}
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
        else { std::unreachable(); }
    }

    [[nodiscard]]
    auto two_indexes_view() const
    {
        auto line_view = std::views::iota(size_t(0), size_t(3));
        auto view_two_indexes = std::views::cartesian_product(line_view, line_view);
        return view_two_indexes;
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
        assert(double_sequence.size() == 9 && "Matrix3: must be 9 values in initialization list.");
        std::ranges::copy(double_sequence | std::views::take(9), m.begin());
    }

    explicit Matrix3(geng::Vec2 vec1, geng::Vec2 vec2 = {}, geng::Vec2 vec3 = {})
    {
        m = {
            vec1.x, vec2.x, vec3.x,
            vec1.y, vec2.y, vec3.y,
            0.0,    0.0,    1.0
        };
    }


    Matrix3(std::initializer_list<geng::Vec2> vec_sequense) :
        Matrix3(
                vec_sequense.size() > 0 ?  *vec_sequense.begin()      : geng::Vec2{},
                vec_sequense.size() > 1 ? *(vec_sequense.begin() + 1) : geng::Vec2{},
                vec_sequense.size() > 2 ? *(vec_sequense.begin() + 2) : geng::Vec2{}
               )
    {
        assert(vec_sequense.size() <= 3 && "Matrix3: too many arguments in initializion list.");
    }

    [[nodiscard]] auto& operator[](this auto&& self, size_t i, size_t j) { return self.m[i * 3 + j]; }

    [[nodiscard]] auto begin(this auto&& self) { return self.m.begin(); }
    [[nodiscard]] auto end(this auto&& self)   { return self.m.end(); }

    [[nodiscard]] auto size() const { return m.size(); }

    [[nodiscard]]
    Matrix3 operator*(const Matrix3& other_mtx) const
    {
        auto get_multiplied_elem = [&other_mtx, this](const auto& indexes) {
            const auto [i, j] = indexes;

            return (*this)[i, 0] * other_mtx[0, j] +
                   (*this)[i, 1] * other_mtx[1, j] +
                   (*this)[i, 2] * other_mtx[2, j];
        };

        auto multiplied_elements = two_indexes_view() | std::views::transform(get_multiplied_elem);

        Matrix3 multiplication_mtx{};

        std::ranges::copy(multiplied_elements, multiplication_mtx.begin());

        return multiplication_mtx;
    }

    geng::Vec2 operator*(const geng::Vec2& vec) const
    {
        const auto [x, y] = scale_two_points(vec.x, vec.y);
        return {x, y};
    }

    geng::Point operator*(const geng::Point& p) const
    {
        const auto [x, y] = scale_two_points(p.x, p.y);
        return {x, y};
    }

    Matrix3 operator*(double scalar)            const { return zip_with_oper(scalar, std::multiplies{}); }
    Matrix3 operator+(const Matrix3& other_mtx) const { return zip_with_oper(other_mtx, std::plus{}); }
    Matrix3 operator-(const Matrix3& other_mtx) const { return zip_with_oper(other_mtx, std::minus{}); }

    [[nodiscard]]
    double det() const
    {
        // On the third row
        return m[6] * minor(2, 0) - m[7] * minor(2, 1) + m[8] * minor(2, 2);
    }

    [[nodiscard]]
    double minor(size_t i, size_t j) const
    {
        const size_t r0 = (i == 0) ? 1 : 0;
        const size_t r1 = (i == 2) ? 1 : 2;
        const size_t c0 = (j == 0) ? 1 : 0;
        const size_t c1 = (j == 2) ? 1 : 2;

        return (*this)[r0, c0] * (*this)[r1, c1] - (*this)[r0, c1] * (*this)[r1, c0];
    }

    Matrix3 transposed() const
    {
        return {
            m[0], m[3], m[6],
            m[1], m[4], m[7],
            m[2], m[5], m[8],
        };
    }

    Matrix3 inverse() const
    {
        Matrix3 minor_mtx = {
            minor(0, 0), -minor(0, 1), minor(0, 2),
            -minor(1, 0), minor(1, 1), -minor(1, 2),
            minor(2, 0), -minor(2, 1), minor(2, 2),
        };

        return minor_mtx.transposed() * (1 / (*this).det());
    }

private:
    std::tuple<double, double> scale_two_points(double x, double y) const
    {
        return {
            (*this)[0, 0] * x + (*this)[0, 1] * y + (*this)[0, 2],
            (*this)[1, 0] * x + (*this)[1, 1] * y + (*this)[1, 2]
        };
    }

    Matrix3 zip_with_oper(const Matrix3& other_mtx, geng::ZipMatrixOper auto oper) const
    {
        Matrix3 result_mtx;
        std::transform(begin(), end(), other_mtx.begin(), result_mtx.begin(), oper);
        return result_mtx;
    }

    Matrix3 zip_with_oper(double scalar, geng::ZipMatrixOper auto oper) const
    {
        Matrix3 result_mtx;
        std::transform(begin(), end(), result_mtx.begin(), [&oper, &scalar](double v){ return oper(scalar, v); });
        return result_mtx;
    }
};
} // namespace geng

namespace geng
{
inline geng::Point geng::Point::operator+(geng::Vec2 vec) const
{
    return {this->x + vec.x, this->y + vec.y};
}

inline geng::Point geng::Point::operator-(geng::Vec2 vec) const
{
    return {this->x - vec.x, this->y - vec.y};
}
} // namespace geng
