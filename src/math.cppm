module;
#include <cmath>
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
}
