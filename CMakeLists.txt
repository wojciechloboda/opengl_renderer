
cmake_minimum_required (VERSION 2.6)
project (opengl_renderer)

add_executable(opengl_renderer src/opengl_renderer.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(extern/glfw)
add_subdirectory(extern/glad)

target_link_libraries(opengl_renderer glfw opengl32 glad)
target_include_directories(opengl_renderer PUBLIC extern/glfw/include extern/glad/include)

set_target_properties(opengl_renderer PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)



