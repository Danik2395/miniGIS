module;
#include <filesystem>
#include <stdexcept>
#include <ranges>
#include <entt/entt.hpp>
export module gengine.serialization;
import gengine.types.precision;
import gengine.types.primitives;
import gengine.types.render;

export namespace geng::serial
{
entt::registry reg_from_file(const std::filesystem::path& path);
} // namespace geng



namespace hardcode
{
auto get_start_to_end_axis_coordinates()
{
    const int start       = -1000;
    const int spacing     = 100;
    const int lines_count = 1000 * 2 / spacing;

    auto lines_iter = std::views::iota(0, lines_count);

    auto coord_range = lines_iter | std::views::transform([](int i){ return start + i * spacing; });

    return coord_range;
}

void emplace_object(entt::registry& reg, geng::Geometry&& obj, geng::Style& style)
{
    auto obj_entity = reg.create();

    reg.emplace<geng::Geometry>(obj_entity, std::move(obj));
    reg.emplace<geng::Style>(obj_entity, style);
}

void create_lines_grid(entt::registry& reg)
{
    auto get_line_x = [](int line_coord) {

        geng::Point x_start = {-1e3, static_cast<double>(line_coord)};
        geng::Point x_end   = { 1e3, static_cast<double>(line_coord)};

        geng::LineString line_x = {{x_start, x_end}};

        return line_x;
    };

    auto get_line_y = [](int line_coord) {

        geng::Point y_start = {static_cast<double>(line_coord), -1e3};
        geng::Point y_end   = {static_cast<double>(line_coord),  1e3};

        geng::LineString line_y = {{y_start, y_end}};

        return line_y;
    };

    auto get_line_style = []() {
        return geng::Style(geng::Color::RGB(0x0000FF), geng::Color(), 2.0f);
    };

    auto coord_range = get_start_to_end_axis_coordinates();

    for (int line_coord : coord_range)
    {
        auto line_x = get_line_x(line_coord);
        auto line_y = get_line_y(line_coord);

        auto line_style = get_line_style();

        emplace_object(reg, std::move(line_x), line_style);
        emplace_object(reg, std::move(line_y), line_style);
    }
}

void create_points_grid(entt::registry& reg)
{
    auto get_point_style = []() {
        return geng::Style(geng::Color::RGB(0xFF00FF), geng::Color(), 16.888f);
    };

    auto coord_range = get_start_to_end_axis_coordinates();

    auto points_grid = std::views::cartesian_product(coord_range, coord_range);

    for (auto [x, y] : points_grid)
    {
        auto point_style = get_point_style();

        emplace_object(reg, geng::Point(x, y), point_style);
    }
}

void create_poly_grid(entt::registry& reg)
{
    auto get_point_style = []() {
        return geng::Style(geng::Color::RGB(0xC6658F), geng::Color::RGBA(0x8F83F5A), 3.0f);
    };

    auto get_poly = [](int x, int y) {
        geng::Polygon poly;

        poly.outer = {
            {10.0 + x, 10.0 + y},
            {90.0 + x, 10.0 + y},
            {90.0 + x, 70.0 + y},
            {70.0 + x, 90.0 + y},
            {10.0 + x, 90.0 + y},
            {10.0 + x, 10.0 + y}
        };

        poly.inner = {
            {
                {35.0 + x, 35.0 + y},
                {35.0 + x, 65.0 + y},
                {65.0 + x, 65.0 + y},
                {65.0 + x, 35.0 + y},
                {35.0 + x, 35.0 + y}
            }
        };

        return poly;
    };

    auto coord_range = get_start_to_end_axis_coordinates();

    auto poly_grid = std::views::cartesian_product(coord_range, coord_range);

    for (auto [x, y] : poly_grid)
    {
        auto poly = get_poly(x, y);

        auto poly_style = get_point_style();

        emplace_object(reg, std::move(poly), poly_style);
    }
}

void create_test_objects(entt::registry& reg)
{
    create_lines_grid(reg);
    create_points_grid(reg);
    create_poly_grid(reg);
}
} // namespace hardcode



namespace geng::serial
{
entt::registry reg_from_file(const std::filesystem::path& path)
{
    // п.55
    if(!path.empty())
    {
        throw std::invalid_argument("Empty path needed for hardcoded scene.");
    }

    entt::registry registry;

    registry.ctx().emplace<geng::QuantizePrecision>(1e-9, 1e+9);

    hardcode::create_test_objects(registry);

    return registry;
}
} // namespace geng
