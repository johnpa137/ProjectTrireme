#version 400

// geometry shader is the gradient rect gs

in vec2 vertexPos;
in vec2 gradientOrigin;

uniform vec4 gradientVector; // origin(x, y), direction(x, y), direction is normalized
uniform vec4 color1; // can be used for normal ColorRects
uniform vec4 color2;
uniform vec2 gradientScales; // major and minor(not in order) radii of gradient
uniform float gradientOffset;

vec2 rotate2D(vec2 vector, float angle); // rotates vector using angle

void main()
{
	vec2 origin = gradientOrigin;
	vec2 direction = gradientVector.zw;
	
	float angle = acos(dot(vec2(0.0, 1.0), direction));
	
	vec2 rotatedPos = abs(rotate2D(vertexPos - origin, -angle));
	
	float xScaled = rotatedPos.x / gradientScales.x;
	float yScaled = rotatedPos.y / gradientScales.y;

	// length should be return something between 0.0 and 1.0, unless the point is purposefully out of bounds
	float gradientFactor = clamp(length(vec2(xScaled, yScaled)), 0.0, 1.0); 
	
	gradientFactor = smoothstep(gradientOffset, 1.0, gradientFactor);
	
	vec4 color = mix(color1, color2, gradientFactor);
	
	gl_FragColor = color;
}

vec2 rotate2D(vec2 vector, float angle)
{
	mat2 rotationMatrix = mat2(cos(angle), sin(angle), -sin(angle), cos(angle));
	
	return vector * rotationMatrix;
}
