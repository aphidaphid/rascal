#include "mesh.h"

extern glm::vec2 g_camera;
extern Client g_client;

Mesh::Mesh(glm::vec2 p_position, glm::vec2 p_scale, float p_rotation)
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

void Mesh::render() {
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
