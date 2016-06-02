#version 400

varying vec2 uvCoord;
uniform sampler2D tex;
uniform vec3 text_color;

void main()
{
	gl_FragColor = vec4(1.0, 1.0, 1.0, texture2D(tex, uvCoord).r) * vec4(text_color, 1.0);
}