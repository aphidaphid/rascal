#version 150 core

uniform float u_time;
uniform sampler2D u_tex0;

in vec3 colour;
in vec2 tex_coord;

out vec4 fragColor;

void main() {
  fragColor = vec4(colour, 1.0);
}
