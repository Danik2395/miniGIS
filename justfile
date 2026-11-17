BUILD_DIR := justfile_directory() + "/build"
TEST_DIR  := BUILD_DIR + "/debug"

default:
    @just --list

clean:
    @rm -rf {{BUILD_DIR}} .cache Testing

_debug preset:
    @mkdir -p {{BUILD_DIR}}/{{preset}}
    @cmake --preset {{preset}}
    @cmake --build --preset {{preset}}
    @ln -srf {{BUILD_DIR}}/{{preset}}/compile_commands.json {{BUILD_DIR}} || true

debug:     (_debug "debug")

debug-san: (_debug "debug-san")

test-all: debug
    @ctest --test-dir {{TEST_DIR}} --output-on-failure

test test_suite: debug
    @ctest --test-dir {{TEST_DIR}} --output-on-failure -R "^{{test_suite}}\."

testf test_full_name: debug
    @ctest --test-dir {{TEST_DIR}} --output-on-failure -R "^{{test_full_name}}$"

test-list:
    @ctest --test-dir {{TEST_DIR}} -N

cov: debug
    @rm -rf "{{TEST_DIR}}/coverage" && mkdir -p "{{TEST_DIR}}/coverage"
    @mkdir -p "{{BUILD_DIR}}/coverage"
    @LLVM_PROFILE_FILE="{{TEST_DIR}}/coverage/%p.profraw" ctest --test-dir {{TEST_DIR}} --output-on-failure
    @llvm-profdata merge -sparse "{{TEST_DIR}}/coverage/"*.profraw -o "{{TEST_DIR}}/coverage/all.profdata"
    @llvm-cov show {{TEST_DIR}}/miniGIS_tests \
        -instr-profile="{{TEST_DIR}}/coverage/all.profdata" \
        -output-dir="{{BUILD_DIR}}/coverage" \
        -format=html \
        -show-directory-coverage=true \
        --show-branches=count \
        --ignore-filename-regex='src/test' \
        src/
