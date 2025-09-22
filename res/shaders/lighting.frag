#version 150

uniform sampler2D u_tex0; // distance field
uniform sampler2D u_tex1; // scene

uniform vec2 u_resolution;

in vec2 tex_coord;

out vec4 fragColor;

#define PI 3.141596
#define TWO_PI 6.2831853071795864769252867665590
#define TAU 0.001
#define DECAY_RATE 1.2
#define MAX_STEPS 128
#define RAYS_PER_PX 256

void main() {
  vec3 light = texture(u_tex1, tex_coord).rgb;

  vec2 resolution = textureSize(u_tex0, 0);
  for (float a = 0; a < TWO_PI; a += TWO_PI/RAYS_PER_PX) {
    vec2 dir = vec2(sin(a), cos(a));
    vec2 uv = tex_coord;
    for (int step = 0; step < MAX_STEPS; step++) {
      if (uv.x != clamp(uv.x, 0.0, 1.0) || uv.y != clamp(uv.y, 0.0, 1.0)) break;

      float dist = texture(u_tex0, uv).r;
      uv += dir * dist * vec2(resolution.y/resolution.x, 1.0);

      if (dist <= TAU) {
        light += texture(u_tex1, uv).rgb;
        break;
      }
    }
  }
  light /= RAYS_PER_PX;

  fragColor = vec4(light, 1.0);
}
