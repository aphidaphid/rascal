#include "client.h"

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
  g_client.cursor.button = static_cast<MouseButton>(button);
  g_client.cursor.is_pressed = action && !g_client.io->WantCaptureMouse;
}

static void scroll_callback(GLFWwindow* window, double xoff, double yoff) {
  g_client.camera.scale += yoff * g_client.camera.scale/1.0f * g_client.delta_time * 2;
  if (g_client.camera.scale < 0.0f)
    g_client.camera.scale = 0.01f;
}

Client::Client(const char* p_title)
: running{false}, cursor{} {
  std::cout << "creating client...\n";

  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    std::cerr << "glfw failed to initialise\n";
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

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
  std::cout << "client created\n";
}

void Client::init_ui() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  // ImGuiIO& io = ImGui::GetIO(); (void)io;
  io = &ImGui::GetIO();
  ImGui_ImplGlfw_InitForOpenGL(handle, true);
  ImGui_ImplOpenGL3_Init("#version 150");
}

Client::~Client() {
  glfwDestroyWindow(handle);
  glfwTerminate();
}

void Client::update() {
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

void Client::ui_begin() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void Client::ui_end() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool Client::get_key(int p_key) {
  return glfwGetKey(handle, p_key);
}
