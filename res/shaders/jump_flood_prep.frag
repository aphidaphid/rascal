#version 150 core

uniform sampler2D u_tex0;

in vec2 tex_coord;

out vec4 fragColor;

void main() {
  fragColor = texture(u_tex0, tex_coord);
  if (fragColor.a == 1.0) {
    fragColor = vec4(tex_coord, 0.0, 1.0);
  }
}
