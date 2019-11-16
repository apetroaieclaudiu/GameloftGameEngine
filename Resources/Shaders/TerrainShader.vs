attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec2 a_uv_blend;
varying vec2 v_uv;
varying vec2 v_uv_blend;
uniform mat4 u_rot;
uniform vec3 height;

uniform sampler2D u_texture3;

void main()
{
vec4 posL = vec4(a_posL, 1.0);
vec4 vblend = texture2D(u_texture3, a_uv_blend);

vec4 pos_new = posL;
//pos_new.y += vblend.r * 10.0 + vblend.g * 0.0 + vblend.b * 2.0;
pos_new.y += vblend.r * height.r + vblend.g * height.g + vblend.b * height.b;
gl_Position = u_rot*pos_new;
v_uv = a_uv;
v_uv_blend = a_uv_blend;
}
   