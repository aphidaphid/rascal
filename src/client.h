#ifndef CLIENT_H
#define CLIENT_H

#define DPRINT(x) std::cout << #x": " << x << "\n"

#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

enum MouseButton {
  MOUSE_1 = 0,
  MOUSE_2,
  MOUSE_3
};

struct Client {
  Client(const char* p_title);
  ~Client();

  void init_ui();
  void update();
  void ui_begin();
  void ui_end();

  bool get_key(int p_key);

  GLFWwindow* handle;
  bool running;
  int width, height;
  double delta_time;
  double last_frame_time;

  std::string text; // for debugging

  ImGuiIO* io;

  // NOTE: `Client` should really just be a container for a graphics context, input & a window, so `camera` doesn't really belong here
  // i'll probably end up moving it to somewhere else
  struct {
    float x, y;
    float scale = 1.0f;
  } camera;

  struct {
    double x, y;
    MouseButton button;
    bool is_pressed;
  } cursor;
};

extern Client g_client;

#endif /* CLIENT_H */
