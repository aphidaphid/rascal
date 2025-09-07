#ifndef GFX_COMMON_H
#define GFX_COMMON_H

#include "client.h"
#include <cassert>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern struct Camera {
  float x, y;
  // glm::vec2 position;
  // float &x{position.x}, &y{position.y};
} g_camera;

#endif /* GFX_COMMON_H */
