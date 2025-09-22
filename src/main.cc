#include "state.h"
#include "gfx.h"
#include "shader.h"
#include "texture.h"
#include "mesh.h"
#include "framebuffer.h"

State g_state{};

int main() {
  g_state.ui_init();

  /* create framebuffers BEFORE regular textures as framebuffer colour buffers etc. will be bound to context */
  Framebuffer fb_emission{}, fb_occlusion{}, fb_scene{}, fb_jfa_a{}, fb_jfa_b{}, fb_jfa_prep{}, fb_distance_field;
  Framebuffer::use_default();

  Texture tiles{"res/textures/tiles_512px.jpg"}, concrete{"res/textures/concrete_512px.jpg"};

  Mesh rect{glm::vec2(0), glm::vec2(300)};
  rect.set_colour(1.0, 0.0, 1.0);
  Mesh rect2{glm::vec2(0), glm::vec2(300)};
  rect2.set_colour(1.0, 1.0, 0.0);
  Mesh rect3{glm::vec2(100, -100), glm::vec2(280)};
  rect3.set_colour(1.0, 1.0, 1.0);

  int jump_size{1024};
  while (g_state.client.running) {
    g_state.ui_begin();
    g_state.ui_debug();
    if (g_state.debug) {
      ImGui::Begin("game");
      ImGui::SliderInt("jump size", &jump_size, 0, 4096);
      ImGui::End();
    }
    g_state.ui_end();

    rect2.scale.y += std::sin(g_state.client.get_time());
    rect2.scale.x += std::cos(g_state.client.get_time());
    rect2.position.y = std::sin(g_state.client.get_time()) * 200;
    rect2.position.x = std::cos(g_state.client.get_time()) * 200;
    rect2.set_colour(std::sin(g_state.client.get_time()) + 1 / 2, 1.0, 0.0);

    if (g_state.client.get_key(GLFW_KEY_C)) {
      g_state.camera = {-static_cast<float>(g_state.client.width)/2, -static_cast<float>(g_state.client.height)/2};
    }

    if (g_state.client.get_key_no_repeat(GLFW_KEY_GRAVE_ACCENT)) {
      g_state.debug = !g_state.debug;
    }

    g_state.update();

    fb_emission.use();

    rect.render(g_state.shaders[VertexColour]);
    rect2.render(g_state.shaders[VertexColour]);

    fb_occlusion.use();

    rect3.render(g_state.shaders[VertexColour]);

    fb_scene.use();

    fb_emission.colour_buffer.use(0);
    fb_occlusion.colour_buffer.use(1);
    g_state.render_screen_rect(g_state.shaders[Scene]);

    fb_jfa_prep.use();

    fb_scene.colour_buffer.use(0);
    g_state.render_screen_rect(g_state.shaders[JumpFloodPrep]);

    fb_jfa_b.use();

    fb_jfa_prep.colour_buffer.use(0);
    g_state.render_screen_rect();

    Framebuffer *jfa1, *jfa2{};
    bool swapped = true;
    for (int j = jump_size*2; j >= 1; j /= 2) {
      if (swapped) {
        jfa1 = &fb_jfa_a;
        jfa2 = &fb_jfa_b;
      } else {
        jfa1 = &fb_jfa_b;
        jfa2 = &fb_jfa_a;
      }
      swapped = !swapped;

      jfa1->use();
      jfa2->colour_buffer.use(0);
      g_state.shaders[JumpFlood]->use();
      g_state.shaders[JumpFlood]->set_int("u_jump_size", j);
      g_state.render_screen_rect(g_state.shaders[JumpFlood]);
    }

    fb_distance_field.use();

    fb_jfa_a.colour_buffer.use(0);
    g_state.render_screen_rect(g_state.shaders[DistanceField]);

    Framebuffer::use_default();

    fb_distance_field.colour_buffer.use(0);
    fb_scene.colour_buffer.use(1);
    g_state.shaders[Lighting]->use();
    g_state.shaders[Lighting]->set_vec2("u_resolution", g_state.client.width, g_state.client.height);
    g_state.render_screen_rect(g_state.shaders[Lighting]);
  }
}
