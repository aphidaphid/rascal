#include "shader.h"
#include "client.h"
#include "texture.h"

static Client client{"rascal"};

int main() {
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  float vertices[] = {
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
  };

  GLuint elements[] = {
    0, 1, 2,
    2, 3, 0
  };

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

  Shader shader{"res/shaders/default.vert", "res/shaders/default.frag"};
  shader.use();

  Texture tiles{"res/textures/tiles_512px.jpg"};
  Texture concrete{"res/textures/concrete_512px.jpg"};
  tiles.use();

  bool textoggle{};
  while (client.running) {
    shader.set_float("u_time", glfwGetTime());
    client.update();

    if (client.get_key(GLFW_KEY_A)) {
      tiles.use();
    } else {
      concrete.use();
    }

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}
