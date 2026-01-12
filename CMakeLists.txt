cmake_minimum_required(VERSION 3.23)

project(gloom LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(prog)

target_sources(prog
  PRIVATE
    src/main.cpp
    src/glad.c
)

target_include_directories(prog
  PRIVATE
    include
    KHR
)

find_package(OpenGL REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(prog PRIVATE
    OpenGL::GL
    SDL2::SDL2
    glm::glm-header-only
)
