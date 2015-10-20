#include "IkaParticle.h"


IkaParticle::IkaParticle(void)
{
	IkaParticle(ofVec2f(0, 0));
}

IkaParticle::IkaParticle(ofVec2f _pos)
{
	pos = _pos;
	vel.x = 0;
	vel.y = 0;
	acc.x = 0;
	acc.y = 0;
	pointSizes = 64.0f;
	rotations = ofRandom(0, 360);
	alphas = 1.0f;
	uni = (int)ofRandom(0,360);
}

IkaParticle::~IkaParticle(void)
{
}

void IkaParticle::setup()
{

}

void IkaParticle::update()
{
	int count = ofGetFrameNum() + uni;
	if(count % 120 == 0){
		acc.x = ofRandom(-3,3);
		acc.y = ofRandom(-3,3);
	}

	acc -= vel * 0.05;

	vel += acc;

	if (pos.x + vel.x < 0) vel.x *= -1;
	if (pos.y + vel.y < 0) vel.y *= -1;
	if (pos.x + vel.x > ofGetWidth()) vel.x *= -1;
	if (pos.y + vel.y > ofGetHeight()) vel.y *= -1;

	pos += vel;
	acc = ofVec2f(0,0);

	// Œõ‚Ì–¾–Å
	float a = min(0.5f + (float)sin( ofDegToRad(count % 360)), 1.0f);
	alphas = a;
}

Particle* IkaParticle::copy(){
	IkaParticle cloneIka(ofVec2f(0,0));
	return &cloneIka;
}