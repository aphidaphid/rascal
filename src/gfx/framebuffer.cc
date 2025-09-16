#include "framebuffer.h"
#include "state.h"

extern State g_state;

Framebuffer::Framebuffer()
// {
: colour_buffer{800, 600}, quad{} {
// : colour_buffer{"res/textures/concrete_512px.jpg"} {
  glGenFramebuffers(1, &handle);

  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != GL_FRAMEBUFFER_COMPLETE) {
    std::cerr << "framebuffer creation failed: " << status << "\n";
    std::abort();
  }

  glBindFramebuffer(GL_FRAMEBUFFER, handle);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colour_buffer.handle, 0);
  glClear(GL_COLOR_BUFFER_BIT);

  use_default();
}

Framebuffer::~Framebuffer() {
  glDeleteFramebuffers(1, &handle);
}

void Framebuffer::use() {
  glBindFramebuffer(GL_FRAMEBUFFER, handle);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Framebuffer::use_default() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::render() {
  // glBindVertexArray(quad.vao);
  //
  // quad.shader->use();
  // glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
  // glm::mat4 view = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0f));
  // glm::mat4 proj = glm::ortho(g_state.camera.x, g_state.camera.x+static_cast<float>(g_state.client.width), g_state.camera.y, g_state.camera.y+static_cast<float>(g_state.client.height), 0.0f, 1000.0f);
  // proj = glm::scale(proj, glm::vec3(glm::vec2(g_state.camera.scale), 1.0f));
  //
  // shader->set_mat4("u_model", model);
  // shader->set_mat4("u_view", view);
  // shader->set_mat4("u_proj", proj);
  //
  // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
