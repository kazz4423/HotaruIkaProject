#version 150

uniform mat4 orientationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in float		pointSize;
in float		angle;
in float		alpha;

in vec4  position;

out float rotAngle;
out float rotAlpha;
void main() {

	rotAngle = angle;
	rotAlpha = alpha;

	vec4 eyeCoord  = modelViewMatrix * position;
	gl_Position    = modelViewProjectionMatrix * position;
	float dist     = sqrt(eyeCoord.x*eyeCoord.x + eyeCoord.y*eyeCoord.y + eyeCoord.z*eyeCoord.z);
	float att	   = 600.0 / dist;
	gl_PointSize   = pointSize;


}
