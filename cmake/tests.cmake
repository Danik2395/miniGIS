if(BUILD_TESTS)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/b66cffcd5f5d6ee34a4f96d57bf016d9a22cb023.zip
    )

    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(${PROJECT_NAME}_tests)

    target_sources(${PROJECT_NAME}_tests PRIVATE FILE_SET CXX_MODULES FILES
        src/test/test.cppm
        src/test/test-base.cppm
        src/test/math/test-math_area.cppm
        src/test/math/test-math_distance.cppm
        src/test/math/test-math_intersection.cppm
        src/test/math/test-math_orientation.cppm
        src/test/math/test-math_predicates.cppm
        src/test/math/test-math_relations.cppm
        src/test/types/test-types_matrix3.cppm
        src/test/types/test-types_point.cppm
        src/test/types/test-types_vec2.cppm
        src/test/types/test-types_segment.cppm
        src/test/types/test-types_render.cppm
        src/test/compare/test-compare.cppm
    )

    target_precompile_headers(${PROJECT_NAME}_tests PRIVATE
        <gtest/gtest.h>
    )

    target_link_libraries(${PROJECT_NAME}_tests PRIVATE
        ${PROJECT_NAME}_core
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}_tests)
endif()
