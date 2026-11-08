export module gengine.types.precision;

export namespace geng
{
struct [[nodiscard]] Precision;

struct [[nodiscard]] QuantizePrecision;
} // namespace geng



namespace geng
{
struct Precision
{
    double eps          = 1e-9;
    double inverted_eps = 1e+9;

    Precision() = default;

    Precision(double eps, double inverted_eps) : eps(eps), inverted_eps(inverted_eps) {}
};

struct QuantizePrecision : public Precision
{
    using Precision::Precision;

    QuantizePrecision(const geng::Precision& prec) : Precision(prec) {}
};
} // namespace geng
