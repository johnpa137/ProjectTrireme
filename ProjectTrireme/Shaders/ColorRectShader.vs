#version 400

attribute vec4 InVertex; // x, y, width, height

void main()
{
	gl_Position = InVertex;
}