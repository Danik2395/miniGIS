module;
#include <entt/entt.hpp>
export module gengine.camera;
import gengine.types.primitives;
import gengine.types.camera;
import gengine.types.input;
import gengine.doc;

export namespace geng::camera
{
geng::Point world_to_screen(const geng::Matrix3& mtx, geng::Point p);

geng::Matrix3 get_transform_matrix(const geng::Doc& doc);
} // namespace geng::camera



namespace geng::camera
{
geng::Point world_to_screen(const geng::Matrix3& mtx, geng::Point p)
{
    return mtx * p;
}

geng::Matrix3 create_viewport_matrix(const geng::Viewport viewport)
{
    return {
        1,  0, 0,
        0, -1, viewport.height,
        0,  0, 1,
    };
}

geng::Matrix3 create_translation_matrix(const geng::Camera camera)
{
    return {
        1, 0, -camera.offset_x,
        0, 1, -camera.offset_y,
        0, 0, 1,
    };
}

geng::Matrix3 get_transform_matrix(const geng::Doc& doc)
{
    const auto& camera   = doc.reg().ctx().get<geng::Camera>();
    const auto& viewport = doc.reg().ctx().get<geng::Viewport>();

    const auto translation_matrix = geng::camera::create_translation_matrix(camera);
    const auto viewport_matrix = geng::camera::create_viewport_matrix(viewport);

    return viewport_matrix * translation_matrix;
}
} // namespace geng::camera
