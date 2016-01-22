#version 400

attribute vec3 vertex;
attribute vec2 uv;

uniform mat4 camera_matrix;
uniform vec3 object_pos;

varying vec2 texCoord;

void main()
{
	texCoord = uv;
	gl_Position = camera_matrix * vec4(vertex + object_pos, 1.0);
}