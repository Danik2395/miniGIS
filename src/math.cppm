module;
#include <cmath>
#include <cassert>
#include <ranges>
#include <algorithm>
#include <utility>
#include <variant>
export module gengine.math;
import gengine.types;

export
namespace geng::math
{
    bool is_zero(double val)
    {
        return std::abs(val) < geng::EPSILON_COMPUTE;
    }

    bool is_equal(double val1, double val2)
    {
        return std::abs(val1 - val2) < geng::EPSILON_COMPUTE;
    }

    bool is_within(double val, double min, double max)
    {
        return (val > min || geng::math::is_equal(val, min)) &&
               (val < max || geng::math::is_equal(val, max));
    }

    double proj_coeff(Vec2 vec_projecting, Vec2 vec_projected)
    {
        return (vec_projecting * vec_projected) / (vec_projecting * vec_projecting);
    }

    double length(Vec2 vec)
    {
        return std::hypot(vec.x, vec.y);
    }

    double cross(Vec2 vec1, Vec2 vec2)
    {
        return vec1.x * vec2.y - vec2.x * vec1.y;
    }

    bool is_zero(geng::Vec2 vec)
    {
        return geng::math::is_zero(geng::math::length(vec));
    }

    Point max(Point p1, Point p2)
    {
        return p1 > p2 ? p1 : p2;
    }

    Point min(Point p1, Point p2)
    {
        return p1 < p2 ? p1 : p2;
    }

    double distance_euclidean(geng::Point p0, geng::Point p1)
    {
        double distance = std::pow(p0.x - p1.x, 2) +
                          std::pow(p0.y - p1.y, 2);
        return std::sqrt(distance);
    }

    double distance(geng::Point p, geng::Point seg_p0, geng::Point seg_p1)
    {
        geng::Vec2 vec_seg_to_point(seg_p0, p);
        geng::Vec2 vec_seg_guiding(seg_p0, seg_p1);

        double proj_coeff_on_guiding = geng::math::proj_coeff(vec_seg_guiding, vec_seg_to_point);

        if (seg_p0 == seg_p1 || proj_coeff_on_guiding < 0)
        {
            return geng::math::distance_euclidean(p, seg_p0);
        }
        if (proj_coeff_on_guiding > 1)
        {
            return geng::math::distance_euclidean(p, seg_p1);
        }

        geng::Point p_projection_on_segment = seg_p0 + vec_seg_guiding * proj_coeff_on_guiding;
        return geng::math::distance_euclidean(p, p_projection_on_segment);
    }

