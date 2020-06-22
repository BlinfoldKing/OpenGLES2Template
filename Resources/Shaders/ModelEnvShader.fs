precision mediump float;

uniform sampler2D u_texture;
uniform samplerCube u_skybox;
uniform vec3 u_camera;
uniform vec3 u_lightpos;
uniform vec3 u_lightcolor;
uniform vec3 u_ambientcolor;

varying vec2 v_uv;
varying vec3 v_pos;
varying vec3 v_norm;

void main()
{
	vec3 I = u_camera - v_pos;
	vec3 R = reflect(normalize(-I), normalize(v_norm));
	vec4 a = textureCube(u_skybox, R).rgba;
	vec4 b = texture2D(u_texture, v_uv).rgba;

	vec3 lightDir = normalize(u_lightpos - v_pos);
	float diff = max(dot(normalize(v_norm), lightDir), 0.0);
	vec3 diffuse = diff * u_lightcolor;

	vec3 halfwayDir = normalize(lightDir + I);
	float specularStrength = 0.5;	
	float spec = pow(max(dot(lightDir, halfwayDir), 0.0), 32.0);
	vec3 specular = specularStrength * spec * u_lightcolor; 


	gl_FragColor = vec4(u_ambientcolor + diffuse + specular, 1.0) * (b + a) ;
}
