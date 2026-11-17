BUILD_DIR     := justfile_directory() + "/build"
DEBUG_DIR     := BUILD_DIR + "/debug"
DEBUG_SAN_DIR := BUILD_DIR + "/debug-san"
TEST_DIR      := BUILD_DIR + "/debug"

default:
    @just --list

clean:
    @rm -rf {{BUILD_DIR}} .cache Testing

debug:
    @mkdir -p {{DEBUG_DIR}}
    @cmake --preset debug
    @cmake --build --preset debug
    @ln -s -r {{DEBUG_DIR}}/compile_commands.json {{BUILD_DIR}} || true

debug-san:
    @mkdir -p {{DEBUG_SAN_DIR}}
    @cmake --preset debug-san
    @cmake --build --preset debug-san
    @ln -s -r {{DEBUG_SAN_DIR}}/compile_commands.json {{BUILD_DIR}} || true

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
