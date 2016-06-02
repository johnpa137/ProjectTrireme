#version 400

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in VS_OUT {
	vec2 heightAndWidth0;
    //vec2 uvDim0;
    //vec2 texCoord0;
} gs_in[];

//in vec2 heightAndWidth0;
//in vec2 uvDim0;
//in vec2 texCoord0;

//uniform mat4 camera;

//out vec2 texCoord1;

void main()
{
	vec4 pos = gl_in[0].gl_Position;
	gl_Position = pos;
	//texCoord1 = gs_in[0].texCoord0;
	EmitVertex();
	
	pos = gl_in[0].gl_Position + vec4(gs_in[0].heightAndWidth0.x, 0.0, 0.0, 0.0);
	gl_Position = pos;
	//texCoord1 = gs_in[0].texCoord0 + vec2(gs_in[0].uvDim0.x, 0.0);
	EmitVertex();
	
	pos = gl_in[0].gl_Position + vec4(0.0, -gs_in[0].heightAndWidth0.y, 0.0, 0.0);
	gl_Position = pos;
	//texCoord1 = gs_in[0].texCoord0 + vec2(0.0, -gs_in[0].uvDim0.y);
	EmitVertex();
	
	pos = gl_in[0].gl_Position + vec4(gs_in[0].heightAndWidth0.x, -gs_in[0].heightAndWidth0.y, 0.0, 0.0);
	gl_Position = pos;
	//texCoord1 = gs_in[0].texCoord0 + vec2(gs_in[0].uvDim0.x, -gs_in[0].uvDim0.y);
	EmitVertex();
	
	EndPrimitive();
}

