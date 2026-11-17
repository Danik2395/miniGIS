add_executable(miniGIS WIN32)

target_sources(miniGIS PRIVATE
    src/main.cpp
    src/ui/gappwindow.h
    src/ui/gappwindow.cpp
    src/ui/gappwindow.ui
    src/ui/gcanvas.h
    src/ui/gcanvas.cpp
)

target_link_libraries(miniGIS PRIVATE
    miniGIS_core
    miniGIS_options
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

target_include_directories(miniGIS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
