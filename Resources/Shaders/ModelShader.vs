attribute vec3 a_posL;
attribute vec2 a_uv;
varying vec2 v_uv;
varying vec4 v_scenePos;
uniform mat4 u_scenePos;
uniform mat4 u_rot;

void main()
{
vec4 posL = vec4(a_posL, 1.0);
v_scenePos = u_scenePos * posL;
posL = u_rot*posL;
gl_Position = posL;
v_uv = a_uv;

}
   