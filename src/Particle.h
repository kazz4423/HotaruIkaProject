#pragma once
#include "ofMain.h"
class Particle
{
protected:
	ofVec2f pos, vel, acc; // 位置、速度、加速度
	float pointSizes, rotations, alphas;  // 画像サイズ、回転、透明度、個体値
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

