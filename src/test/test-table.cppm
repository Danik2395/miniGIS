module;
#include <concepts>
#include <ranges>
#include <string>
#include <gtest/gtest.h>
export module geotest:table;

namespace test::table
{
template<typename S>
concept StringOrCString = std::same_as<std::remove_cvref_t<S>, std::string> ||
                          std::same_as<std::remove_cvref_t<S>, const char*>;

template<typename ArSt>
concept ArrangeStruct = requires (const ArSt& arst)
{
    { arst.name } -> test::table::StringOrCString;
};

template<typename Container>
concept Table = std::ranges::forward_range<Container> &&
                test::table::ArrangeStruct<std::ranges::range_value_t<Container>>;

template<typename Fn, typename ArSt>
concept TableTestFunc = requires (Fn fn, ArSt arst)
{
    requires test::table::ArrangeStruct<ArSt>;
    { fn(arst) } -> std::same_as<void>;
};

template<test::table::Table T, test::table::TableTestFunc<std::ranges::range_value_t<T>> Fn>
void run_test_table(const T& table, Fn fn)
{
    for (const auto& table_case : table)
    {
        SCOPED_TRACE(testing::Message() << "Case: " << table_case.name);
        fn(table_case);
    }
}
} // namespace test::table
