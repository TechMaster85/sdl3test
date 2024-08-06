cmake_minimum_required(VERSION 3.5)

project(sdl3test)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_LIBRARY_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# By default, download SDL3. Change this when a stable release is out and system
# packages are in almost all repositories.
include(FetchContent)
set(SDL_SHARED
    TRUE
    CACHE BOOL "Build a SDL shared library (if available)")

set(SDL_STATIC
    TRUE
    CACHE BOOL "Build a SDL static library (if available)")

FetchContent_Declare(
  SDL
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main # Replace this with a particular git tag or git hash
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)
message(STATUS "Using SDL3 via FetchContent")

FetchContent_Declare(
  SDL_IMAGE
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG main
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE)
message(STATUS "Using SDL3_Image via FetchContent")

FetchContent_MakeAvailable(SDL SDL_IMAGE)
set_property(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/_deps/sdl-src"
             PROPERTY EXCLUDE_FROM_ALL TRUE)
set_property(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/_deps/sdl_image-src"
             PROPERTY EXCLUDE_FROM_ALL TRUE)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)

# Create your game executable target as usual
add_executable(sdl3test)

target_sources(sdl3test PRIVATE src/main.c)

# Link to the actual SDL3 library.
target_link_libraries(
  sdl3test
  PRIVATE SDL3::SDL3
  PRIVATE SDL3_image::SDL3_image)
