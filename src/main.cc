#include "client.h"
#include "gfx.h"
#include "shader.h"
#include "texture.h"
#include "mesh.h"

/*
 * TODO: gltf import
 * TODO: framebuffers
 * TODO: keyboard, mouse, resize callbacks
 */

Client g_client{"rascal"};

int main() {
  g_client.init_ui();

  Texture tiles{"res/textures/tiles_512px.jpg", 0};
  Texture concrete{"res/textures/concrete_512px.jpg", 1};
  Shader default_shader{"res/shaders/default.vert", "res/shaders/default.frag"};
  Mesh rect{glm::vec2(0), glm::vec2(300), 0, &default_shader};
  Mesh rect2{glm::vec2(0), glm::vec2(300), 0, &default_shader};

  g_client.camera = {-static_cast<float>(g_client.width)/2, -static_cast<float>(g_client.height)/2};
  float x{}, y{};
  glm::vec2 curlastpos{g_client.cursor.x, g_client.cursor.y};
  while (g_client.running) {
    g_client.ui_begin();
    ImGui::Begin("info");
    ImGui::Text(std::to_string(g_client.delta_time).c_str());
    ImGui::End();
    g_client.ui_end();

    rect2.scale.y += std::sin(glfwGetTime());
    rect2.scale.x += std::cos(glfwGetTime());
    rect2.position.y = std::sin(glfwGetTime());
    rect2.position.x = std::cos(glfwGetTime());

    if (g_client.cursor.is_pressed) {
      glm::vec2 position{g_client.cursor.x, g_client.cursor.y};
      position -= curlastpos;
      g_client.camera.x -= position.x;
      g_client.camera.y += position.y;
    }
    curlastpos = { g_client.cursor.x, g_client.cursor.y };

    if (g_client.get_key(GLFW_KEY_C)) {
      g_client.camera = {-static_cast<float>(g_client.width)/2, -static_cast<float>(g_client.height)/2};
    }

    g_client.update();

    rect.render();
    rect2.render();
  }
}
