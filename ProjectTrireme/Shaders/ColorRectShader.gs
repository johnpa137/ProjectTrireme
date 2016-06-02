#version 400

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

out vec2 vertexPos;

void main()
{
	// top left corner
	vec4 pos = vec4(gl_in[0].gl_Position.xy, 0.0, 1.0);
	float width = gl_in[0].gl_Position.z;
	float height = gl_in[0].gl_Position.w;
	
	vertexPos = pos.xy;
	gl_Position = pos;
	EmitVertex();
	
	// top right corner
	pos = gl_in[0].gl_Position + vec4(width, 0.0, 0.0, 1.0);
	vertexPos = pos.xy;
	gl_Position = pos;
	EmitVertex();
	
	// bottom right corner
	pos = gl_in[0].gl_Position + vec4(width, -height, 0.0, 1.0);
	vertexPos = pos.xy;
	gl_Position = pos;
	EmitVertex();
	
	// bottom left corner
	pos = gl_in[0].gl_Position + vec4(0.0, -height, 0.0, 1.0);
	vertexPos = pos.xy;
	gl_Position = pos;
	EmitVertex();
	
	EndPrimitive();
}

