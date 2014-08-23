cmake_minimum_required(VERSION 2.6)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_definitions("-Wall -O2 -g -pedantic -std=gnu11")

# Version
# =======

set(MAJOR 0)
set(MINOR 1)
set(PATCH 0)
set(VERSION ${MAJOR}.${MINOR}.${PATCH})

# Game naming
# ==============
set(GAME ld30_multiverse)

# Binary
# ======

file(GLOB SOURCE src/*.c)
add_executable(${GAME} ${SOURCE})
target_link_libraries(${GAME} estk3 SDL GL GLEW m)

