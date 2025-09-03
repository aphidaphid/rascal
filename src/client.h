#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Client {
  Client(const char* p_title);
  ~Client();

  void update();
  bool get_key(int p_key);

  GLFWwindow* handle;
  bool running;
  int width, height;
};

#endif /* CLIENT_H */
