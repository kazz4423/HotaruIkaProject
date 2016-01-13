#pragma once
#include "particlesystem.h"
#include "IkaParticle.h"
#include "vectorField.h"
class IkaAnimParticleSystem :
	public ParticleSystem
{
	private:
	int gameTime; // game“àŽžŠÔ

	std::vector<float> pointSize;
	std::vector<float> rotation;
	std::vector<float> alpha;
	std::vector<float> frame;
	std::vector<ofVec2f> pos;

	int cols, rows;

	vectorField VF;
	
	ofImage* texture1;
	std::vector<std::shared_ptr<IkaParticle>> particles;
public:
	IkaAnimParticleSystem(void);
	IkaAnimParticleSystem(int _maxNum, ofShader* _shader, ofImage* _texture1, int _cols, int _lows);
	~IkaAnimParticleSystem(void);

	void setVectorField(vectorField _vf);
	void resetIkaPos();
	void setup();
	void update();
	void draw();
};

