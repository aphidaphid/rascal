#ifndef SHADER_H
#define SHADER_H

#include "gfx.h"
#include <cstring>
#include <cstdio>
#ifndef NDEBUG
#include <sys/inotify.h>
#endif

struct Shader {
  Shader(const char* p_vertfile, const char* p_fragfile);
  ~Shader();

  void use();

  void set_float(const char* p_uniform, float p_set);
  void set_int(const char* p_uniform, int p_set);
  void set_mat4(const char* p_uniform, glm::mat4& p_set);
  void set_vec2(const char* p_uniform, glm::vec2& p_set);
  void set_vec2(const char* p_uniform, float p_x, float p_y);

  GLuint handle, vhandle, fhandle;
};

#endif /* SHADER_H */
