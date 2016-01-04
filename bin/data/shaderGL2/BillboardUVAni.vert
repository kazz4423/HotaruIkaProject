
attribute float		pointSize;
attribute  float	angle;
attribute	 float  alpha;
attribute float frame;
attribute int cols;
attribute int rows;

varying  float		rotAngle;
varying  float    rotAlpha;
varying  float    rotFrame;
void main() {

	rotAngle = angle;
	rotAlpha = alpha;
	rotFrame= frame;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	vec4 eyeCoord  = gl_ModelViewMatrix * gl_Vertex;
	gl_Position    = gl_ProjectionMatrix * eyeCoord;
	float dist     = sqrt(eyeCoord.x*eyeCoord.x + eyeCoord.y*eyeCoord.y + eyeCoord.z*eyeCoord.z);
	float att	   = 600.0 / dist;
	gl_PointSize   = pointSize;
	gl_FrontColor  = gl_Color;


}