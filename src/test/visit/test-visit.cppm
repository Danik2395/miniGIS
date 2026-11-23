module;
#include <gtest/gtest.h>
export module geotest:visit;
import gengine.types.primitives;
import gengine.visit;

TEST(visit_Visit, TransformPoint)
{
    geng::Geometry geom = geng::Point(3.0, 3.8);
    const geng::Point expected_after_transform_p(6.0, 7.6);

    geng::visit::for_each_point(geom, [](geng::Point& point){ point.x *= 2; point.y *= 2; });

    EXPECT_EQ(std::get<geng::Point>(geom), expected_after_transform_p);
}

TEST(visit_Visit, TransformLineString)
{
    geng::Geometry geom = geng::LineString({{3.0, 3.8}, {5.3, 8.0}});
    const geng::LineString expected_after_transform_p({{6.0, 7.6}, {10.6, 16.0}});

    geng::visit::for_each_point(geom, [](geng::Point& point){ point.x *= 2; point.y *= 2; });

    EXPECT_EQ(std::get<geng::LineString>(geom), expected_after_transform_p);
}

TEST(visit_Visit, TransformPolygon)
{
    geng::Geometry geom = geng::Polygon{
        {{3.0, 3.8}, {5.3, 8.0}, {2.1, 6.4}},
        {{{3.5, 4.2}, {4.1, 5.3}, {3.0, 5.7}}}
    };
    const geng::Polygon expected_after_transform_p{
        {{6.0, 7.6}, {10.6, 16.0}, {4.2, 12.8}},
        {{{7.0, 8.4}, {8.2, 10.6}, {6.0, 11.4}}}
    };

    geng::visit::for_each_point(geom, [](geng::Point& point){ point.x *= 2; point.y *= 2; });

    EXPECT_EQ(std::get<geng::Polygon>(geom), expected_after_transform_p);
}
