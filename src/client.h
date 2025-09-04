#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

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
};

extern Client g_client;

#endif /* CLIENT_H */
