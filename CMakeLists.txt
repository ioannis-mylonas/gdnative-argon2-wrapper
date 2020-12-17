cmake_minimum_required(VERSION 3.2)

project(gdnative-argon2-wrapper)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(HEADERS_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR}/godot_headers)
include_directories(${INCLUDE_DIR}/godot)
include_directories(${INCLUDE_DIR}/godot/core)
include_directories(${INCLUDE_DIR}/godot/gen)

include_directories(${INCLUDE_DIR}/argon2)
include_directories(${HEADERS_DIR})

link_directories(${LIB_DIR}/argon2)
link_directories(${LIB_DIR}/godot)

add_library(gdnative-argon2-wrapper SHARED
  src/gdlibrary.cpp
  src/wrapper/wrapper.cpp)

target_compile_options(gdnative-argon2-wrapper PUBLIC -g -O3 -std=c++14 -Wwrite-strings)
target_link_options(gdnative-argon2-wrapper PUBLIC --static -Wl,--no-undefined -static-libgcc -static-libstdc++)

target_link_libraries(gdnative-argon2-wrapper godot-cpp.windows.release.64 argon2)