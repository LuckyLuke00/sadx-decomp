cmake_minimum_required(VERSION 3.25)
project(decomp C CXX)

# Only the game's own compiler can produce matching code. Build through
# tools/check.py, which points CMake at the VC++ 2010 SP1 toolchain in .toolchain.
if(NOT MSVC_VERSION EQUAL 1600)
    message(FATAL_ERROR "Needs VC++ 2010 SP1 (cl 16.00.40219.01). Build with: python tools/check.py gate")
endif()

# Code generation. The static CRT is the default; game.cmake can change it.
# The base flags are the ones every code group shares. The rest differ per
# group (data/codegen-groups.csv): check.py writes them per source file into
# codegen-groups.cmake, from the addresses of the FUNCTIONs in each file.
set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded)
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT Embedded)
set(CMAKE_C_FLAGS_RELWITHDEBINFO "/fp:precise /DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/fp:precise /DNDEBUG")
# /DEBUG is added per target, so the self-test original gets no PDB.
set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/INCREMENTAL:NO")
include("${CMAKE_BINARY_DIR}/codegen-groups.cmake")

# The game: build/game.exe from src/. /DEBUG is for reccmp, which needs the PDB.
# Most decompiled functions have no caller yet, so /OPT:NOREF keeps them, and
# /OPT:NOICF keeps identical ones apart so each keeps its own name. /FIXED:NO
# keeps the relocations even with ASLR off: they tell reccmp which numbers in
# our code are addresses.
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS src/*.c src/*.cpp)
# The game's objects sit in its exe in link order, and the linker keeps the first copy of a function that
# several objects hold, such as a header function. codegen-groups.cmake lists the files with FUNCTIONs by
# lowest address; they link first in that order, the rest follow in path order.
list(TRANSFORM GAME_LINK_ORDER PREPEND "${CMAKE_SOURCE_DIR}/")
list(REMOVE_ITEM GAME_SOURCES ${GAME_LINK_ORDER})
list(PREPEND GAME_SOURCES ${GAME_LINK_ORDER})
add_executable(game ${GAME_SOURCES})
target_link_options(game PRIVATE /DEBUG /OPT:NOREF /OPT:NOICF /FIXED:NO)
# check.py writes library.rsp: an /INCLUDE for every function in src/library.csv,
# so each one is linked and reccmp scores it.
target_link_options(game PRIVATE "@${CMAKE_BINARY_DIR}/library.rsp")
set_property(TARGET game APPEND PROPERTY LINK_DEPENDS "${CMAKE_BINARY_DIR}/library.rsp")
# link adds the C++ runtime library by itself only for code that includes a C++
# header, so an /INCLUDE of a C++ runtime function needs it named. It follows the
# runtime that game.cmake may pick.
target_link_libraries(game PRIVATE
    $<IF:$<STREQUAL:$<TARGET_PROPERTY:game,MSVC_RUNTIME_LIBRARY>,MultiThreadedDLL>,msvcprt.lib,libcpmt.lib>)
# The game's own settings: the PE header flags, and anything else only this
# game needs. Each game writes its own (docs/PORTING.md).
include("${CMAKE_SOURCE_DIR}/game.cmake")

# Pipeline self-test, part of `check.py ci`. selftest_original stands in for
# a retail binary: no PDB, deterministic bytes. SELFTEST is its decompiled
# twin, which reccmp scores against it. Both keep the flags that the original's
# pinned hash and tests/selftest/expected.json were made with.
set(SELFTEST_FLAGS /O2 /Oi /Oy- /GS /Gy)
set(SELFTEST_LINK_FLAGS /OPT:REF /OPT:ICF)
# Both builds hold the /GL pair, compiled with /GL as a code group's flags would
# do it. The link then restarts with /LTCG by itself.
set(SELFTEST_GL_SOURCES tests/selftest/gl-caller.cpp tests/selftest/gl-callee.cpp)
set_source_files_properties(${SELFTEST_GL_SOURCES} PROPERTIES COMPILE_OPTIONS /GL)
add_executable(selftest_original tests/selftest/original.cpp ${SELFTEST_GL_SOURCES})
set_target_properties(selftest_original PROPERTIES
    OUTPUT_NAME SELFTEST
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/selftest-original"
)
target_compile_options(selftest_original PRIVATE ${SELFTEST_FLAGS})
# /FIXED drops the relocations, as in most old exes. check.py reads the map for
# the function sizes, as data/functions.csv gives them for the game.
target_link_options(selftest_original PRIVATE ${SELFTEST_LINK_FLAGS} /FIXED /MAP)

add_executable(selftest tests/selftest/decomp.cpp ${SELFTEST_GL_SOURCES})
set_target_properties(selftest PROPERTIES OUTPUT_NAME SELFTEST)
target_compile_options(selftest PRIVATE ${SELFTEST_FLAGS})
target_link_options(selftest PRIVATE ${SELFTEST_LINK_FLAGS} /DEBUG)
