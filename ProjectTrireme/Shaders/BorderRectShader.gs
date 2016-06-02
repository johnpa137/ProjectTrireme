#version 400

// vertex shader is color rect shader

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

out vec2 vertexPos;
out vec2 rectCenter;
out vec2 rectDimensions; //height and width

uniform float borderThickness;

void main()
{
	vec4 pos = vec4(gl_in[0].gl_Position.xy + vec2(-borderThickness, -borderThickness), 0.0, 1.0);
	float width = gl_in[0].gl_Position.z + borderThickness * 2.0;
	float height = gl_in[0].gl_Position.w + borderThickness * 2.0;
	float rectCenter0 = pos + vec2(width/2.0, height/2.0);
	
	vertexPos = pos.xy;
	rectCenter = rectCenter0;
	rectDimensions = vec2(width, height);
	gl_Position = pos;
	EmitVertex();
	
	pos = gl_in[0].gl_Position + vec4(width, 0.0, 0.0, 1.0);
	vertexPos = pos.xy;
	rectCenter = rectCenter0;
	rectDimensions = vec2(width, height);
	gl_Position = pos;
	EmitVertex();
	
	pos = gl_in[0].gl_Position + vec4(width, -height, 0.0, 1.0);
	vertexPos = pos.xy;
	rectCenter = rectCenter0;
	rectDimensions = vec2(width, height);
	gl_Position = pos;
	EmitVertex();
	
	pos = gl_in[0].gl_Position + vec4(0.0, -height, 0.0, 1.0);
	vertexPos = pos.xy;
	rectCenter = rectCenter0;
	rectDimensions = vec2(width, height);
	gl_Position = pos;
	EmitVertex();
	
	EndPrimitive();
}

