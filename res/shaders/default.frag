#version 150 core

uniform float u_time;
uniform sampler2D u_tex0;
uniform sampler2D u_tex1;

in vec3 colour;
in vec2 tex_coord;

out vec4 fragColor;

void main() {
  fragColor = texture(u_tex0, tex_coord);
  // fragColor = vec4(tex_coord, 0.0, 1.0);
}
