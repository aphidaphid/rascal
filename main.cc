#include <cstdio>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static bool create_shader(GLuint& handle, GLenum p_type, const char* p_src) {
  std::string src{};
  FILE* file = std::fopen(p_src, "r");

  int c;
  while ((c = std::fgetc(file)) != EOF)
    src += c;

  std::fclose(file);

  const char* src_cstr = src.c_str();

  handle = glCreateShader(p_type);
  glShaderSource(handle, 1, &src_cstr, NULL);
  glCompileShader(handle);

  GLint status;
  glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
  if (!status) {
    std::cerr << "shader creation failed\n";
    return false;
  }

  return true;
}

static bool create_shader_programme(GLuint& handle, GLuint& vhandle, GLuint& fhandle) {
  handle = glCreateProgram();
  glAttachShader(handle, vhandle);
  glAttachShader(handle, fhandle);
  glBindFragDataLocation(handle, 0, "fragColor");
  glLinkProgram(handle);
  return true;
}

static inline void use_shader_programme(GLuint& handle) {
  glUseProgram(handle);
}

static void error_callback(int err, const char* description)
{
  std::cerr << err << " error: " << description << "\n";
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
  if (!glfwInit()) {
    std::cerr << "glfw failed to initialise\n";
  }

  glfwSetErrorCallback(error_callback);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  GLFWwindow* window = glfwCreateWindow(800, 600, "title", NULL, NULL);
  if (!window) {
    std::cerr << "GLFWwindow failed to initialise\n";
  }

  glfwSetKeyCallback(window, key_callback);

  glfwMakeContextCurrent(window);
  gladLoadGL();

  float vertices[] = {
     0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f
  };

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint vertexShader, fragmentShader, shaderProgramme;
  create_shader(vertexShader, GL_VERTEX_SHADER, "default.vert");
  create_shader(fragmentShader, GL_FRAGMENT_SHADER, "default.frag");

  create_shader_programme(shaderProgramme, vertexShader, fragmentShader);
  use_shader_programme(shaderProgramme);

  GLint posAttrib = glGetAttribLocation(shaderProgramme, "a_position");
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
  glEnableVertexAttribArray(posAttrib);

  GLint colAttrib = glGetAttribLocation(shaderProgramme, "a_colour");
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
  glEnableVertexAttribArray(colAttrib);

  GLint time = glGetUniformLocation(shaderProgramme, "u_time");

  while (!glfwWindowShouldClose(window)) {
    glUniform1f(time, glfwGetTime());
    glClear(GL_COLOR_BUFFER_BIT);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
