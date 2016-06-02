#version 400

in vec2 vertexPos;
in vec2 rectCenter;
in vec2 rectDimensions; //height and width

uniform vec4 color; 
uniform float borderThickness;

void main()
{
	vec2 pos = vertexPos - rectCenter;
	
	float xBorderFactor = (1.0 - step(abs(pos.x), width/2.0 - borderThickness)) * 
	(1.0 - step(height/2.0 - cornerRadius, abs(pos.y)));
	
	float yBorderFactor = (1.0 - step(abs(pos.y), height/2.0 - borderThickness)) * 
	(1.0 - step(width/2.0 - cornerRadius, abs(pos.x)));
	
	float borderFactor = clamp(xBorderFactor + yBorderFactor, 0.0, 1.0);
	
	gl_FragColor = vec4(color.xyz, color.w * borderFactor);
}

