#version 400

attribute vec3 vertex; // x and y position on screen and z-layer, usually 0
attribute vec2 heightAndWidth; // height and width of rectangle on screen
//attribute vec2 uvDim; // height and width in texture
//attribute vec2 uv; // top-left corner of uv coordinate

out VS_OUT{
	vec2 heightAndWidth0;
} vs_out;
//out vec2 uvDim0;
//out vec2 texCoord0;

void main()
{
	gl_Position = vec4(vertex, 1.0);
	vs_out.heightAndWidth0 = heightAndWidth;
	//texCoord0 = uv;
	//uvDim0 = uvDim;
}