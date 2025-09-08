#include "state.h"

State::State() {
  camera = {-static_cast<float>(client.width)/2, -static_cast<float>(client.height)/2};
}

void State::update() {
  client.update();

  static glm::vec2 curlastpos{};
  if (client.cursor.is_pressed) {
    glm::vec2 position{client.cursor.x, client.cursor.y};
    position -= curlastpos;
    camera.x -= position.x;
    camera.y += position.y;
  }
  curlastpos = { client.cursor.x, client.cursor.y };
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

