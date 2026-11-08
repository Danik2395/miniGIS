module;
#include <gtest/gtest.h>
#include <entt/entt.hpp>
export module geotest:base;
import gengine.doc;
import gengine.types.precision;

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

        add_quantize_precision_to_reg(registry);

        return registry;
    }

    void add_quantize_precision_to_reg(entt::registry& reg)
    {
        reg.ctx().emplace<geng::QuantizePrecision>(1e-9, 1e+9);
    }
};
