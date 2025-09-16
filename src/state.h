#ifndef STATE_H
#define STATE_H

#include <vector>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "client.h"
#include "shader.h"
#include "mesh.h"

enum ShaderIndex {
  Default = 0,
  Error,
  VertexColour,
  JumpFlood
};

struct State {
  State();
  void update();
  void render_screen_rect(Shader* shader = nullptr);

  void ui_init();
  void ui_begin();
  void ui_end();
  void ui_debug();

  void reload_shaders();

  std::vector<Shader*> shaders;

  Client client{"rascal"};
  ImGuiIO* ui;
  bool debug;

  Mesh screen_rect;
  struct {
    float x, y;
    float scale = 1.0f;
  } camera;
};

extern State g_state;

#endif /* STATE_H */
