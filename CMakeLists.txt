cmake_minimum_required(VERSION 3.28)
project(miniGIS VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)

include(FetchContent)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_library(${PROJECT_NAME}_core OBJECT)

target_sources(${PROJECT_NAME}_core PUBLIC FILE_SET CXX_MODULES FILES
    src/types/types.cppm
    src/types/types-primitives.cppm
    src/math.cppm
)

add_executable(${PROJECT_NAME} WIN32)

target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${PROJECT_NAME}_core
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

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
        src/test/test-math.cppm
    )

    target_link_libraries(${PROJECT_NAME}_tests PRIVATE
        ${PROJECT_NAME}_core
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}_tests)
endif()
