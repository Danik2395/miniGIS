module;
#include <concepts>
#include <ranges>
#include <algorithm>
#include <utility>
#include <variant>
export module gengine.visit;
import gengine.types.primitives;

namespace geng::visit
{
template<typename Fn, typename PointT>
concept ForEachPFunc = requires (Fn fn, PointT& p)
{
    { fn(p) } -> std::same_as<void>;
};

template<typename PassedGeometry, typename TargetGeometry>
concept DecaysTo = std::same_as<std::remove_cvref_t<PassedGeometry>, TargetGeometry>;

template<typename Fn>
struct ForEachPVisiter
{
    Fn&& fn;

    void operator()(this auto&& self, geng::visit::DecaysTo<geng::Point> auto&& p)
    {
        self.fn(p);
    }

    void operator()(this auto&& self, geng::visit::DecaysTo<geng::LineString> auto&& line)
    {
        std::ranges::for_each(line.points, self.fn);
    }

    void operator()(this auto&& self, geng::visit::DecaysTo<geng::Polygon> auto&& poly)
    {
        auto inner_poly_points = poly.inner | std::views::join;
        std::ranges::for_each(inner_poly_points, self.fn);
        std::ranges::for_each(poly.outer, self.fn);
    }
};
} // namespace geng::visit



export namespace geng::visit
{
template<typename GeomT, typename Fn>
    requires std::same_as<std::remove_const_t<GeomT>, geng::Geometry> &&
             geng::visit::ForEachPFunc<Fn, std::conditional_t<std::is_const_v<GeomT>, const geng::Point, geng::Point>>
void for_each_point(GeomT& geom, Fn&& fn)
{
    std::visit(geng::visit::ForEachPVisiter<Fn>{std::forward<Fn>(fn)}, geom);
}
} // namespace geng::visit
