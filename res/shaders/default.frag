#version 150 core

uniform float u_time;
uniform sampler2D u_tex0;
uniform sampler2D u_tex1;

in vec3 colour;
in vec2 tex_coord;

out vec4 fragColor;

void main()
{
  vec4 tex0col = texture(u_tex0, tex_coord);
  vec4 tex1col = texture(u_tex1, tex_coord);
  fragColor = mix(tex0col, tex1col, sin(u_time));
}
