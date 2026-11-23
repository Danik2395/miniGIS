module;
#include <vector>
#include <algorithm>
export module gengine.looprunner;
import gengine.types;
import gengine.render;
import gengine.doc;
import gengine.visit;
import gengine.camera;

export namespace geng::looprunner
{
std::vector<geng::RenderUnit> run_frame(const geng::Doc& doc);
} // namespace geng::looprunner



namespace geng::looprunner
{
std::vector<geng::RenderUnit> run_frame(const geng::Doc& doc)
{
    auto render_sequence = geng::render::query_draw_sequence(doc);

    const auto transform_mtx = geng::camera::get_transform_matrix(doc);

    std::ranges::for_each(render_sequence, [&transform_mtx](auto& unit){
            geng::visit::for_each_point(unit.geometry, [&transform_mtx](geng::Point& p){
                    p = geng::camera::world_to_screen(transform_mtx, p);
                    });
            });

    return render_sequence;
}
} // namespace geng::looprunner
