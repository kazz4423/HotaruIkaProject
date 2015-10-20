#include "Particle.h"


Particle::Particle(void)
{
}


Particle::~Particle(void)
{
}

void Particle::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

ofVec2f Particle::getPos(){
	return pos;
}

float Particle::getPointSize(){
	return pointSizes;
}

float Particle::getRotation(){
	return rotations;
}

float Particle::getAlpha(){
	return alphas;
}