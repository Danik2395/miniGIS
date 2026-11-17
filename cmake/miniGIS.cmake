add_executable(${PROJECT_NAME} WIN32)

target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
    src/ui/gappwindow.h
    src/ui/gappwindow.cpp
    src/ui/gappwindow.ui
    src/ui/gcanvas.h
    src/ui/gcanvas.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${PROJECT_NAME}_core
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
