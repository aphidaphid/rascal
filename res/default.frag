#version 150 core

uniform float u_time;
uniform sampler2D tex;

in vec3 colour;
in vec2 tex_coord;

out vec4 fragColor;

void main()
{
  // fragColor = vec4(colour + vec3(sin(u_time)), 1.0);
  fragColor = texture(tex, tex_coord) * vec4(colour, 1.0);
}
