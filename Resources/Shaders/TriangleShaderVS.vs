attribute vec3 a_posL;
attribute vec3 a_color;
varying vec3 v_color;
uniform mat4 u_rot;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
posL = u_rot*posL;
gl_Position = posL;
v_color = a_color;
}
   