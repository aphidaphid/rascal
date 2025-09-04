#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* p_file, int p_texunit) {
  int width, height, channels;
  unsigned char* img_handle = stbi_load(p_file, &width, &height, &channels, 0);

  assert((img_handle != NULL) && "image loading failed");

  glGenTextures(1, &handle);
  glActiveTexture(GL_TEXTURE0+p_texunit);
  glBindTexture(GL_TEXTURE_2D, handle);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_handle);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(img_handle);
}

void Texture::use(int p_texunit) {
  glActiveTexture(GL_TEXTURE0+p_texunit);
  glBindTexture(GL_TEXTURE_2D, handle);
}
