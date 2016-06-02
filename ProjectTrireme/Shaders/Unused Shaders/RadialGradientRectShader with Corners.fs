#version 400

in vec2 vertexPos;
in vec2 uvCoord;
in vec2 cornerCenter; // center of corner based on cornerRadius

uniform vec4 gradientVector; // origin(x, y), direction(x, y), direction is normalized
uniform vec4 color1; // can be used for normal ColorRects
uniform vec4 color2;
uniform vec2 gradientScales; // magnitudes for each vector in the gradient, lengths of gradient vector
uniform float gradientOffset;
uniform float cornerRadius;

mat2 rotateXY(float angle); // returns 2D rotation matrix
float checkIfAtCorner(); // returns 1.0 if at corner, otherwise 0.0

void main()
{
	vec2 origin = gradientVector.xy;
	vec2 direction = gradientVector.zw;
	
	float angle = acos(dot(vec2(0.0, 1.0), direction));
	
	mat2 rotationMatrix = rotateXY(-angle);
	
	vec2 rotatedPos = ((vertexPos - origin) * rotationMatrix);
	
	float xRelativeToVector = clamp((rotatedPos.x - gradientOffset) / (gradientScales.x - gradientOffset), 0.0, 1.0);
	
	float yRelativeToVector = clamp((rotatedPos.y - gradientOffset) / (gradientScales.y - gradientOffset), 0.0, 1.0);

	float distanceFromOriginAfterScales = min(length(vec2(xRelativeToVector, yRelativeToVector)), 1.0);
	
	vec4 color = mix(color1, color2, distanceFromOriginAfterScales);
	
	color = vec4(color.xyz, (1.0 - checkIfAtCorner()));
	
	gl_FragColor = color;
}

mat2 rotateXY(float angle)
{
	return mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
}

float checkIfAtCorner()
{
	vec2 pos = vertexPos - cornerCenter;
	
	float cornerFactor = step(pos.x, 0.0);
	
	cornerFactor = cornerFactor * step(0.0, pos.y);
	
	cornerFactor = cornerFactor * pow(pos.x, 2.0) + pow(pos.y, 2.0);
	
	cornerFactor = step(cornerFactor, pow(cornerRadius, 2.0));
	
	return cornerFactor;
}

