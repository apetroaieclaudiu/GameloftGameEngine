precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_texture;
uniform float u_r;
uniform float u_R;
uniform vec3 u_fogColor;
uniform vec3 u_camPos;
void main()
{
	vec4 color = texture2D(u_texture, v_uv);

	if(color.a < 0.1)
	discard;
	
	gl_FragColor = color;

}
