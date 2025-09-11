#ifndef STATE_H
#define STATE_H

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "client.h"

struct State {
  State();
  void update();

  void ui_init();
  void ui_begin();
  void ui_end();
  void ui_debug();

  Client client{"rascal"};
  ImGuiIO* ui;
  bool debug;

  struct {
    float x, y;
    float scale = 1.0f;
  } camera;
};

extern State g_state;

#endif /* STATE_H */
