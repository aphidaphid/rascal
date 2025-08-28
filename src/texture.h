#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>

struct Texture {
  Texture(const char* p_file);
  void use();

  GLuint handle;
  unsigned char* img_handle;
  int width, height, channels;
};

#endif /* TEXTURE_H */
