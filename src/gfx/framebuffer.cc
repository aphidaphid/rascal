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

void Framebuffer::render(Shader* shader) {
  if (!shader)
    shader = g_state.shaders[Default];

  glBindVertexArray(quad.vao);
  glBindBuffer(GL_ARRAY_BUFFER, quad.vbo);

  colour_buffer.use();
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
