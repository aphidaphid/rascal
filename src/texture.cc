#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* p_file) {
  img_handle = stbi_load(p_file, &width, &height, &channels, 0);

  if (img_handle == NULL) {
    std::cerr << "image loading failed\n";
  }

  glGenTextures(1, &handle);
  glBindTexture(GL_TEXTURE_2D, handle);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_handle);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {
  stbi_image_free(img_handle);
}

void Texture::use() {
  glBindTexture(GL_TEXTURE_2D, handle);
}
