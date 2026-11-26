export module gengine.types.input;
import gengine.types.primitives;

export namespace geng
{
struct [[nodiscard]] Viewport;

struct [[nodiscard]] MouseButtons;

struct [[nodiscard]] Mouse;
} // namespace geng



namespace geng
{
struct Viewport
{
    double height = 0;
    double width = 0;
    // geng::Box box;
};

struct MouseButtons
{
    bool b1_pressed = false;
    bool b2_pressed = false;
    bool b3_pressed = false;
};

struct Mouse
{
    geng::Point last_pos;
    geng::Point pos;

    geng::MouseButtons buttons;
};
} // namespace geng
