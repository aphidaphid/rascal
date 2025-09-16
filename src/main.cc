#include "state.h"
#include "gfx.h"
#include "shader.h"
#include "texture.h"
#include "mesh.h"
#include "framebuffer.h"

/*
 * TODO: gltf import
 * TODO: framebuffers
 */

State g_state{};

int main() {
  g_state.ui_init();

  /* create framebuffers BEFORE regular textures as framebuffer colour buffers etc. will be bound to context */
  Framebuffer emission_fb{};
  Framebuffer::use_default();

  Texture tiles{"res/textures/tiles_512px.jpg"};
  Texture concrete{"res/textures/concrete_512px.jpg"};

  Mesh rect{glm::vec2(0), glm::vec2(300)};
  rect.set_colour(1.0, 0.0, 1.0);
  Mesh rect2{glm::vec2(0), glm::vec2(300)};
  rect2.set_colour(1.0, 1.0, 0.0);

  while (g_state.client.running) {
    g_state.ui_begin();
    g_state.ui_debug();
    g_state.ui_end();

    rect2.scale.y += std::sin(g_state.client.get_time());
    rect2.scale.x += std::cos(g_state.client.get_time());
    rect2.position.y = std::sin(g_state.client.get_time());
    rect2.position.x = std::cos(g_state.client.get_time());

    if (g_state.client.get_key(GLFW_KEY_C)) {
      g_state.camera = {-static_cast<float>(g_state.client.width)/2, -static_cast<float>(g_state.client.height)/2};
    }

    if (g_state.client.get_key_no_repeat(GLFW_KEY_GRAVE_ACCENT)) {
      g_state.debug = !g_state.debug;
    }

    g_state.update();

    emission_fb.use();

    tiles.use();
    rect.render(g_state.shaders[VertexColour]);

    concrete.use();
    rect2.render(g_state.shaders[VertexColour]);

    Framebuffer::use_default();

    emission_fb.render(g_state.shaders[JumpFlood]);
  }
}
