#pragma once
#include "ParticleSystem.h"
#include "IkaParticle.h"
#include "vectorField.h"

class IkaParticleSystem :
	public ParticleSystem
{
private:
	int gameTime; // game“àŽžŠÔ

	std::vector<float> pointSize;
	std::vector<float> rotation;
	std::vector<float> alpha;
	std::vector<ofVec2f> pos;

	vectorField VF;
	
	ofImage* texture1;
	ofImage* texture2;

public:
	IkaParticleSystem(void);
	IkaParticleSystem(int _maxNum, ofShader* _shader, ofImage* _texture1, ofImage* _texture2);
	~IkaParticleSystem(void);


	void setVectorField(vectorField _vf);
	void setup();
	void update();
	void draw();
};

