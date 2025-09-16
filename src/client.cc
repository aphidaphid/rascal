#include "client.h"
#include "state.h"

extern State g_state;

static void error_callback(int err, const char* description) {
  std::cerr << " error: " << description << "(" << err << ")\n";
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);

  g_state.client.keyboard[key] = static_cast<KeyState>(action);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  switch (button) {
    case 0:
      g_state.client.mouse.m1 = action && !g_state.ui->WantCaptureMouse;
      break;
    case 1:
      g_state.client.mouse.m2 = action && !g_state.ui->WantCaptureMouse;
      break;
    case 2:
      g_state.client.mouse.m3 = action && !g_state.ui->WantCaptureMouse;
      break;
  }
  g_state.client.mouse.is_pressed = (g_state.client.mouse.m1 || g_state.client.mouse.m2 || g_state.client.mouse.m3) && !g_state.ui->WantCaptureMouse;
}

static void scroll_callback(GLFWwindow* window, double xoff, double yoff) {
#ifndef STATIC_CAMERA
  if (g_state.ui->WantCaptureMouse)
    return;
  // multiply with `g_state.client.camera.scale/1.0f` to zoom linearly
  g_state.camera.scale += yoff * g_state.camera.scale/1.0f * g_state.client.delta_time * 2;
  if (g_state.camera.scale < 0.0f)
    g_state.camera.scale = 0.01f;
#endif
}

static void window_size_callback(GLFWwindow* window, int width, int height) {
  g_state.client.width = width;
  g_state.client.height = height;
  glfwGetFramebufferSize(g_state.client.handle, &width, &height);
  glViewport(0, 0, width, height);
}

Client::Client(const char* p_title)
: running{false}, mouse{} {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    std::cerr << "glfw failed to initialise\n";
    std::abort();
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  handle = glfwCreateWindow(800, 600, p_title, NULL, NULL);
  if (!handle) {
    std::cerr << "GLFWwindow failed to initialise\n";
  }

  glfwSetKeyCallback(handle, key_callback);
  glfwSetMouseButtonCallback(handle, mouse_button_callback);
  glfwSetScrollCallback(handle, scroll_callback);
  glfwSetWindowSizeCallback(handle, window_size_callback);

  glfwGetFramebufferSize(handle, &width, &height);
  glfwMakeContextCurrent(handle);
  glfwSwapInterval(1); // vsync
  gladLoadGL();

  running = true;
}

Client::~Client() {
  glfwDestroyWindow(handle);
  glfwTerminate();
}

void Client::update() {
  // while (!glfwGetWindowAttrib(handle, GLFW_HOVERED)) {
  // }

  static double last_frame_time{};
  delta_time = glfwGetTime() - last_frame_time;
  last_frame_time = glfwGetTime();
  glfwSwapBuffers(handle);
  glfwPollEvents();

  glClear(GL_COLOR_BUFFER_BIT);

  running = !glfwWindowShouldClose(handle);

  glfwGetCursorPos(handle, &mouse.x, &mouse.y);
}

double Client::get_time() {
  return glfwGetTime();
}

KeyState Client::get_key(int p_key) {
  KeyState result = keyboard[p_key];
  /* such that there is one press event */
  if (keyboard[p_key] == KeyState::Press) {
    keyboard[p_key] = KeyState::Repeat;
  }
  return result;
}

bool Client::get_key_no_repeat(int p_key) {
  return get_key(p_key) == KeyState::Press;
}
