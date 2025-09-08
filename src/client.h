#ifndef CLIENT_H
#define CLIENT_H

#define DPRINT(x) std::cout << #x": " << x << "\n"

#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Client {
  Client(const char* p_title);
  ~Client();

  void update();

  double get_time();
  bool get_key(int p_key);

  GLFWwindow* handle;
  bool running;
  int width, height;
  double delta_time;

  struct {
    double x, y;
    bool m1, m2, m3, is_pressed;
  } mouse;
};

#endif /* CLIENT_H */
