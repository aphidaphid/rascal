#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "gfx.h"
#include "texture.h"
#include "mesh.h"

struct Framebuffer {
  Framebuffer();
  ~Framebuffer();

  void use();
  static void use_default();
  void render(Shader* shader = nullptr);

  GLuint handle;
  Texture colour_buffer;
  Mesh quad;
};

#endif /* FRAMEBUFFER_H */
