module;
#include <cmath>
#include <ranges>
#include <algorithm>
export module gengine.math;
import gengine.types;

export
namespace geng::math
{
    bool is_zero(double v)
    {
        return std::abs(v) < geng::EPSILON_COMPUTE;
    }

    bool is_equal(double v0, double v1)
    {
        return std::abs(v0 - v1) < geng::EPSILON_COMPUTE;
    }

    double projection_coeff(Vec2 vec_projecting, Vec2 vec_projected)
    {
        return (vec_projecting * vec_projected) / (vec_projecting * vec_projecting);
    }

    double length(Vec2 vec)
    {
        return std::hypot(vec.x, vec.y);
    }

    Point max(Point p0, Point p1)
    {
        return p0 > p1 ? p0 : p1;
    }

    Point min(Point p0, Point p1)
    {
        return p0 < p1 ? p0 : p1;
    }

    double calc_distance_euclidean(geng::Point p0, geng::Point p1)
    {
        double distance = std::pow(p0.x - p1.x, 2) +
                          std::pow(p0.y - p1.y, 2);
        return std::sqrt(distance);
    }

    double calc_distance_point_to_segment(geng::Point p,
                                          geng::Point segment_p0,
                                          geng::Point segment_p1)
    {
        geng::Vec2 u(segment_p0, p);
        geng::Vec2 seg_guiding(segment_p0, segment_p1);

        double projection_coeff = geng::math::projection_coeff(seg_guiding, u);

        if (segment_p0 == segment_p1 || projection_coeff < 0)
        {
            return geng::math::calc_distance_euclidean(p, segment_p0);
        }
        if (projection_coeff > 1)
        {
            return geng::math::calc_distance_euclidean(p, segment_p1);
        }

        geng::Point p_projection_on_segment = segment_p0 + seg_guiding * projection_coeff;
        return geng::math::calc_distance_euclidean(p, p_projection_on_segment);
    }

    double calc_area_polygon(const geng::Polygon& poly)
    {
        namespace views  = std::views;
        namespace ranges = std::ranges;

        auto outer_trapezoid_peaks = poly.outer | views::pairwise;

        auto inner_trapezoid_peaks = poly.inner
                                   | views::transform([](const auto& ring){ return ring | views::pairwise; })
                                   | views::join;

        auto area_below_segment = [](const auto& group) {
            auto [p0, p1] = group;
            return p0.x * p1.y - p0.y * p1.x;
        };

        auto areas_outer = outer_trapezoid_peaks | views::transform(area_below_segment);
        auto areas_inner = inner_trapezoid_peaks | views::transform(area_below_segment);

        const double result_area = std::ranges::fold_left(
                areas_outer,
                ranges::fold_left(areas_inner, 0.0, std::plus{}),
                std::plus{}
                );

        return std::abs(result_area / 2);
    }

    enum class Orientation
    {
        LEFT,
        RIGHT,
        COLINEAR
    };

    Orientation orientation_point_segment(geng::Point p, geng::Point segment_p0, geng::Point segment_p1)
    {
        geng::Matrix3 orientation_matrix = {
            geng::Vec2(segment_p0, segment_p1),
            geng::Vec2(segment_p0, p)
        };

        double determinant = orientation_matrix.det();

        if (determinant > 0) return Orientation::LEFT;
        if (geng::math::is_zero(determinant)) return Orientation::COLINEAR;
        return Orientation::RIGHT;
    }
}
