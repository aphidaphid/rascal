#version 150 core

uniform float u_time;

in vec3 colour;

out vec4 fragColor;

void main()
{
  fragColor = vec4(colour + vec3(sin(u_time)), 1.0);
}
