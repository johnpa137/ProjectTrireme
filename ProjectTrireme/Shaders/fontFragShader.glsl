#version 400

varying vec2 texCoord;
uniform sampler2D tex;
uniform vec3 text_color;

void main()
{
	gl_FragColor = vec4(1.0, 1.0, 1.0, texture2D(tex, texCoord).r) * vec4(text_color, 1.0);
	//gl_FragColor = vec4(text_color, 1.0);
}