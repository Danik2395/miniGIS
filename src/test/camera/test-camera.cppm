module;
#include <gtest/gtest.h>
export module geotest:camera;
import :table;
import :base;
import gengine.types;
import gengine.camera;

class camera_Camera : public test::base::GeoTestBase {};

TEST_F(camera_Camera, ThroughTestOfWorldToScreen)
{
    auto doc = app.get_current_doc();

    const geng::Matrix3 imitate_pan_mtx = {
        1,  0, -200,
        0,  1, -200,
        0,  0,  1,
    };
    doc.reg().ctx().get<geng::Camera>().mtx = imitate_pan_mtx;

    const double vh = 500;
    const double vw = 500;
    geng::camera::update_viewport(doc, vh, vw);

    const geng::Matrix3 transform_mtx = geng::camera::get_transform_matrix(doc);
    const geng::Point world_point = {250.0, 210.0};
    const geng::Point expected_screen_point = {50.0, 490.0};

    const geng::Point result_screen_point = geng::camera::world_to_screen(transform_mtx, world_point);

    EXPECT_EQ(result_screen_point, expected_screen_point);
}
