#version 400

in vec2 vertexPos;
in vec2 uvCoord;

uniform sampler2D image;

void main()
{
	gl_FragColor = texture2D(image, uvCoord);
}

