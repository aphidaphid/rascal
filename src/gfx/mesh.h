#ifndef MESH_H
#define MESH_H

#include "gfx.h"
#include "shader.h"

struct Mesh {
  Mesh(glm::vec2 p_position = {}, glm::vec2 p_scale = {}, float p_rotation = 0);
  ~Mesh();

  void set_colour(float r, float g, float b);
  void set_colour(glm::vec3 col);
  void render(Shader* shader = nullptr);

  GLuint vao, vbo, ebo;
  glm::vec2 position, scale;
  float rotation;
};

#endif /* MESH_H */
