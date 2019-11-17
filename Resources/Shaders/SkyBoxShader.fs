precision mediump float;
varying vec3 v_coord;
uniform samplerCube u_texture;
void main()
{
	vec4 vfinal = textureCube(u_texture, v_coord);
	gl_FragColor = vfinal;

}
