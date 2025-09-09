#include "state.h"

State::State() {
  camera = {-static_cast<float>(client.width)/2, -static_cast<float>(client.height)/2};
}

void State::update() {
  client.update();

  static glm::vec2 curlastpos{};
  if (client.mouse.is_pressed) {
    glm::vec2 position{client.mouse.x, client.mouse.y};
    position -= curlastpos;
    camera.x -= position.x;
    camera.y += position.y;
  }
  curlastpos = { client.mouse.x, client.mouse.y };
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

void State::ui_debug() {
  ImGui::Begin("debug");
  if (ImGui::BeginTabBar("tab_bar", ImGuiTabBarFlags_None)) {

    if (ImGui::BeginTabItem("info")) {
      ImGui::Text(("delta_time: " + std::to_string(g_state.client.delta_time)).c_str());
      ImGui::Text(("time: " + std::to_string(g_state.client.get_time())).c_str());
      static bool wireframe{false};
      if (ImGui::Checkbox("wireframe", &wireframe)) {
        if (wireframe)
          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      }
      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("input")) {
      if (ImGui::BeginTabBar("input_tab_bar", ImGuiTabBarFlags_None)) {
        if (ImGui::BeginTabItem("mouse")) {
          ImGui::Text(std::to_string(g_state.client.mouse.x).c_str());
          ImGui::SameLine();
          ImGui::Text(std::to_string(g_state.client.mouse.y).c_str());
          ImGui::Checkbox("m1", &g_state.client.mouse.m1);
          ImGui::Checkbox("m2", &g_state.client.mouse.m2);
          ImGui::Checkbox("m3", &g_state.client.mouse.m3);
          ImGui::Checkbox("is_pressed", &g_state.client.mouse.is_pressed);
          ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
      }
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();

  }
  ImGui::End();
}
