#include "state.h"

State::State()
: debug{false}, shaders{} {
  shaders.push_back(new Shader("res/shaders/default.vert", "res/shaders/default.frag"));
  shaders.push_back(new Shader("res/shaders/default.vert", "res/shaders/error.frag"));
  shaders.push_back(new Shader("res/shaders/default.vert", "res/shaders/vertex_colour.frag"));
  shaders.push_back(new Shader("res/shaders/default.vert", "res/shaders/jfa.frag"));

  camera = {-static_cast<float>(client.width)/2, -static_cast<float>(client.height)/2};
}

void State::update() {
  client.update();

  /* calc camera movement */
#ifndef STATIC_CAMERA
  static glm::vec2 curlastpos{};
  if (client.mouse.is_pressed) {
    glm::vec2 position{client.mouse.x, client.mouse.y};
    position -= curlastpos;
    camera.x -= position.x;
    camera.y += position.y;
  }
  curlastpos = { client.mouse.x, client.mouse.y };
#endif
}

void State::ui_init() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ui = &ImGui::GetIO();
  ImGui_ImplGlfw_InitForOpenGL(client.handle, true);
  ImGui_ImplOpenGL3_Init("#version 150");
}

void State::ui_begin() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void State::ui_end() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

#define DTEXT(x) ImGui::Text((#x": " + std::to_string(x)).c_str())

void State::ui_debug() {
  if (!debug) return;

  ImGui::Begin("debug");
  if (ImGui::BeginTabBar("tab_bar", ImGuiTabBarFlags_None)) {

    if (ImGui::BeginTabItem("state")) {
      static bool wireframe{false};
      if (ImGui::Checkbox("wireframe", &wireframe))
        glPolygonMode(GL_FRONT_AND_BACK, (wireframe) ? GL_LINE : GL_FILL);

      DTEXT(client.delta_time);
      DTEXT(client.get_time());
      DTEXT(camera.x);
      DTEXT(camera.y);
      DTEXT(camera.scale);

      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("input")) {
      DTEXT(client.mouse.x);
      DTEXT(client.mouse.y);
      ImGui::Checkbox("m1", &g_state.client.mouse.m1); ImGui::SameLine();
      ImGui::Checkbox("m2", &g_state.client.mouse.m2); ImGui::SameLine();
      ImGui::Checkbox("m3", &g_state.client.mouse.m3);
      ImGui::Checkbox("is_pressed", &g_state.client.mouse.is_pressed);

      ImGui::Separator();

      for (int i = 0; i < GLFW_KEY_LAST; i++) {
        KeyState ks = g_state.client.get_key(i);
        if (ks) {
          char ch = static_cast<char>(i);
          DTEXT(ch);
          ImGui::SameLine();
          ImGui::Text(&ch);
          ImGui::SameLine();
          ImGui::Text(ks == KeyState::Press ? "Press" : "Repeat");
        }
      }
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();

  }
  ImGui::End();
}
