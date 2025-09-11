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
  int width, height;

  bool running;
  double delta_time;

  KeyState keyboard[GLFW_KEY_LAST];

  struct {
    double x, y;
    bool m1, m2, m3, is_pressed;
  } mouse;
};

#endif /* CLIENT_H */
