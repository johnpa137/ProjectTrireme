#version 400

uniform sampler2D diffuse;

varying vec2 texCoord;

void main()
{
	// gl_FragColor = texture2D(diffuse, texCoord);
	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}