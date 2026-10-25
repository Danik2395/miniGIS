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
    bool is_zero(double v)
    {
        return std::abs(v) < geng::EPSILON_COMPUTE;
    }

    bool is_equal(double v0, double v1)
    {
        return std::abs(v0 - v1) < geng::EPSILON_COMPUTE;
    }

    bool is_within(double val, double min, double max)
    {
        return (val > min || geng::math::is_equal(val, min)) &&
               (val < max || geng::math::is_equal(val, max));
    }

    double projection_coeff(Vec2 vec_projecting, Vec2 vec_projected)
    {
        return (vec_projecting * vec_projected) / (vec_projecting * vec_projecting);
    }

    double length(Vec2 vec)
    {
        return std::hypot(vec.x, vec.y);
    }

    double cross(Vec2 vec0, Vec2 vec1)
    {
        return vec0.x * vec1.y - vec1.x * vec0.y;
    }

    bool is_zero(geng::Vec2 vec)
    {
        return geng::math::is_zero(geng::math::length(vec));
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
        geng::Vec2 seg_to_point_vec(segment_p0, p);
        geng::Vec2 seg_guiding_vec(segment_p0, segment_p1);

        double projection_coeff = geng::math::projection_coeff(seg_guiding_vec, seg_to_point_vec);

        if (segment_p0 == segment_p1 || projection_coeff < 0)
        {
            return geng::math::calc_distance_euclidean(p, segment_p0);
        }
        if (projection_coeff > 1)
        {
            return geng::math::calc_distance_euclidean(p, segment_p1);
        }

        geng::Point p_projection_on_segment = segment_p0 + seg_guiding_vec * projection_coeff;
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
        COLLINEAR
    };

    Orientation orientation_point_segment(geng::Point p, geng::Point segment_p0, geng::Point segment_p1)
    {
        geng::Matrix3 orientation_matrix = {
            geng::Vec2(segment_p0, segment_p1),
            geng::Vec2(segment_p0, p)
        };

        double determinant = orientation_matrix.det();

        if (determinant > 0) return Orientation::LEFT;
        if (geng::math::is_zero(determinant)) return Orientation::COLLINEAR;
        return Orientation::RIGHT;
    }

    void make_segment_left_to_right(geng::Segment& seg)
    {
        if (seg.p0 > seg.p1) std::swap(seg.p0, seg.p1);
    }

    Orientation orientation_point_segment(geng::Point p, geng::Segment seg)
    {
        return orientation_point_segment(p, seg.p0, seg.p1);
    }

    bool is_point_on_segment(geng::Point p, geng::Point segment_p0, geng::Point segment_p1)
    {
        if (orientation_point_segment(p, segment_p0, segment_p1) != geng::math::Orientation::COLLINEAR)
        {
            return false;
        }

        geng::Vec2 seg_guiding_vec = {segment_p0, segment_p1};
        geng::Vec2 seg_to_point_vec = {segment_p0, p};

        if (geng::math::is_zero(seg_to_point_vec))
        {
            return p == segment_p0;
        }

        double proj_coeff = geng::math::projection_coeff(seg_guiding_vec, seg_to_point_vec);

        return proj_coeff >= 0 && proj_coeff <= 1;
    }

    bool is_point_on_segment(geng::Point p, geng::Segment seg)
    {
        return is_point_on_segment(p, seg.p0, seg.p1);
    }

    std::pair<bool, geng::Point> is_point_end_of_segment(geng::Point p, geng::Point segment_p0, geng::Point segment_p1)
    {
        if (p == segment_p0) return {true, {segment_p0}};
        if (p == segment_p1) return {true, {segment_p1}};
        return {false, {}};
    }

    std::pair<bool, geng::Point> is_point_end_of_segment(geng::Point p, geng::Segment seg)
    {
        return is_point_end_of_segment(p, seg.p0, seg.p1);
    }

    using SegmentsIntersection = std::variant<std::monostate, geng::Point, geng::Segment>;

    SegmentsIntersection calc_intersection(geng::Segment seg0, geng::Segment seg1)
    {
        geng::Vec2 vec_seg0                  = {seg0.p0, seg0.p1};
        geng::Vec2 vec_seg1                  = {seg1.p0, seg1.p1};
        geng::Vec2 vec_seg0_begin_seg1_begin = {seg0.p0, seg1.p0};

        double cross_seg0_seg1 = geng::math::cross(vec_seg0, vec_seg1);

        if (!geng::math::is_equal(cross_seg0_seg1, 0))
        {
            double cross_begins_seg0 = geng::math::cross(vec_seg0_begin_seg1_begin, vec_seg1);
            double cross_begins_seg1 = geng::math::cross(vec_seg0_begin_seg1_begin, vec_seg0);

            // M(t), N(u) - are points of intersection on seg0 and seg1
            // M(t) = N(u)
            // x1 + t * p_x = x3 + u * q_x
            // y1 + t * p_y = y3 + u * q_y
            // Solve system to get t and u
            double coeff_seg0 = cross_begins_seg0 / cross_seg0_seg1;
            double coeff_seg1 = cross_begins_seg1 / cross_seg0_seg1;

            if (!geng::math::is_within(coeff_seg0, 0.0, 1.0) ||
                !geng::math::is_within(coeff_seg1, 0.0, 1.0))
            {
                return std::monostate();
            }

            geng::Point intersection_point = seg0.p0 + vec_seg0 * coeff_seg0;

            return intersection_point;
        }

        geng::Vec2 vec_seg0_begin_seg1_end = {seg0.p0, seg1.p1};

        double cross_to_check_segments_on_one_line = geng::math::cross(vec_seg0_begin_seg1_begin, vec_seg0_begin_seg1_end);

        if (!geng::math::is_equal(cross_to_check_segments_on_one_line, 0))
        {
            return std::monostate();
        }

        double coeff0 = geng::math::projection_coeff(vec_seg0, vec_seg0_begin_seg1_begin);
        double coeff1 = geng::math::projection_coeff(vec_seg0, vec_seg0_begin_seg1_end);

        double start_coeff = std::max(0.0, std::min(coeff0, coeff1));
        double end_coeff   = std::min(1.0, std::max(coeff0, coeff1));

        if (start_coeff > end_coeff)
        {
            return std::monostate();
        }

        geng::Point intersection_point_begin = seg0.p0 + vec_seg0 * start_coeff;

        if (geng::math::is_equal(start_coeff, end_coeff))
        {
            return intersection_point_begin;
        }

        geng::Point intersection_point_end = seg0.p0 + vec_seg0 * end_coeff;

        return geng::Segment(intersection_point_begin, intersection_point_end);
    }

    bool is_intersect(geng::Segment seg0, geng::Segment seg1)
    {
        return !std::holds_alternative<std::monostate>(geng::math::calc_intersection(seg0, seg1));
    }
}
