export module gengine.types.precision;

export namespace geng
{
struct [[nodiscard]] Precision;
} // namespace geng



namespace geng
{
struct Precision
{
    double eps          = 1e-9;
    double inverted_eps = 1e+9;
};
} // namespace geng
