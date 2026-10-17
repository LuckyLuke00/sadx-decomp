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
