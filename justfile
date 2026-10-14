BUILD_DIR := "./build"
DEBUG_DIR := "./build/debug"
TEST_DIR  := "./build/debug"

default:
    @just --list

clean:
    @rm -rf {{BUILD_DIR}} .cache

debug:
    @mkdir -p {{DEBUG_DIR}}
    @cmake --preset debug
    @cmake --build --preset debug
    @ln -s -r {{DEBUG_DIR}}/compile_commands.json {{BUILD_DIR}} || true

test-all: debug
    @ctest --test-dir {{TEST_DIR}} --output-on-failure

test test_suite: debug
    @ctest --test-dir {{TEST_DIR}} --output-on-failure -R "^{{test_suite}}/."

testf test_full_name: debug
    @ctest --test-dir {{TEST_DIR}} --output-on-failure -R "^{{test_full_name}}$"

test-list:
    @ctest --test-dir {{TEST_DIR}} -N
