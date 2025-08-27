#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Client {
  GLFWwindow* handle;

  Client(const char* p_title);
  ~Client();
  void render();
};

#endif /* CLIENT_H */
