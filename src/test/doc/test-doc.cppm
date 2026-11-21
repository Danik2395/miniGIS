module;
#include <entt/entt.hpp>
#include <gtest/gtest.h>
export module geotest:doc;
import :base;
import gengine.doc;
import gengine.compare;
import gengine.types.precision;

class doc_AppState : public ::testing::Test
{
protected:
    geng::AppState app;
    static constexpr geng::QuantizePrecision qprec = {1e-7, 1e+7};
    static constexpr geng::IdDoc unreachable_id_aka_not_valid = 999;

    geng::IdDoc add_test_doc()
    {
        entt::registry reg;
        test::base::add_quantize_precision_to_reg(reg, qprec);
        return app.add_doc(std::move(reg));
    }

    void expect_debug_death_on_doc_access(const char* assert_find_regex)
    {
        EXPECT_DEBUG_DEATH(app.remove_doc(unreachable_id_aka_not_valid), assert_find_regex);
        EXPECT_DEBUG_DEATH(app.set_current_doc_id(unreachable_id_aka_not_valid), assert_find_regex);
        EXPECT_DEBUG_DEATH(std::ignore = app.get_doc(unreachable_id_aka_not_valid), assert_find_regex);
    }
};

TEST_F(doc_AppState, AddDocDoesNotHandleCurrendDocumentId)
{
    const auto id_current_doc_before_doc_add = app.id_current_doc();

    add_test_doc();

    const auto id_current_doc_after_doc_add = app.id_current_doc();

    EXPECT_EQ(id_current_doc_before_doc_add, id_current_doc_after_doc_add);
}

TEST_F(doc_AppState, AddDocMonotonicId)
{
    const auto doc_id1 = add_test_doc();
    const auto doc_id2 = add_test_doc();

    app.clear_all_doc();

    const auto doc_id3 = add_test_doc();

    EXPECT_TRUE(doc_id1 != doc_id2 && doc_id1 != doc_id3 && doc_id2 !=doc_id3);
}

TEST_F(doc_AppState, RemoveDocOfNonCurrentDocDoesNotAffectCerrntDoc)
{
    const auto doc_id1 = add_test_doc();
    const auto doc_id2 = add_test_doc();

    app.set_current_doc_id(doc_id1);

    app.remove_doc(doc_id2);

    const auto current_doc_id_after_not_current_doc_removal = app.id_current_doc();

    EXPECT_EQ(doc_id1, current_doc_id_after_not_current_doc_removal);
}

TEST_F(doc_AppState, RemoveDocOfCurrentDocSetCurrentDocToGuardValue)
{
    const auto id_test_doc = add_test_doc();

    app.set_current_doc_id(id_test_doc);

    app.remove_doc(id_test_doc);

    const auto current_doc_id_after_current_doc_removal = app.id_current_doc();

    EXPECT_FALSE(id_test_doc == current_doc_id_after_current_doc_removal);
}

TEST_F(doc_AppState, AfterWorkAppNoAnyDocumentAssert)
{
    const auto id_test_doc = add_test_doc();
    app.set_current_doc_id(id_test_doc);
    app.remove_doc(id_test_doc);

    expect_debug_death_on_doc_access("No any doc");
}

TEST_F(doc_AppState, EmptyAppNoAnyDocumentAssert)
{
    expect_debug_death_on_doc_access("No any doc");
}

TEST_F(doc_AppState, NoSuchDocumentAssert)
{
    const auto id_test_doc = add_test_doc();
    app.set_current_doc_id(id_test_doc);

    expect_debug_death_on_doc_access("No such doc");
}

TEST_F(doc_AppState, DocumentsOwnTheirRegistries)
{
    const auto doc_id1 = add_test_doc();
    const auto doc_id2 = add_test_doc();
    const auto doc1 = app.get_doc(doc_id1);
    const auto doc2 = app.get_doc(doc_id2);

    const bool doc1_registries_equality = &doc1.reg() == &app.get_doc(doc_id1).reg();
    const bool doc1_registry_and_doc2_registry_equality = &doc1.reg() == &doc2.reg();

    EXPECT_TRUE(doc1_registries_equality);
    EXPECT_FALSE(doc1_registry_and_doc2_registry_equality);
}

TEST_F(doc_AppState, DocObjectChangeQuantizePrecitionFromPassedRegistry)
{
    const double v1 = 5.98765432187;
    const double v2 = 5.98765431435;

    const auto id_test_doc = add_test_doc();
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
