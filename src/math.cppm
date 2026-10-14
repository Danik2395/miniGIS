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
        double dy = segment_p0.y - segment_p1.y;
        double dx = segment_p0.x - segment_p1.x;

        double a =  dy;
        double b = -dx;
        double c = segment_p1.y * dx - segment_p1.x * dy;

        if (segment_p0 == segment_p1)
        {
            return calc_distance_euclidean(p, segment_p0);
        }

        return std::abs(a * p.x + b * p.y + c) / std::hypot(a, b);
    }
}
