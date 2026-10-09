export module gengine.types:math;

export
{
    namespace geng
    {
        struct Vec2d
        {
            double x, y;
        };

        struct Matrix3
        {
            double m[3][3];

            Matrix3 operator*(const Matrix3& other);
        };
    }
}
