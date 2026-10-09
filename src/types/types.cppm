module;
#include <vector>
export module gengine.types;
export import :math;

export
{
    namespace geng
    {
        struct Point
        {
            double x, y;
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
    }
}
