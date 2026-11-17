add_library(miniGIS_core OBJECT)

FetchContent_Declare(
    entt
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG        v4.0.0
)

FetchContent_MakeAvailable(entt)

target_sources(miniGIS_core PUBLIC FILE_SET CXX_MODULES FILES
    src/types/types.cppm
    src/types/types-primitives.cppm
    src/types/types-precision.cppm
    src/types/types-render.cppm
    src/math/math.cppm
    src/compare/compare.cppm
    src/compare/compare-doubles.cppm
    src/compare/compare-primitives.cppm
    src/doc/doc.cppm
    src/render/render.cppm
    src/serialization/serialization.cppm
)

target_link_libraries(miniGIS_core PUBLIC EnTT::EnTT)

target_link_libraries(miniGIS_core PUBLIC miniGIS_options)
