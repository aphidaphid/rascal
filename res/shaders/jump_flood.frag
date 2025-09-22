#version 150 core

uniform int u_jump_size;
uniform sampler2D u_tex0;

in vec2 tex_coord;

out vec4 fragColor;

void main() {
  fragColor = texture(u_tex0, tex_coord);
  vec2 resolution = textureSize(u_tex0, 0);
  vec2 ndc = gl_FragCoord.xy/resolution;
  float closest = 1.0; // in px
  for (int x = -1; x <= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      vec2 neighbour_coord = ndc + (vec2(x, y)/resolution) * u_jump_size; // in ndc
      vec4 neighbour_sample = texture(u_tex0, neighbour_coord);

      if (neighbour_coord != clamp(neighbour_coord, 0.0, 1.0)) continue;
      if (neighbour_sample.a == 0) continue;

      float d = length((neighbour_sample.rg - ndc) * vec2(resolution.x/resolution.y, 1.0));
      if (d < closest || closest == 1.0) {
        closest = d;
        fragColor = vec4(neighbour_sample.rg, d, 1.0);
      }
    }
  }
}
