#pragma once
#include "Particle.h"
class IkaParticle :
	public Particle
{
private:
	int frame;
public:
	IkaParticle(void);
	IkaParticle(ofVec2f _pos);
	~IkaParticle(void);
	void setup();
	void update();
	Particle* copy();

	int getAnimFrame();
};

