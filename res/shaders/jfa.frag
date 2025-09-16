#version 150 core

uniform float u_time;
uniform sampler2D u_tex0;

in vec3 colour;
in vec2 tex_coord;

out vec4 fragColor;

void main() {
  fragColor = texture(u_tex0, tex_coord);
  if (fragColor == vec4(0.0, 0.0, 0.0, 1.0)) {
    fragColor = vec4(1.0);
  }
  // fragColor = vec4(1.0, 0.0, 1.0, 1.0);
}
