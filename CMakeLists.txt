
cmake_minimum_required (VERSION 2.6)
project (opengl_renderer)

set(sources src/opengl_renderer.cpp
            src/framebuffer.cpp
            src/camera.cpp
            src/glslprogram.cpp)

add_executable(opengl_renderer ${sources})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(extern/glfw)
add_subdirectory(extern/glad)
add_subdirectory(extern/imgui)

target_link_libraries(opengl_renderer glfw opengl32 glad imgui)
target_include_directories(opengl_renderer PUBLIC extern/glfw/include
                                                  extern/glad/include
                                                  extern/vmath/include
                                                  extern/stb
                                                  extern/obj
                                                  extern/imgui
                                                  extern/imgui/backends
                                                  extern/glm)

set_target_properties(opengl_renderer PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)



