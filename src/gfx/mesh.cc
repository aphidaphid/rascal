#include "mesh.h"

extern Client g_client;

Mesh::Mesh(glm::vec2 p_position, glm::vec2 p_scale, float p_rotation, Shader* p_shader)
: position{p_position}, scale{p_scale}, rotation{p_rotation} {
  shader = p_shader;

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

Mesh::~Mesh() {
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
  glDeleteVertexArrays(1, &vao);
}

void Mesh::render() {
  glBindVertexArray(vao);

  shader->use();
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
  glm::mat4 view = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0f));
  glm::mat4 proj = glm::ortho(g_client.camera.x, g_client.camera.x+static_cast<float>(g_client.width), g_client.camera.y, g_client.camera.y+static_cast<float>(g_client.height), 0.0f, 1000.0f);
  proj = glm::scale(proj, glm::vec3(glm::vec2(g_client.camera.scale), 1.0f));

  shader->set_mat4("u_model", model);
  shader->set_mat4("u_view", view);
  shader->set_mat4("u_proj", proj);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
