#include "shader.h"

static inline GLuint create_shader(const char* p_src, GLenum p_type) {
  GLuint handle = glCreateShader(p_type);
  glShaderSource(handle, 1, &p_src, NULL);
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

  vhandle = create_shader(vsrc, GL_VERTEX_SHADER);
  fhandle = create_shader(fsrc, GL_FRAGMENT_SHADER);

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
