module;
#include <cmath>
#include <cassert>
#include <ranges>
#include <algorithm>
#include <utility>
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

    bool is_intersect(geng::Segment seg0, geng::Segment seg1)
    {
        using Orient = geng::math::Orientation;

        struct CheckOrientGroup {
            Orient orient;
            geng::Point point;
            geng::Segment seg;
        };

        std::array checks = {
            CheckOrientGroup{orientation_point_segment(seg0.p0, seg1), seg0.p0, seg1},
            CheckOrientGroup{orientation_point_segment(seg0.p1, seg1), seg0.p1, seg1},
            CheckOrientGroup{orientation_point_segment(seg1.p0, seg0), seg1.p0, seg0},
            CheckOrientGroup{orientation_point_segment(seg1.p1, seg0), seg1.p1, seg0},
        };

        bool has_collinear = std::ranges::any_of(checks, [](const auto& group){ return group.orient == Orient::COLLINEAR; });

        // Could be collinear without intersecting
        if (!has_collinear && (checks[0].orient != checks[1].orient && checks[2].orient != checks[3].orient)) return true;

        bool has_intersection =
            std::ranges::any_of(checks, [](const auto& group){ return geng::math::is_point_on_segment(group.point, group.seg); });

        if (has_intersection) return true;

        return false;
    }

    geng::Point calc_intersection_point(geng::Segment seg0, geng::Segment seg1)
    {
        assert(is_intersect(seg0, seg1) && "calc_intersection_point: segments have no intersection points.");

        geng::math::make_segment_left_to_right(seg0);
        geng::math::make_segment_left_to_right(seg1);

        double x1 = seg0.p0.x, y1 = seg0.p0.y;
        double x2 = seg0.p1.x, y2 = seg0.p1.y;

        double x3 = seg1.p0.x, y3 = seg1.p0.y;
        double x4 = seg1.p1.x, y4 = seg1.p1.y;

        double k1 = (y2 - y1) / (x2 - x1);
        double k2 = (y4 - y3) / (x4 - x3);

        if (geng::math::is_equal(x1, x2)) // seg0 vertical: k1 -> inf
        {
            double y_on_seg0 = k2 * (x1 - x3) + y3;
            return {x1, y_on_seg0};
        }
        if (geng::math::is_equal(x3, x4))
        {
            double y_on_seg1 = k1 * (x3 - x1) + y1;
            return {x3, y_on_seg1};
        }

        if (geng::math::is_equal(k1, k2))
        {
            auto check_pair_left_point  = geng::math::is_point_end_of_segment(seg0.p0, seg1);
            auto check_pair_right_point = geng::math::is_point_end_of_segment(seg0.p1, seg1);

            if (check_pair_left_point.first)  return check_pair_left_point.second;
            if (check_pair_right_point.first) return check_pair_right_point.second;
        }

        double x_intersection = (k1 * x1 - k2 * x3 + y3 -y1) / (k1 - k2);
        double y_intersection = k1 * (x_intersection - x1) + y1;

        return {x_intersection, y_intersection};
    }

    std::pair<bool, geng::Point> calc_intersection_point_with_check(geng::Segment seg0, geng::Segment seg1)
    {
        bool has_intersect = geng::math::is_intersect(seg0, seg1);

        if (!has_intersect) return {has_intersect, {}};

        geng::Point intersection_point = calc_intersection_point(seg0, seg1);

        return {has_intersect, intersection_point};
    }
}
