# Build settings only this game needs. CMakeLists.txt includes this file after
# it adds the `game` target.
#
# From the exe's PE header (`check.py probe` prints them): a GUI program
# (subsystem 2) with no ASLR (characteristics 0x103, DLL characteristics
# 0x8100). The game has no relocations either, but ours keep theirs for reccmp.
set_target_properties(game PROPERTIES WIN32_EXECUTABLE TRUE)
target_link_options(game PRIVATE /DYNAMICBASE:NO)

# The game compiled its .c files as C++: at /Od, C puts string literals in .data
# and C++ in .rdata, and the literals of task.c, enemy.c and eventdraw.c, all /Od,
# sit in .rdata (docs/STYLE.md).
set_source_files_properties(${GAME_SOURCES} PROPERTIES LANGUAGE CXX)

# The shared declarations that every source file includes as "decls.h".
target_include_directories(game PRIVATE "${CMAKE_SOURCE_DIR}/src/include")

# Steamworks SDK v1.26a, the one with the game's steam_api.dll. Its license
# allows local use only, so it is never committed: extract it to
# .toolchain/steamworks-126a. Without it, src/steam/ is left out of the build.
set(STEAMWORKS "${CMAKE_SOURCE_DIR}/.toolchain/steamworks-126a")
file(GLOB_RECURSE STEAM_SOURCES CONFIGURE_DEPENDS src/steam/*.c src/steam/*.cpp)
# Configure again when the SDK comes or goes. Its files keep the zip's old
# times, so the folder that holds it is the input that changes.
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/.toolchain" "${STEAMWORKS}/public/steam/steam_api.h")
if(EXISTS "${STEAMWORKS}/public/steam/steam_api.h")
    target_include_directories(game PRIVATE "${STEAMWORKS}/public")
    target_link_libraries(game PRIVATE "${STEAMWORKS}/redistributable_bin/steam_api.lib")
else()
    message(STATUS "No Steamworks SDK in ${STEAMWORKS}: src/steam/ is not built")
    set_source_files_properties(${STEAM_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)
endif()
