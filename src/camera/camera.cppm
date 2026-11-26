module;
#include <entt/entt.hpp>
export module gengine.camera;
import gengine.types.primitives;
import gengine.types.camera;
import gengine.types.input;
import gengine.doc;

export namespace geng::camera
{
void update_camera_on_mouse_move(geng::Doc& doc);

geng::Point world_to_screen(const geng::Matrix3& mtx, geng::Point p);

geng::Point screen_to_world(const geng::Matrix3& mtx, geng::Point p);

geng::Matrix3 get_transform_matrix(const geng::Doc& doc);
} // namespace geng::camera



namespace geng::camera
{
void update_camera_on_mouse_move(geng::Doc& doc)
{
    auto& mouse = doc.reg().ctx().get<geng::Mouse>();

    // п.77
    // if (config.mouse_middle_button_pan)
    // {
    // if (config.pan_button)
    if (mouse.buttons.b1_pressed)
    {
        auto& camera = doc.reg().ctx().get<geng::Camera>();

        camera.x_offset -= mouse.pos.x - mouse.last_pos.x;
        camera.y_offset += mouse.pos.y - mouse.last_pos.y;
    }
    // }
}

geng::Point world_to_screen(const geng::Matrix3& mtx, geng::Point p)
{
    return mtx * p;
}

geng::Point screen_to_world(const geng::Matrix3& mtx, geng::Point p)
{
    return mtx.inverse() * p;
}

geng::Matrix3 create_viewport_coordinates_normalization_matrix(const geng::Viewport viewport)
{
    return {
        1,  0, 0,
        0, -1, viewport.height,
        0,  0, 1,
    };
}

geng::Matrix3 create_pan_matrix(const geng::Camera camera)
{
    return {
        1, 0, -camera.x_offset,
        0, 1, -camera.y_offset,
        0, 0, 1,
    };
}

geng::Matrix3 create_translation_matrix(const geng::Camera camera)
{
    auto pan_mtx = geng::camera::create_pan_matrix(camera);

    return pan_mtx;
}

geng::Matrix3 get_transform_matrix(const geng::Doc& doc)
{
    const auto& camera   = doc.reg().ctx().get<geng::Camera>();
    const auto& viewport = doc.reg().ctx().get<geng::Viewport>();

    const auto translation_matrix = geng::camera::create_translation_matrix(camera);
    const auto viewport_matrix = geng::camera::create_viewport_coordinates_normalization_matrix(viewport);

    return viewport_matrix * translation_matrix;
}
} // namespace geng::camera
