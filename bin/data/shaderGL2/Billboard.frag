
uniform sampler2D	tex0;
uniform sampler2D	tex1;
varying  float		rotAngle;
varying	 float		rotAlpha;

void main (void) {

	float angle		= rotAngle;
	vec2 offset		= vec2(.5, .5);
	vec2 v2 = gl_TexCoord[0].st;

	// not sure this is right
	// I just search on how to rotate
	// a texture...
	float cosX, sinX;
	float cosY, sinY;
	sinX = sin(angle);
	cosX = cos(angle);
	sinY = sin(angle);
	cosY = cos(angle);

	mat2 rotationMatrix = mat2( cosX, -sinX,
							    sinY, cosX);

	vec2 newcoords = ((v2-offset) * (rotationMatrix));
	newcoords += offset;
	
	vec4 tex0c = texture2D(tex0, newcoords);
	vec4 tex1c = texture2D(tex1, newcoords);
	if(tex0c.r == 0 && tex0c.g == 0 && tex0c.b == 0){
		tex0c.a = rotAlpha;
	}
	tex1c = tex0c.a * tex0c + (1-tex0c.a)* tex1c;

	//gl_FragColor = (texture2D(tex0, newcoords) + tex1c) * gl_Color;
	gl_FragColor = tex1c * gl_Color;
	//gl_FragColor.a = rotAlpha;
}
