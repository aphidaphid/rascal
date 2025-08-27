#include "shader.h"
#include "client.h"

int main() {
  Client client{"rascal"};

  float vertices[] = {
     0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f
  };

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  Shader shader{"default.vert", "default.frag"};
  shader.use();

  GLint posAttrib = glGetAttribLocation(shader.handle, "a_position");
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
  glEnableVertexAttribArray(posAttrib);

  GLint colAttrib = glGetAttribLocation(shader.handle, "a_colour");
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
  glEnableVertexAttribArray(colAttrib);

  while (!glfwWindowShouldClose(client.handle)) {
    shader.set_uniform1f("u_time", glfwGetTime());
    glDrawArrays(GL_TRIANGLES, 0, 3);
    client.render();
  }
}
