module;
#include <cmath>
export module gengine.types:math;
import :primitives;

export
{
    namespace geng
    {
        struct Vec2
        {
            double x, y;

            Vec2() = default;

            Vec2(double x, double y) : x(x), y(y) {}

            explicit Vec2(geng::Point p0, geng::Point p1) :
                x(p1.x - p0.x),
                y(p1.y - p0.y)
            {}

            double operator*(Vec2 other_vec)
            {
                return this->x * other_vec.x + this->y * other_vec.y;
            }

            Vec2 operator*(double scalar)
            {
                return {this->x * scalar, this->y * scalar};
            }

            Vec2 operator+(Vec2 other_vec)
            {
                return {this->x + other_vec.x, this->y + other_vec.y};
            }

            Vec2 operator-(Vec2 other_vec)
            {
                return {this->x - other_vec.x, this->y - other_vec.y};
            }

            double projection(Vec2 vec_projected)
            {
                return (*this * vec_projected) / (*this * *this);
            }

            static double abs(Vec2 vec)
            {
                return std::hypot(vec.x, vec.y);
            }
        };

        struct Matrix3
        {
            double m[3][3];

            Matrix3 operator*(const Matrix3& other);
        };
    }
}
