#ifndef STATE_H
#define STATE_H

#include <vector>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "client.h"
#include "shader.h"

enum ShaderIndex {
  Default = 0,
  Error,
  VertexColour,
  JFA
};

struct State {
  State();
  void update();

  void ui_init();
  void ui_begin();
  void ui_end();
  void ui_debug();

  std::vector<Shader*> shaders;

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
