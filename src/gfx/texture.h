#ifndef TEXTURE_H
#define TEXTURE_H

#include "gfx.h"

struct Texture {
  Texture(int p_width, int p_height);
  Texture(const char* p_file);
  ~Texture();
  void use(int p_texunit = 0);

  GLuint handle;
};

#endif /* TEXTURE_H */
