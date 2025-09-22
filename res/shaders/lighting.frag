#version 150

uniform sampler2D u_tex0; // distance field
uniform sampler2D u_tex1; // scene

uniform int u_rays_per_px;
uniform int u_max_steps;
uniform vec2 u_resolution;

in vec2 tex_coord;

out vec4 fragColor;

#define PI 3.141596
#define TWO_PI 6.2831853071795864769252867665590
#define TAU 0.001
#define DECAY_RATE 1.2

void main() {
  vec2 fragCoord = gl_FragCoord.xy/textureSize(u_tex0, 0);

  vec3 light = texture(u_tex1, tex_coord).rgb;

  for (float a = 0; a < TWO_PI; a += TWO_PI/u_rays_per_px) {
    vec2 dir = vec2(sin(a), cos(a));
    vec2 uv = tex_coord;
    for (int step = 0; step < u_max_steps; step++) {
      float dist = texture(u_tex0, uv).r;
      uv += dir * dist;

      if (uv.x != clamp(uv.x, 0.0, 1.0) || uv.y != clamp(uv.y, 0.0, 1.0)) continue;

      if (dist <= TAU) {
        light += texture(u_tex1, uv).rgb;
        break;
      }
    }
  }
  light /= u_rays_per_px;

  fragColor = vec4(light, 1.0);
}
