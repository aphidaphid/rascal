#include "shader.h"

static GLuint create_shader(const char* p_src, GLenum p_type) {
  std::string src_s;

  std::FILE* f = std::fopen(p_src, "r");

  int c;
  while ((c = std::fgetc(f)) != EOF)
    src_s += c;

  std::fclose(f);

  const char* src = src_s.c_str();

  GLuint handle = glCreateShader(p_type);
  glShaderSource(handle, 1, &src, NULL);
  glCompileShader(handle);

  GLint status;
  glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
  if (!status) {
    char buffer[512];
    glGetShaderInfoLog(handle, 512, NULL, buffer);

    std::cerr << "shader creation failed:\n";
    std::cerr << buffer;

    std::abort();
  }
  return handle;
}

Shader::Shader(const char* p_vertfile, const char* p_fragfile) {
  vhandle = create_shader(p_vertfile, GL_VERTEX_SHADER);
  fhandle = create_shader(p_fragfile, GL_FRAGMENT_SHADER);

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

    std::abort();
  }

  GLint posAttrib = glGetAttribLocation(handle, "a_position");
  GLint colAttrib = glGetAttribLocation(handle, "a_colour");
  GLint texCoordAttrib = glGetAttribLocation(handle, "a_tex_coord");

  glVertexAttribPointer(posAttrib,      2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);
  glVertexAttribPointer(colAttrib,      3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(2*sizeof(float)));
  glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(5*sizeof(float)));

  glEnableVertexAttribArray(posAttrib);
  glEnableVertexAttribArray(colAttrib);
  glEnableVertexAttribArray(texCoordAttrib);
}

void Shader::use() {
  glUseProgram(handle);
}

void Shader::set_float(const char* p_uniform, float p_set) {
  glUniform1f(glGetUniformLocation(handle, p_uniform), p_set);
}

void Shader::set_int(const char* p_uniform, int p_set) {
  glUniform1i(glGetUniformLocation(handle, p_uniform), p_set);
}

void Shader::set_mat4(const char* p_uniform, glm::mat4& p_set) {
  glUniformMatrix4fv(glGetUniformLocation(handle, p_uniform), 1, GL_FALSE, glm::value_ptr(p_set));
}
