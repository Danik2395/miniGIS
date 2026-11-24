export module gengine.types.camera;
import gengine.types.primitives;

export namespace geng
{
struct [[nodiscard]] Camera;
} // namespace geng



namespace geng
{
struct Camera
{
    double x_offset = 0;
    double y_offset = 0;
};
} // namespace geng
