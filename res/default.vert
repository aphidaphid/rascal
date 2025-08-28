#version 150 core

in vec2 a_position;
in vec3 a_colour;
in vec2 a_tex_coord;

out vec3 colour;
out vec2 tex_coord;

void main()
{
  colour = a_colour;
  tex_coord = a_tex_coord;
  gl_Position = vec4(a_position, 0.0, 1.0);
}
