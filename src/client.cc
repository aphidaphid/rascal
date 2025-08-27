#include "client.h"

static void error_callback(int err, const char* description)
{
  std::cerr << err << " error: " << description << "\n";
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Client::Client(const char* p_title)
: running{false} {
  if (!glfwInit()) {
    std::cerr << "glfw failed to initialise\n";
  }

  glfwSetErrorCallback(error_callback);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  handle = glfwCreateWindow(800, 600, p_title, NULL, NULL);
  if (!handle) {
    std::cerr << "GLFWwindow failed to initialise\n";
  }

  glfwSetKeyCallback(handle, key_callback);

  glfwMakeContextCurrent(handle);
  gladLoadGL();

  running = true;
}

Client::~Client() {
  glfwDestroyWindow(handle);
  glfwTerminate();
}

void Client::update() {
  glfwSwapBuffers(handle);
  glfwPollEvents();

  glClear(GL_COLOR_BUFFER_BIT);

  int width, height;
  glfwGetFramebufferSize(handle, &width, &height);
  glViewport(0, 0, width, height);

  running = !glfwWindowShouldClose(handle);
}
