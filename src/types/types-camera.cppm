export module gengine.types.camera;
import gengine.types.primitives;

export namespace geng
{
struct [[nodiscard]] Camera;

struct [[nodiscard]] Viewport;
} // namespace geng



namespace geng
{
struct Camera
{
    geng::Matrix3 mtx = geng::Matrix3::Diagonal(1);
};

struct Viewport
{
    geng::Matrix3 mtx = {
        1,  0, 0,
        0, -1, 0,
        0,  0, 1,
    };
    // geng::Box box;
};
} // namespace geng
