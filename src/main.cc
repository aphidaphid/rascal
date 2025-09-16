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
  glClearColor(0.165, 0.274, 0.165, 1.0);

  /* create framebuffers before regular textures as framebuffer colour buffers etc. will be bound to context */
  Framebuffer fb{};
  Framebuffer::use_default();

  Texture tiles{"res/textures/tiles_512px.jpg"};
  Texture concrete{"res/textures/concrete_512px.jpg"};
  Mesh rect{glm::vec2(0), glm::vec2(300), 0, g_state.shaders[Default]};
  Mesh rect2{glm::vec2(0), glm::vec2(300), 0, g_state.shaders[Error]};

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

    fb.use();

    tiles.use();
    rect.render();

    concrete.use();
    rect2.render();

    Framebuffer::use_default();

    glBindVertexArray(fb.quad.vao);

    fb.colour_buffer.use();
    g_state.shaders[JFA]->use();
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::scale(model, glm::vec3(g_state.client.width, g_state.client.height, 1.0f));
    view = glm::scale(view, glm::vec3(1.0f, -1.0f, 1.0f));
    glm::mat4 proj = glm::ortho(
        -static_cast<float>(g_state.client.width)/2, static_cast<float>(g_state.client.width)/2,
        -static_cast<float>(g_state.client.height)/2, static_cast<float>(g_state.client.height)/2,
        0.0f, 1000.0f);

    g_state.shaders[JFA]->set_mat4("u_model", model);
    g_state.shaders[JFA]->set_mat4("u_view", view);
    g_state.shaders[JFA]->set_mat4("u_proj", proj);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}
