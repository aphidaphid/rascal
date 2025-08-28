#include "shader.h"
#include "client.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

  Shader shader{"res/default.vert", "res/default.frag"};
  shader.use();

  GLint posAttrib = glGetAttribLocation(shader.handle, "a_position");
  GLint colAttrib = glGetAttribLocation(shader.handle, "a_colour");
  GLint texCoordAttrib = glGetAttribLocation(shader.handle, "a_tex_coord");

  glVertexAttribPointer(posAttrib,      2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);
  glVertexAttribPointer(colAttrib,      3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(2*sizeof(float)));
  glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(5*sizeof(float)));

  glEnableVertexAttribArray(posAttrib);
  glEnableVertexAttribArray(colAttrib);
  glEnableVertexAttribArray(texCoordAttrib);

  GLuint tex;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);

  int width{}, height{}, channels{};
  unsigned char *img = stbi_load("res/cat.png", &width, &height, &channels, 0);
  if (img == NULL) {
    std::cerr << "image loading failed\n";
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(img);

  while (client.running) {
    client.update();

    shader.set_float("u_time", glfwGetTime());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}
