#include "client.h"
#include "state.h"

extern State g_state;

static void error_callback(int err, const char* description) {
  std::cerr << " error: " << description << "(" << err << ")\n";
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  // DPRINT(key);
  // DPRINT(static_cast<char>(key));
  // DPRINT(scancode);
  // DPRINT(action);
  // DPRINT(mods);
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  g_state.client.cursor.button = static_cast<MouseButton>(button);
  g_state.client.cursor.is_pressed = action && !g_state.ui->WantCaptureMouse;
}

static void scroll_callback(GLFWwindow* window, double xoff, double yoff) {
  // multiply with `g_state.client.camera.scale/1.0f` to zoom linearly
  g_state.camera.scale += yoff * g_state.camera.scale/1.0f * g_state.client.delta_time * 2;
  if (g_state.camera.scale < 0.0f)
    g_state.camera.scale = 0.01f;
}

Client::Client(const char* p_title)
: running{false}, cursor{} {
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
  while (!glfwGetWindowAttrib(handle, GLFW_HOVERED)) {
  }

  delta_time = glfwGetTime() - last_frame_time;
  last_frame_time = glfwGetTime();
  glfwSwapBuffers(handle);
  glfwPollEvents();

  glClear(GL_COLOR_BUFFER_BIT);

  glfwGetFramebufferSize(handle, &width, &height);
  glViewport(0, 0, width, height);

  running = !glfwWindowShouldClose(handle);

  glfwGetCursorPos(handle, &cursor.x, &cursor.y);
}

double Client::get_time() {
  return glfwGetTime();
}

bool Client::get_key(int p_key) {
  return glfwGetKey(handle, p_key);
}
