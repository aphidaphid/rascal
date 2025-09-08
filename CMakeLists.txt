cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS    "-Wfatal-errors")
set(CMAKE_BUILD_TYPE   Debug)

project(rascal)

add_subdirectory(lib)

add_executable(${PROJECT_NAME} src/main.cc src/client.cc src/gfx/shader.cc src/gfx/texture.cc src/gfx/mesh.cc src/state.cc)
target_include_directories(${PROJECT_NAME} PUBLIC "src" "src/gfx" "lib/glad/include" "lib/imgui" "lib/stb")
target_link_libraries(${PROJECT_NAME} glfw glad imgui -lglfw -lglm)
