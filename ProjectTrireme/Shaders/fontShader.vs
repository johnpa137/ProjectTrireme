#version 400

attribute vec4 vertex;

varying vec2 uvCoord;

void main()
{
	gl_Position = vec4(vertex.xy, 0.0, 1.0);
	uvCoord = vertex.zw;
}