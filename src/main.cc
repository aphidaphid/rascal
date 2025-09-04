#include "gfx.h"
#include "shader.h"
#include "client.h"
#include "texture.h"
#include "mesh.h"

glm::vec2 g_camera{};
Client g_client{"rascal"};

int main() {
  g_client.init_ui();

  Mesh rect{glm::vec2(0), glm::vec2(300)};

  Texture tiles{"res/textures/tiles_512px.jpg", 0};
  Texture concrete{"res/textures/concrete_512px.jpg", 1};

  Shader default_shader{"res/shaders/default.vert", "res/shaders/default.frag"};
  rect.shader = &default_shader;

  g_camera = {-static_cast<float>(g_client.width)/2, -static_cast<float>(g_client.height)/2};
  while (g_client.running) {
    g_client.ui_begin();
    // ImGui::Begin("xy");
    // ImGui::SliderFloat("x", &x, 0.0f, 16.0f);
    // ImGui::SliderFloat("y", &y, 0.0f, 16.0f);
    // ImGui::End();
    bool t = true;
    ImGui::ShowDemoWindow(&t);
    g_client.ui_end();

    g_client.update();
    rect.render();
  }
}
