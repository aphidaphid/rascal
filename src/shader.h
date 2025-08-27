#ifndef SHADER_H
#define SHADER_H

#include <cstring>
#include <cstdio>
#include <iostream>
#include <glad/glad.h>

struct Shader {
  Shader(const char* p_vertfile, const char* p_fragfile);
  void use();
  void set_uniform1f(const char* p_uniform, float p_set);

  GLuint handle, vhandle, fhandle;
};

#endif /* SHADER_H */
