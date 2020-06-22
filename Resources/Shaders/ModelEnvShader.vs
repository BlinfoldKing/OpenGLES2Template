attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec3 a_normal;
uniform mat4 u_model;
uniform mat4 u_world;

varying vec2 v_uv;
varying vec3 v_pos;
varying vec3 v_norm;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_world * posL;
	v_norm = mat3(u_model) * a_normal;
	v_pos = mat3(u_model) * a_posL;
	v_uv = a_uv;
}
