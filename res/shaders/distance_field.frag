#version 150 core

uniform sampler2D u_tex0;

in vec2 tex_coord;

out vec4 fragColor;

void main() {
  fragColor.rgb = texture(u_tex0, tex_coord).bbb;
}
