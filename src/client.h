#ifndef CLIENT_H
#define CLIENT_H

#define DPRINT(x) std::cout << #x": " << x << "\n"

#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum KeyState {
  Release,
  Press,
  Repeat
};

struct Client {
  Client(const char* p_title);
  ~Client();

  void update();

  double get_time();
  KeyState get_key(int p_key);
  bool get_key_no_repeat(int p_key);

  GLFWwindow* handle;
  bool running;
  int width, height;
  double delta_time;

  struct {
    double x, y;
    bool m1, m2, m3, is_pressed;
  } mouse;

  KeyState keyboard[GLFW_KEY_LAST];
};

#endif /* CLIENT_H */
