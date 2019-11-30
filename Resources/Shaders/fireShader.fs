precision mediump float;
varying vec2 v_uv;
varying vec4 v_scenePos;
uniform sampler2D u_texture;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform float u_r;
uniform float u_R;
uniform float u_time;
uniform float u_dispMax;
uniform vec3 u_fogColor;
uniform vec3 u_camPos;
void main()
{
    vec2 disp = texture2D(u_texture, vec2(v_uv.x, v_uv.y + u_time)).rg;
    vec2 offset = vec2(u_dispMax * (2.0 * disp.x - 1.0), u_dispMax * (2.0 * disp.y - 1.0));
    vec2 v_uv_displaced = v_uv + offset;
    vec4 c_fire = texture2D(u_texture1, v_uv_displaced);
    vec4 c_alpha = texture2D(u_texture2, v_uv);
    c_fire.a *= c_alpha.r;

	vec4 color = texture2D(u_texture, v_uv);

    float d = distance(v_scenePos, vec4(u_camPos, 1.0));
    float alpha = clamp((d - u_r) / (u_R - u_r), 0.0, 1.0);
    color = alpha * vec4(u_fogColor, 1.0) + (1.0 - alpha) * color;

	if(color.a < 0.1)
	discard;
	
	gl_FragColor = c_fire;

}
