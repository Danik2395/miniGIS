module;
#include <gtest/gtest.h>
#include <entt/entt.hpp>
export module geotest:base;
import gengine.doc;
import gengine.types;
import gengine.camera;

namespace test::base
{
void add_quantize_precision_to_reg(entt::registry& reg, const geng::QuantizePrecision qprec)
{
    reg.ctx().emplace<geng::QuantizePrecision>(qprec);
}

class GeoTestBase : public ::testing::Test
{
protected:
    geng::AppState app;

    void SetUp() override
    {
        auto clean_reg = build_clean_registry();

        auto clean_doc_id = app.add_doc(std::move(clean_reg));
        app.set_current_doc_id(clean_doc_id);
    }

    void TearDown() override
    {
        app.clear_all_doc();
    }

private:
    entt::registry build_clean_registry()
    {
        auto registry = entt::registry();

        add_quantize_precision_to_reg(registry, {1e-7, 1e+7});

        registry.ctx().emplace<geng::Camera>();

        registry.ctx().emplace<geng::Viewport>();

        registry.ctx().emplace<geng::Mouse>();

        return registry;
    }
};
} // namespace test::base
