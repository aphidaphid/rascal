#version 150 core

uniform float u_time;
uniform sampler2D u_tex0; // emission map
uniform sampler2D u_tex1; // occlusion map

in vec3 colour;
in vec2 tex_coord;

out vec4 fragColor;

void main() {
  vec4 emission = texture(u_tex0, tex_coord);
  vec4 occlusion = texture(u_tex1, tex_coord);

  vec4 col = occlusion == vec4(0.0, 0.0, 0.0, 0.0) ? emission : occlusion;

  fragColor = col;
}
