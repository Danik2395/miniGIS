add_library(miniGIS_options INTERFACE)

target_compile_options(miniGIS_options INTERFACE
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wshadow
    -Werror
)

if(ENABLE_SANITIZERS)
    target_compile_options(miniGIS_options INTERFACE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )

    target_link_options(miniGIS_options INTERFACE
        -fsanitize=address,undefined
    )
endif()

if(ENABLE_COVERAGE)
    target_compile_options(miniGIS_options INTERFACE
        -fprofile-instr-generate
        -fcoverage-mapping
    )

    target_link_options(miniGIS_options INTERFACE
        -fprofile-instr-generate
        -fcoverage-mapping
    )
endif()
