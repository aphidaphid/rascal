add_library(glad glad/src/glad.c)
target_include_directories(glad PUBLIC "glad/include")

file(GLOB imgui_src imgui/*.h imgui/*.cpp imgui/backends/imgui_impl_opengl3.* imgui/backends/imgui_impl_glfw.*)
add_library(imgui ${imgui_src})
target_include_directories(imgui PUBLIC "imgui/" -lglfw)
