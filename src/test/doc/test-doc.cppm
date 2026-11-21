module;
#include <entt/entt.hpp>
#include <gtest/gtest.h>
export module geotest:doc;
import :base;
import gengine.doc;
import gengine.compare;
import gengine.types.precision;

TEST(doc_AppState, AddDocDoesNotHandleCurrendDocumentId)
{
    geng::AppState app;
    entt::registry reg;
    const geng::QuantizePrecision qprec = {1e-7, 1e+7};
    test::base::add_quantize_precision_to_reg(reg, qprec);

    const auto id_current_doc_before_doc_add = app.id_current_doc();
    app.add_doc(std::move(reg));

    const auto id_current_doc_after_doc_add = app.id_current_doc();

    EXPECT_EQ(id_current_doc_before_doc_add, id_current_doc_after_doc_add);
}

TEST(doc_AppState, AddDocMonotonicId)
{
    geng::AppState app;
    const geng::QuantizePrecision qprec = {1e-7, 1e+7};

    entt::registry reg1;
    test::base::add_quantize_precision_to_reg(reg1, qprec);
    const auto doc_id1 = app.add_doc(std::move(reg1));

    entt::registry reg2;
    test::base::add_quantize_precision_to_reg(reg2, qprec);
    const auto doc_id2 = app.add_doc(std::move(reg2));

    app.clear_all_doc();

    entt::registry reg3;
    test::base::add_quantize_precision_to_reg(reg3, qprec);
    const auto doc_id3 = app.add_doc(std::move(reg3));

    EXPECT_TRUE(doc_id1 != doc_id2 && doc_id1 != doc_id3 && doc_id2 !=doc_id3);
}

TEST(doc_AppState, RemoveDocOfNonCurrentDocDoesNotAffectCerrntDoc)
{
    geng::AppState app;
    const geng::QuantizePrecision qprec = {1e-7, 1e+7};

    entt::registry reg1;
    test::base::add_quantize_precision_to_reg(reg1, qprec);
    const auto doc_id1 = app.add_doc(std::move(reg1));

    entt::registry reg2;
    test::base::add_quantize_precision_to_reg(reg2, qprec);
    const auto doc_id2 = app.add_doc(std::move(reg2));

    app.set_current_doc_id(doc_id1);

    app.remove_doc(doc_id2);

    const auto current_doc_id_after_not_current_doc_removal = app.id_current_doc();

    EXPECT_EQ(doc_id1, current_doc_id_after_not_current_doc_removal);
}

TEST(doc_AppState, RemoveDocOfCurrentDocSetCurrentDocToGuardValue)
{
    geng::AppState app;
    entt::registry reg;
    const geng::QuantizePrecision qprec = {1e-7, 1e+7};
    test::base::add_quantize_precision_to_reg(reg, qprec);

    const auto id_test_doc = app.add_doc(std::move(reg));

    app.set_current_doc_id(id_test_doc);

    app.remove_doc(id_test_doc);

    const auto current_doc_id_after_current_doc_removal = app.id_current_doc();

    EXPECT_FALSE(id_test_doc == current_doc_id_after_current_doc_removal);
}

TEST(doc_AppState, AfterWorkAppNoAnyDocumentAssert)
{
    geng::AppState app;
    const geng::IdDoc id = 5;
    entt::registry reg;
    const geng::QuantizePrecision qprec = {1e-7, 1e+7};
    test::base::add_quantize_precision_to_reg(reg, qprec);

    const auto id_test_doc = app.add_doc(std::move(reg));
    app.set_current_doc_id(id_test_doc);
    app.remove_doc(id_test_doc);

    EXPECT_DEBUG_DEATH(app.remove_doc(id), "No any doc");
    EXPECT_DEBUG_DEATH(app.set_current_doc_id(id), "No any doc");
    EXPECT_DEBUG_DEATH(std::ignore = app.get_doc(id), "No any doc");
}

TEST(doc_AppState, EmptyAppNoAnyDocumentAssert)
{
    geng::AppState app;
    const geng::IdDoc id = 5;

    EXPECT_DEBUG_DEATH(app.remove_doc(id), "No any doc");
    EXPECT_DEBUG_DEATH(app.set_current_doc_id(id), "No any doc");
    EXPECT_DEBUG_DEATH(std::ignore = app.get_doc(id), "No any doc");
}

TEST(doc_AppState, NoSuchDocumentAssert)
{
    geng::AppState app;
    const geng::IdDoc id = 5;
    entt::registry reg;
    const geng::QuantizePrecision qprec = {1e-7, 1e+7};
    test::base::add_quantize_precision_to_reg(reg, qprec);

    const auto id_test_doc = app.add_doc(std::move(reg));
    app.set_current_doc_id(id_test_doc);

    EXPECT_DEBUG_DEATH(app.remove_doc(id), "No such doc");
    EXPECT_DEBUG_DEATH(app.set_current_doc_id(id), "No such doc");
    EXPECT_DEBUG_DEATH(std::ignore = app.get_doc(id), "No such doc");
}

TEST(doc_AppState, DocObjectChangeQuantizePrecitionFromPassedRegistry)
{
    geng::AppState app;
    entt::registry reg;
    const double v1 = 5.98765432187;
    const double v2 = 5.98765431435;
    const geng::QuantizePrecision qprec = {1e-7, 1e+7};
    test::base::add_quantize_precision_to_reg(reg, qprec);

    const auto id_test_doc = app.add_doc(std::move(reg));
    const bool values_equality_on_default_precision_after_doc_added = geng::is_equal(v1, v2);
    EXPECT_FALSE(values_equality_on_default_precision_after_doc_added);

    app.set_current_doc_id(id_test_doc);
    const bool values_equality_with_current_doc_set = geng::is_equal(v1, v2);
    EXPECT_FALSE(values_equality_with_current_doc_set);

    {
        const auto doc = app.get_current_doc();
        const bool values_equality_after_current_doc_acquisition = geng::is_equal(v1, v2);
        EXPECT_TRUE(values_equality_after_current_doc_acquisition);
    }

    const bool values_equality_on_reset_default_precision_after_doc_expired = geng::is_equal(v1, v2);
    EXPECT_FALSE(values_equality_on_reset_default_precision_after_doc_expired);
}