    double area(const geng::Polygon& poly)
    {
        namespace views  = std::views;
        namespace ranges = std::ranges;

        auto outer_trapezoid_peaks = poly.outer | views::pairwise;

        auto inner_trapezoid_peaks = poly.inner
                                   | views::transform([](const auto& ring){ return ring | views::pairwise; })
                                   | views::join;

        auto area_below_segment = [](const auto& seg_points) {
            auto [p0, p1] = seg_points;
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
        COLLINEAR
    };

    Orientation orientation(geng::Point p, geng::Point seg_p0, geng::Point seg_p1)
    {
        geng::Matrix3 orientation_matrix = {
            geng::Vec2(seg_p0, seg_p1),
            geng::Vec2(seg_p0, p)
        };

        double determinant = orientation_matrix.det();

        if (determinant > 0) return Orientation::LEFT;
        if (geng::math::is_zero(determinant)) return Orientation::COLLINEAR;
        return Orientation::RIGHT;
    }

    Orientation orientation(geng::Point p, const geng::Segment& seg)
    {
        return orientation(p, seg.p0, seg.p1);
    }

    bool is_point_on_segment(geng::Point p, geng::Point seg_p0, geng::Point seg_p1)
    {
        if (orientation(p, seg_p0, seg_p1) != geng::math::Orientation::COLLINEAR)
        {
            return false;
        }

        geng::Vec2 vec_seg_guiding  = {seg_p0, seg_p1};
        geng::Vec2 vec_seg_to_point = {seg_p0, p};

        if (geng::math::is_zero(vec_seg_to_point))
        {
            return p == seg_p0;
        }

        double proj_coeff_on_guiding = geng::math::proj_coeff(vec_seg_guiding, vec_seg_to_point);

        return proj_coeff_on_guiding >= 0 && proj_coeff_on_guiding <= 1;
    }

    bool is_point_on_segment(geng::Point p, const geng::Segment& seg)
    {
        return is_point_on_segment(p, seg.p0, seg.p1);
    }

    std::pair<bool, geng::Point> is_point_end_of_segment(geng::Point p, geng::Point seg_p0, geng::Point seg_p1)
    {
        if (p == seg_p0) return {true, {seg_p0}};
        if (p == seg_p1) return {true, {seg_p1}};
        return {false, {}};
    }

    std::pair<bool, geng::Point> is_point_end_of_segment(geng::Point p, const geng::Segment& seg)
    {
        return is_point_end_of_segment(p, seg.p0, seg.p1);
    }

    using SegmentsIntersection = std::variant<std::monostate, geng::Point, geng::Segment>;

    SegmentsIntersection intersection(const geng::Segment& seg1, const geng::Segment& seg2)
    {
        geng::Vec2 vec_seg1          = {seg1.p0, seg1.p1};
        geng::Vec2 vec_seg2          = {seg2.p0, seg2.p1};
        geng::Vec2 vec_begin1_begin2 = {seg1.p0, seg2.p0};

        double cross_seg1_seg2 = geng::math::cross(vec_seg1, vec_seg2);

        if (!geng::math::is_equal(cross_seg1_seg2, 0))
        {
            double cross_begins_seg1 = geng::math::cross(vec_begin1_begin2, vec_seg1);
            double cross_begins_seg2 = geng::math::cross(vec_begin1_begin2, vec_seg2);

            // M(t), N(u) - are points of intersection on seg1 and seg2
            // M(t) = N(u)
            // x1 + t * p_x = x3 + u * q_x
            // y1 + t * p_y = y3 + u * q_y
            // Solve system to get t and u
            double coeff_seg1 = cross_begins_seg2 / cross_seg1_seg2;
            double coeff_seg2 = cross_begins_seg1 / cross_seg1_seg2;

            if (!geng::math::is_within(coeff_seg1, 0.0, 1.0) ||
                !geng::math::is_within(coeff_seg2, 0.0, 1.0))
            {
                return std::monostate();
            }

            geng::Point intersection_point = seg1.p0 + vec_seg1 * coeff_seg1;

            return intersection_point;
        }

        geng::Vec2 vec_begin1_end2 = {seg1.p0, seg2.p1};

        double cross_to_check_segments_on_one_line = geng::math::cross(vec_begin1_begin2, vec_begin1_end2);

        if (!geng::math::is_equal(cross_to_check_segments_on_one_line, 0))
        {
            return std::monostate();
        }

        double start_point_proj_coeff = geng::math::proj_coeff(vec_seg1, vec_begin1_begin2);
        double end_point_proj_coeff   = geng::math::proj_coeff(vec_seg1, vec_begin1_end2);

        //              *--------------------*   seg1
        //   *--------------------*              seg2
        //              *---------*              intersection_seg
        double start_coeff = std::max(0.0, std::min(start_point_proj_coeff, end_point_proj_coeff));
        double end_coeff   = std::min(1.0, std::max(start_point_proj_coeff, end_point_proj_coeff));

        if (start_coeff > end_coeff)
        {
            return std::monostate();
        }

        geng::Point intersection_point_begin = seg1.p0 + vec_seg1 * start_coeff;

        if (geng::math::is_equal(start_coeff, end_coeff))
        {
            return intersection_point_begin;
        }

        geng::Point intersection_point_end = seg1.p0 + vec_seg1 * end_coeff;

        return geng::Segment(intersection_point_begin, intersection_point_end);
    }

    bool is_intersect(const geng::Segment& seg1, const geng::Segment& seg2)
    {
        return !std::holds_alternative<std::monostate>(geng::math::intersection(seg1, seg2));
    }
}
