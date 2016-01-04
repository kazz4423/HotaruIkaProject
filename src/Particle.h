#pragma once
#include "ofMain.h"
class Particle
{
protected:
	ofVec2f pos, vel, acc; // �ʒu�A���x�A�����x
	float pointSizes, rotations, alphas;  // �摜�T�C�Y�A��]�A�����x�A�̒l
	int uni;
public:
	Particle(void);
	~Particle(void);
	virtual void setup() = 0;
	virtual void update() = 0;
	void setPos(float x, float y);
	ofVec2f getPos();
	float getPointSize();
	float getRotation();
	float getAlpha();
	int getUniNum();

	void addForce(ofVec2f _acc);
	virtual Particle* copy() = 0;

};

