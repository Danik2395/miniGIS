export module gengine.compare.primitives;
import gengine.compare.doubles;
import gengine.types;

export
namespace geng
{
    [[nodiscard]]
    bool is_zero(geng::Vec2 vec)
    {
        return geng::is_zero(vec.length());
    }
}
