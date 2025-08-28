#include "shader.h"

static std::string read_file(const char* p_file) {
  std::string result{};
  std::FILE* f = std::fopen(p_file, "r");

  int c;
  while ((c = std::fgetc(f)) != EOF)
    result += c;

  std::fclose(f);

  return result;
}

Shader::Shader(const char* p_vertfile, const char* p_fragfile) {
  std::string vsrc_s = read_file(p_vertfile);
  std::string fsrc_s = read_file(p_fragfile);
  const char* vsrc = vsrc_s.c_str();
  const char* fsrc = fsrc_s.c_str();

  vhandle = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vhandle, 1, &vsrc, NULL);
  glCompileShader(vhandle);

  fhandle = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fhandle, 1, &fsrc, NULL);
  glCompileShader(fhandle);

  handle = glCreateProgram();
  glAttachShader(handle, vhandle);
  glAttachShader(handle, fhandle);
  glBindFragDataLocation(handle, 0, "fragColor");
  glLinkProgram(handle);

  GLint status;
  glGetProgramiv(handle, GL_LINK_STATUS, &status);
  if (!status) {
    char buffer[512];
    glGetProgramInfoLog(handle, 512, NULL, buffer);

    std::cerr << "shader programme creation failed:\n";
    std::cerr << buffer;
  }
}

void Shader::use() {
  glUseProgram(handle);
}

void Shader::set_float(const char* p_uniform, float p_set) {
  glUniform1f(glGetUniformLocation(handle, p_uniform), p_set);
}
