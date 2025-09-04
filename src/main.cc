#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "client.h"
#include "texture.h"

static glm::vec2 g_camera{};
static Client g_client{"rascal"};

struct Mesh {
  Mesh(glm::vec2 p_position, glm::vec2 p_scale, float p_rotation = 0)
  : position{p_position}, scale{p_scale}, rotation{p_rotation} {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float vertices[] = {
    // pos       // colour         // texcoord
      -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
       0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
       0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
      -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };

    GLuint elements[] = {
      0, 1, 2,
      2, 3, 0
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
  }

  void render() {
    glBindVertexArray(vao);
    shader->use();
    float x = std::sin(glfwGetTime());
    float y = std::cos(glfwGetTime());

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    glm::mat4 view = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0f));
    glm::mat4 proj = glm::ortho(g_camera.x, g_camera.x+static_cast<float>(g_client.width), g_camera.y, g_camera.y+static_cast<float>(g_client.height), 0.0f, 1000.0f);

    shader->set_mat4("u_model", model);
    shader->set_mat4("u_view", view);
    shader->set_mat4("u_proj", proj);

    shader->set_float("u_time", glfwGetTime());

    shader->set_int("u_tex0", 0);
    shader->set_int("u_tex1", 1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

  GLuint vao, vbo, ebo;
  glm::vec2 position, scale;
  float rotation;
  Shader* shader;
};

int main() {
  g_client.init_ui();

  Mesh rect{glm::vec2(0), glm::vec2(300)};

  Texture tiles{"res/textures/tiles_512px.jpg", 0};
  Texture concrete{"res/textures/concrete_512px.jpg", 1};

  Shader default_shader{"res/shaders/default.vert", "res/shaders/default.frag"};
  rect.shader = &default_shader;

  g_camera = {-static_cast<float>(g_client.width)/2, -static_cast<float>(g_client.height)/2};
  while (g_client.running) {
    // g_client.begin_ui();
    // ImGui::Begin("xy");
    // ImGui::SliderFloat("x", &x, 0.0f, 16.0f);
    // ImGui::SliderFloat("y", &y, 0.0f, 16.0f);
    // ImGui::End();
    // g_client.render_ui();
    g_client.update();
    rect.render();
  }
}
