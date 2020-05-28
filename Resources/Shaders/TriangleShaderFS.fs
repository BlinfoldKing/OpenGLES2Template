precision mediump float;
varying lowp vec4 posL;

void main()
{
	vec3 position = posL.xyz;
	vec3 color = position + vec3(0.5, 0.5, 0.5);
	gl_FragColor = vec4(color, 1.0);
}
