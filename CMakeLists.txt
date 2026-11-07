cmake_minimum_required(VERSION 3.20)
project(algo CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Source to build; watch.sh passes -DSRC=<file>.
set(SRC main.cpp CACHE FILEPATH "Source file to build")
add_executable(main ${SRC})

target_compile_options(main PRIVATE
  -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion
  -g -O1 -fno-omit-frame-pointer
  -fsanitize=address,undefined
  -fno-sanitize-recover=all
)
target_link_options(main PRIVATE -fsanitize=address,undefined)

target_compile_definitions(main PRIVATE _GLIBCXX_DEBUG _GLIBCXX_DEBUG_PEDANTIC)
