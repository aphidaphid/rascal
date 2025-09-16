#ifndef MESH_H
#define MESH_H

#include "gfx.h"
#include "shader.h"

struct Mesh {
  Mesh(glm::vec2 p_position = {}, glm::vec2 p_scale = {}, float p_rotation = 0, Shader* p_shader = nullptr);
  ~Mesh();

  void render();

  GLuint vao, vbo, ebo;
  glm::vec2 position, scale;
  float rotation;
  Shader* shader;
};

#endif /* MESH_H */
