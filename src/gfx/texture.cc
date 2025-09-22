#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(int p_width, int p_height, bool alpha) {
  glGenTextures(1, &handle);
  glBindTexture(GL_TEXTURE_2D, handle);

  GLenum format = alpha ? GL_RGBA : GL_RGB;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, p_width, p_height, 0, format, GL_UNSIGNED_BYTE, nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(const char* p_file) {
  int width, height, channels;
  unsigned char* img_handle = stbi_load(p_file, &width, &height, &channels, 0);

  assert((img_handle != nullptr) && "image loading failed");

  glGenTextures(1, &handle);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, handle);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_handle);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(img_handle);
}

Texture::~Texture() {
  glDeleteTextures(1, &handle);
}

void Texture::use(int p_texunit) {
  glActiveTexture(GL_TEXTURE0+p_texunit);
  glBindTexture(GL_TEXTURE_2D, handle);
}
