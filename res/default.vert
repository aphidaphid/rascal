#version 150 core

in vec2 a_position;
in vec3 a_colour;

out vec3 colour;

void main()
{
  colour = a_colour;
  vec2 pos = a_position;
  pos.y = -pos.y;
  gl_Position = vec4(pos, 0.0, 1.0);
}
