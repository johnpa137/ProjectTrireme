#version 400

in vec3 vertexPos;
in vec2 uvCoord;

uniform sampler2D image; // texture
uniform vec4 gradientVector; // origin(x, y), direction(x, y)
uniform vec4 color1; // can be used for normal ColorRects
uniform vec4 color2;
uniform vec2 gradientScales; // magnitudes for each vector in the gradient
uniform float gradientOffset;
uniform float cornerRadius;
uniform float borderThickness;

vec4 evaluateColor(vec4 color);
vec4 evaluateImage(vec4 color);
vec4 evaluateGradient(vec4 color);
vec4 evalutaBorder(vec4 color);
vec4 evaluateCorner(vec4 color);

void main()
{
	vec4 color = vec4(1.0, 1.0, 1.0, 1.0); // pure white
	color = evaluateColor(color);
	color = evaluateImage(color);
	color = evaluateGradient(color);
	color = evalutaBorder(color);
	color = evaluateCorner(color);
	
	gl_FragColor = color;
}

// color shader
vec4 evaluateColor(vec4 color)
{
	return color * color1;
}

// image shader
vec4 evaluateImage(vec4 color)
{
	return color * texture2D(image, uvCoord);
}

// gradient rect
vec4 evaluateGradient(vec4 color)
{
	vec2 origin = gradientVector.xy;
	vec2 direction = gradientVector.zw;
	
	float angle = acos(dot(vec2(0.0, 1.0), direction));
	
	mat2 rotationMatrix = rotateXY(-angle);
	
	vec2 rotatedPos = ((vertexPos - origin) * rotationMatrix);
	
	float checkScale = 1.0 - step(gradientScales.x, 0.0); // checkScale is 0.0 if gradientScales.x is 0.0, otherwise 1.0
	
	float rotatePosFinal = mix(0.0, rotatePos.y, checkScale); // returns 0.0 if checkScale is 0.0
	
	float scale = mix(1.0, gradientScales.x, checkScale); // returns 1.0 if checkScale is 0.0
	
	vec4 mixedColor1 = mix(color1, color2, rotatePosFinal / scale); // returns color1 is checkScale is 0.0
	
	checkScale = 1.0 - step(gradientScales.y, 0.0);
	
	rotatePosFinal = mix(0.0, rotatePos.x, checkScale);
	
	scale = mix(1.0, gradientScales.y, checkScale);
	
	vec4 mixedColor2 = mix(color1, color2, rotatePosFinal / scale);
	
	return color * mixedColor1 * mixedColor2;
}

mat2 rotateXY(float angle)
{
	return mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
}

// border rect
vec4 evalutaBorder(vec4 color)
{
	
}

// rounded corner rect
vec4 evaluateCorner(vec4 color)
{
	
}