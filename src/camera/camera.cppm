module;
#include <entt/entt.hpp>
export module gengine.camera;
import gengine.types.primitives;
import gengine.types.camera;
import gengine.doc;

export namespace geng::camera
{
geng::Point world_to_screen(const geng::Matrix3& mtx, geng::Point p);

geng::Matrix3 get_transform_matrix(const geng::Doc& doc);

void update_viewport(geng::Doc& doc, double vh, double vw);
} // namespace geng::camera



namespace geng::camera
{
geng::Point world_to_screen(const geng::Matrix3& mtx, geng::Point p)
{
    return mtx * p;
}

geng::Matrix3 get_transform_matrix(const geng::Doc& doc)
{
    const auto& translation_matrix = doc.reg().ctx().get<geng::Camera>().mtx;
    const auto& viewport_matrix = doc.reg().ctx().get<geng::Viewport>().mtx;

    return viewport_matrix * translation_matrix;
}
} // namespace geng::camera
