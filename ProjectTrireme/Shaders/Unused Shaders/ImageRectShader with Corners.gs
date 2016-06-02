#version 400

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in vec4 uvRect;

out vec2 vertexPos;
out vec2 uvCoord;
out vec2 cornerCenter; // height and width

uniform vec2 imageScale;
uniform float cornerRadius;

void main()
{
	vec4 pos = vec4(gl_in[0].gl_Position.xy, 0.0, 1.0);
	float width = gl_in[0].gl_Position.z;
	float height = gl_in[0].gl_Position.w;
	float uvWidth = uvRect.z;
	float uvHeight = uvRect.w;
	vec2 uvCenter = uvRect.xy + vec2(uvWidth/2.0, -(uvHeight/2.0));
	float uvScaleWidth = uvWidth * imageScale;
	float uvScaleHeight = uvHeight * imageScale;
	vec2 rectCenter = pos + vec2(width/2.0, height/2.0);
	float halfWidthMinusCorner = width/2.0 - cornerRadius;
	float halfHeightMinusCorner = height/2.0 - cornerRadius;
	
	uvCoord = uvCenter + vec2(-uvScaleWidth, uvScaleHeight);
	vertexPos = pos;
	cornerCenter = rectCenter + vec2(-halfWidthMinusCorner, halfHeightMinusCorner);
	gl_Position = pos;
	EmitVertex();
	
	pos = gl_in[0].gl_Position + vec4(width, 0.0, 0.0, 0.0);
	uvCoord = uvCenter + vec2(uvScaleWidth, uvScaleHeight);
	vertexPos = pos;
	cornerCenter = rectCenter + vec2(halfWidthMinusCorner, halfHeightMinusCorner);
	gl_Position = pos;
	EmitVertex();
	
	pos = gl_in[0].gl_Position + vec4(width, -height, 0.0, 0.0);
	uvCoord = uvCenter + vec2(uvScaleWidth, -uvScaleHeight);
	vertexPos = pos;
	cornerCenter = rectCenter + vec2(halfWidthMinusCorner, -halfHeightMinusCorner);
	gl_Position = pos;
	EmitVertex();
	
	pos = gl_in[0].gl_Position + vec4(0.0, -height, 0.0, 0.0);
	uvCoord = uvCenter + vec2(-uvScaleWidth, -uvScaleHeight);
	vertexPos = pos;
	cornerCenter = rectCenter + vec2(-halfWidthMinusCorner, -halfHeightMinusCorner);
	gl_Position = pos;
	EmitVertex();
	
	EndPrimitive();
}

