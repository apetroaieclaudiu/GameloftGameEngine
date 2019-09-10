attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec2 a_uv_blend;
varying vec2 v_uv;
varying vec2 v_uv_blend;
uniform mat4 u_rot;

uniform sampler2D u_texture3;

void main()
{
vec4 posL = vec4(a_posL, 1.0);
vec4 vblend = texture2D(u_texture3, a_uv_blend);

posL = u_rot*posL;
gl_Position = posL;
v_uv = a_uv;
v_uv_blend = a_uv_blend;
}
   