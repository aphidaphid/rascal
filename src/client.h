#ifndef CLIENT_H
#define CLIENT_H

#define DPRINT(x) std::cout << #x": " << x << "\n"

#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum MouseButton {
  MOUSE_1 = 0,
  MOUSE_2,
  MOUSE_3
};

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
  double last_frame_time;

  struct {
    double x, y;
    MouseButton button;
    bool is_pressed;
  } cursor;
};

#endif /* CLIENT_H */
