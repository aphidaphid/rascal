#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(int p_width, int p_height, unsigned char* p_img_handle) {
  glGenTextures(1, &handle);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, handle);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, p_width, p_height, 0, GL_RGB, GL_UNSIGNED_BYTE, p_img_handle);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::Texture(const char* p_file) {
  int width, height, channels;
  unsigned char* img_handle = stbi_load(p_file, &width, &height, &channels, 0);

  assert((img_handle != NULL) && "image loading failed");

  Texture(width, height, img_handle);

  stbi_image_free(img_handle);
}

Texture::~Texture() {
  glDeleteTextures(1, &handle);
}

void Texture::use(int p_texunit) {
  glActiveTexture(GL_TEXTURE0+p_texunit);
  glBindTexture(GL_TEXTURE_2D, handle);
}
