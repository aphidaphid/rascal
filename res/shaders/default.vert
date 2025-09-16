#version 150 core

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

in vec3 a_colour;
in vec2 a_tex_coord;
in vec2 a_position;

out vec3 colour;
out vec2 tex_coord;

void main() {
  colour = a_colour;
  tex_coord = a_tex_coord;
  gl_Position = u_proj * u_view * u_model * vec4(a_position, 0.0, 1.0);
}
