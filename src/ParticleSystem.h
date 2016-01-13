#pragma once
#include "ofMain.h"
#include <memory>
#include "ofVbo.h"
#include "Particle.h"
class ParticleSystem
{
protected:
	ofShader* shader;
	ofVbo vbo;
	int maxNum;
	std::vector<std::shared_ptr<Particle>> particles;
public:
	ParticleSystem(void);
	~ParticleSystem(void);

	virtual void setup() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	void changeParticleNum(int num); // Ç‹Çæégópã÷é~ÅI
};

