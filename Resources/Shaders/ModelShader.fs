precision mediump float;
varying vec2 v_uv;
varying vec4 v_scenePos;
uniform sampler2D u_texture;
uniform float u_r;
uniform float u_R;
uniform vec3 u_fogColor;
uniform vec3 u_camPos;
void main()
{
	vec4 color = texture2D(u_texture, v_uv);

    float d = distance(v_scenePos, vec4(u_camPos, 1.0));
    float alpha = clamp((d - u_r) / (u_R - u_r), 0.0, 1.0);
    color = alpha * vec4(u_fogColor, 1.0) + (1.0 - alpha) * color;

	if(color.a < 0.1)
	discard;
	
	gl_FragColor = color;

}
