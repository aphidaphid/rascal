#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
