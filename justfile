CURRENT_DIR := justfile_directory()
BUILD_DIR   := CURRENT_DIR + "/build"
TEST_DIR    := BUILD_DIR   + "/debug"

default:
    @just --list

list: default

clean:
    @rm -rf {{BUILD_DIR}} .cache Testing

_debug preset:
    @mkdir -p {{BUILD_DIR}}/{{preset}}
    @cmake --preset {{preset}}
    @cmake --build --preset {{preset}}
    @ln -srf {{BUILD_DIR}}/{{preset}}/compile_commands.json {{BUILD_DIR}} || true

debug:     (_debug "debug")

debug-san: (_debug "debug-san")

_test test_command: debug
    @ctest --test-dir {{TEST_DIR}} --output-on-failure {{test_command}}

test-all:
    @just _test ''

test test_suite:
    @just _test '-R "^.*_{{test_suite}}\."'

testm test_module:
    @just _test '-R "^{{test_module}}_"'

testf test_full_name:
    @just _test '-R "^{{test_full_name}}$"'

test-list:
    @ctest --test-dir {{TEST_DIR}} -N

cov mod:
    @rm -rf "{{TEST_DIR}}/coverage" "{{BUILD_DIR}}/coverage" && mkdir -p "{{TEST_DIR}}/coverage"
    @mkdir -p "{{BUILD_DIR}}/coverage"
    @LLVM_PROFILE_FILE="{{TEST_DIR}}/coverage/%p.profraw" just testm '{{mod}}'
    @llvm-profdata merge -sparse "{{TEST_DIR}}/coverage/"*.profraw -o "{{TEST_DIR}}/coverage/all.profdata"
    @llvm-cov show {{TEST_DIR}}/miniGIS_tests \
        -instr-profile="{{TEST_DIR}}/coverage/all.profdata" \
        -output-dir="{{BUILD_DIR}}/coverage" \
        -format=html \
        -show-directory-coverage=true \
        --show-branches=count \
        --ignore-filename-regex='(src/test|src/ui|build)' \
        --include-filename-regex='src/{{mod}}/'

cov-all: (cov '.*')
