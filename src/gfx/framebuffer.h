#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "gfx.h"
#include "texture.h"

struct Framebuffer {
  Framebuffer();
  ~Framebuffer();

  void use();
  static void use_default();

  GLuint handle;
  Texture colour_buffer;
};

#endif /* FRAMEBUFFER_H */
