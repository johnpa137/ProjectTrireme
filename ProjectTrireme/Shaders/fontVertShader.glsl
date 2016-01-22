#version 400

attribute vec4 vertex;

varying vec2 texCoord;

void main()
{
	gl_Position = vec4(vertex.x, vertex.y, 0.0, 1.0);
	texCoord = vec2(vertex.z, vertex.w);
}