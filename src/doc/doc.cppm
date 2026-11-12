module;
#include <cassert>
#include <map>
#include <cstdint>
#include <utility>
#include <entt/entt.hpp>
export module gengine.doc;
import gengine.compare.doubles;
import gengine.types.precision;

export namespace geng
{
using IdDoc = uint32_t;

class [[nodiscard]] Doc;

class [[nodiscard]] AppState;
} // namespace geng



namespace geng
{
class Doc
{
    friend class geng::AppState;

    entt::registry& registry;
    geng::compare::CacheQuantizePrecision cached_quantize_precision;

    Doc(entt::registry& reg) :
        registry(reg),
        cached_quantize_precision(reg.ctx().get<geng::QuantizePrecision>())
    {};

public:
    Doc(const Doc&) = delete;
    Doc(Doc&&)      = delete;

    Doc& operator=(const Doc&) = delete;
    Doc& operator=(Doc&&)      = delete;

    entt::registry& reg()
    {
        return registry;
    }

    const entt::registry& reg() const
    {
        return registry;
    }
};

class AppState
{
    std::map<geng::IdDoc, entt::registry> documents_registers;

    geng::IdDoc current_doc_id  = 0;
    geng::IdDoc last_add_doc_id = 0;

public:
    AppState() = default;

    AppState(const AppState&) = delete;
    AppState(AppState&&)      = delete;

    AppState& operator=(const AppState&) = delete;
    AppState& operator=(AppState&&)      = delete;

    geng::IdDoc add_doc(entt::registry reg)
    {
        documents_registers.emplace(++last_add_doc_id, std::move(reg));
        return last_add_doc_id;
    }

    void remove_doc(geng::IdDoc id)
    {
        documents_registers.erase(id);

        if (id == current_doc_id)
        {
            set_current_doc_guard();
        }
    }

    void clear_all_doc()
    {
        documents_registers.clear();

        set_current_doc_guard();
    }

    void set_current_doc_id(geng::IdDoc id)
    {
        check_document_valid(id);

        current_doc_id = id;
    }

    [[nodiscard]]
    geng::IdDoc id_current_doc() const
    {
        return current_doc_id;
    }

    geng::Doc current_doc()
    {
        return get_doc(current_doc_id);
    }

    geng::Doc get_doc(geng::IdDoc id)
    {
        check_document_valid(id);

        auto& current_doc_reg = documents_registers.at(id);
        return geng::Doc(current_doc_reg);
    }

private:
    void check_document_valid(geng::IdDoc id) const
    {
        assert(!documents_registers.empty() && "AppState: No any document.");
        assert(documents_registers.find(id) != documents_registers.end() && "AppState: No such document.");
    }

    void set_current_doc_guard()
    {
        current_doc_id = 0;
    }
};
} // namespace geng
