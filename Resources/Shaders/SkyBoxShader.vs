attribute vec3 a_posL;
varying vec3 v_coord;
uniform mat4 u_rot;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
posL = u_rot*posL;
gl_Position = posL;
v_coord = a_posL;
}
   