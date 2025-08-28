#ifndef SHADER_H
#define SHADER_H

#include <cstring>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <glad/glad.h>

struct Shader {
  Shader(const char* p_vertfile, const char* p_fragfile);
  void use();
  void set_float(const char* p_uniform, float p_set);
  void set_int(const char* p_uniform, int p_set);

  GLuint handle, vhandle, fhandle;
};

#endif /* SHADER_H */
