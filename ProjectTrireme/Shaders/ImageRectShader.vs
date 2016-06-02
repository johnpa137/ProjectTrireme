#version 400

attribute vec4 InVertex; // x, y, width, height
attribute vec4 InUVRect; // x, y, width, height

out vec4 uvRect;

void main()
{
	gl_Position = InVertex;
	uvRect = InUVRect;
}