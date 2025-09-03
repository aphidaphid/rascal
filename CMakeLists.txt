cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS    "-Wfatal-errors")

project(rascal)

add_subdirectory(lib)

add_executable(${PROJECT_NAME} src/main.cc src/client.cc src/shader.cc src/texture.cc)
target_include_directories(${PROJECT_NAME} PUBLIC "lib/glad/include" "lib/imgui" "lib/stb")
target_link_libraries(${PROJECT_NAME} glfw glad imgui -lglfw -lglm)
