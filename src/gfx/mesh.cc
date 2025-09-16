#include "mesh.h"
#include "state.h"

extern State g_state;

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

Mesh::~Mesh() {
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
  glDeleteVertexArrays(1, &vao);
}

void Mesh::set_colour(float r, float g, float b) {
  glBindVertexArray(vao);

  float vertices[] = {
  // pos       // colour         // texcoord
    -0.5f,  0.5f, r, g, b, 0.0f, 0.0f,
     0.5f,  0.5f, r, g, b, 1.0f, 0.0f,
     0.5f, -0.5f, r, g, b, 1.0f, 1.0f,
    -0.5f, -0.5f, r, g, b, 0.0f, 1.0f
  };

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Mesh::set_colour(glm::vec3 col) {
  set_colour(col.x, col.y, col.z);
}

// TODO: clean this up
void Mesh::render(Shader* shader) {
  if (!shader)
    shader = g_state.shaders[Default];

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  shader->use();

  GLint posAttrib = glGetAttribLocation(shader->handle, "a_position");
  GLint colAttrib = glGetAttribLocation(shader->handle, "a_colour");
  GLint texCoordAttrib = glGetAttribLocation(shader->handle, "a_tex_coord");

  glVertexAttribPointer(posAttrib,      2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);
  glVertexAttribPointer(colAttrib,      3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(2*sizeof(float)));
  glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(5*sizeof(float)));

  glEnableVertexAttribArray(posAttrib);
  glEnableVertexAttribArray(colAttrib);
  glEnableVertexAttribArray(texCoordAttrib);

  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
  glm::mat4 view = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0f));
  glm::mat4 proj = glm::ortho(g_state.camera.x, g_state.camera.x+static_cast<float>(g_state.client.width), g_state.camera.y, g_state.camera.y+static_cast<float>(g_state.client.height), 0.0f, 1000.0f);
  proj = glm::scale(proj, glm::vec3(glm::vec2(g_state.camera.scale), 1.0f));

  shader->set_mat4("u_model", model);
  shader->set_mat4("u_view", view);
  shader->set_mat4("u_proj", proj);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
