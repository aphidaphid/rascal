#version 150 core

uniform sampler2D u_tex0; // emission map
uniform sampler2D u_tex1; // occlusion map

in vec2 tex_coord;

out vec4 fragColor;

void main() {
  vec4 emission = texture(u_tex0, tex_coord);
  vec4 occlusion = texture(u_tex1, tex_coord);
  fragColor = occlusion == vec4(0.0, 0.0, 0.0, 0.0) ? emission : vec4(0.0, 0.0, 0.0, occlusion.a);
  if (fragColor.a == 1.0) {
    fragColor = vec4(tex_coord, 0.0, 1.0);
  }
}
