#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>

struct Texture {
  Texture(const char* p_file, int p_texunit = 0);
  void use(int p_texunit = 0);

  GLuint handle;
  unsigned char* img_handle;
  int width, height, channels;
};

#endif /* TEXTURE_H */
