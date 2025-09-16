#include "framebuffer.h"
#include "state.h"

extern State g_state;

Framebuffer::Framebuffer()
// {
: colour_buffer{800, 600} {
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

void Framebuffer::render(Shader* shader) {
  colour_buffer.use();
  g_state.render_screen_rect();
}
