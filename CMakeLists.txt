cmake_minimum_required(VERSION 3.28)
project(miniGIS VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(FetchContent)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

include(cmake/core.cmake)

include(cmake/miniGIS.cmake)

include(cmake/tests.cmake)
