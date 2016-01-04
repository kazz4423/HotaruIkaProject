
uniform sampler2D	tex0;

uniform int cols;
uniform int rows;
varying float rotFrame;

varying  float		rotAngle;
varying	 float		rotAlpha;

void main (void) {
	float angle		= rotAngle;
	vec2 v2 = gl_TexCoord[0].st;
	
	float cosX, sinX;
	float cosY, sinY;
	sinX = sin(angle);
	cosX = cos(angle);
	sinY = sin(angle);
	cosY = cos(angle);
	
	mat2 rotationMatrix = mat2( cosX, -sinX,
							    sinY, cosX);

	// UV Animetions setting
	float stepx = 1.0/4.0;
	float stepy = 1.0/4.0;
	vec2 offset = vec2(.0,.0);
	
	offset.x += stepx * 2 * mod(int(1),3);
	offset.y += stepy * 2 * int(1/3);
	
	float resize = 1.0/3.0;
	
	mat2 resizeMatrix = mat2(resize, 0,
							0, resize);
							
	vec2 newcoords = v2 * resizeMatrix;
	newcoords = (newcoords - offset); // * (rotationMatrix));
	//newcoords += offset*4;
	
	
	gl_FragColor = texture2D(tex0, newcoords);
}
