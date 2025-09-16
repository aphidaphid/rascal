#include "state.h"

State::State()
: debug{false}, shaders{}, screen_rect{} {
  reload_shaders();
  camera = {-static_cast<float>(client.width)/2, -static_cast<float>(client.height)/2};
}

void State::update() {
  client.update();

  /* calc camera movement */
#ifndef STATIC_CAMERA
  static glm::vec2 curlastpos{};
  if (client.mouse.is_pressed) {
    glm::vec2 position{client.mouse.x, client.mouse.y};
    position -= curlastpos;
    camera.x -= position.x;
    camera.y += position.y;
  }
  curlastpos = { client.mouse.x, client.mouse.y };
#endif
}

void State::render_screen_rect(Shader* shader) {
  if (!shader)
    shader = g_state.shaders[Default];

  glBindVertexArray(screen_rect.vao);
  glBindBuffer(GL_ARRAY_BUFFER, screen_rect.vbo);

  shader->use();

  GLint posAttrib = glGetAttribLocation(shader->handle, "a_position");
  GLint colAttrib = glGetAttribLocation(shader->handle, "a_colour");
  GLint texCoordAttrib = glGetAttribLocation(shader->handle, "a_tex_coord");

  glVertexAttribPointer(posAttrib,      2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);
  glVertexAttribPointer(colAttrib,      3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(2*sizeof(float)));
  glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(5*sizeof(float)));

  glEnableVertexAttribArray(posAttrib);
  glEnableVertexAttribArray(colAttrib);
  glEnableVertexAttribArray(texCoordAttrib);

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::scale(model, glm::vec3(g_state.client.width, g_state.client.height, 1.0f));
  view = glm::scale(view, glm::vec3(1.0f, -1.0f, 1.0f));
  glm::mat4 proj = glm::ortho(
      -static_cast<float>(g_state.client.width)/2, static_cast<float>(g_state.client.width)/2,
      -static_cast<float>(g_state.client.height)/2, static_cast<float>(g_state.client.height)/2,
      0.0f, 1000.0f);

  shader->set_mat4("u_model", model);
  shader->set_mat4("u_view", view);
  shader->set_mat4("u_proj", proj);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void State::ui_init() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ui = &ImGui::GetIO();
  ImGui_ImplGlfw_InitForOpenGL(client.handle, true);
  ImGui_ImplOpenGL3_Init("#version 150");
}

void State::ui_begin() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void State::ui_end() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

#define DTEXT(x) ImGui::Text((#x": " + std::to_string(x)).c_str())

void State::ui_debug() {
  if (!debug) return;

  ImGui::Begin("debug");
  if (ImGui::BeginTabBar("tab_bar", ImGuiTabBarFlags_None)) {

    if (ImGui::BeginTabItem("state")) {
      static bool wireframe{false};
      if (ImGui::Checkbox("wireframe", &wireframe))
        glPolygonMode(GL_FRONT_AND_BACK, (wireframe) ? GL_LINE : GL_FILL);

      if (ImGui::Button("reload shaders")) {
        reload_shaders();
      }

      DTEXT(client.delta_time);
      DTEXT(client.get_time());
      DTEXT(camera.x);
      DTEXT(camera.y);
      DTEXT(camera.scale);

      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("input")) {
      DTEXT(client.mouse.x);
      DTEXT(client.mouse.y);
      ImGui::Checkbox("m1", &g_state.client.mouse.m1); ImGui::SameLine();
      ImGui::Checkbox("m2", &g_state.client.mouse.m2); ImGui::SameLine();
      ImGui::Checkbox("m3", &g_state.client.mouse.m3);
      ImGui::Checkbox("is_pressed", &g_state.client.mouse.is_pressed);

      ImGui::Separator();

      for (int i = 0; i < GLFW_KEY_LAST; i++) {
        KeyState ks = g_state.client.get_key(i);
        if (ks) {
          char ch = static_cast<char>(i);
          DTEXT(ch);
          ImGui::SameLine();
          ImGui::Text(&ch);
          ImGui::SameLine();
          ImGui::Text(ks == KeyState::Press ? "Press" : "Repeat");
        }
      }
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();

  }
  ImGui::End();
}

void State::reload_shaders() {
  for (int i = shaders.size()-1; i >= 0; i--) {
    delete shaders[i];
  }
  shaders.clear();

  #define LOAD_SHADER(x, y) shaders.insert(shaders.begin()+x,      new Shader("res/shaders/default.vert", "res/shaders/"#y".frag"))

  LOAD_SHADER(Default,      default);
  LOAD_SHADER(Error,        error);
  LOAD_SHADER(VertexColour, vertex_colour);
  LOAD_SHADER(Scene,        scene);
  LOAD_SHADER(JumpFlood,    jump_flood);
  // shaders.insert(shaders.begin()+Default,      new Shader("res/shaders/default.vert", "res/shaders/default.frag"));
  // shaders.insert(shaders.begin()+Error,        new Shader("res/shaders/default.vert", "res/shaders/error.frag"));
  // shaders.insert(shaders.begin()+VertexColour, new Shader("res/shaders/default.vert", "res/shaders/vertex_colour.frag"));
  // shaders.insert(shaders.begin()+Scene,        new Shader("res/shaders/default.vert", "res/shaders/scene.frag"));
}
