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
    geng::Matrix3 mtx = geng::Matrix3::Diagonal(1);
};
} // namespace geng
