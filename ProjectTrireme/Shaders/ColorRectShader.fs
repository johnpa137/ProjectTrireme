#version 400

in vec2 vertexPos;

uniform vec4 color;

void main()
{
	gl_FragColor = color;
}

