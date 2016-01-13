#include "IkaAnimParticleSystem.h"


IkaAnimParticleSystem::IkaAnimParticleSystem(void)
{
}

IkaAnimParticleSystem::IkaAnimParticleSystem(int _maxNum, ofShader* _shader, ofImage* _texture1, int _cols, int _rows)
{
	maxNum = _maxNum;
	shader = _shader;
	texture1 = _texture1;
	cols = _cols;
	rows = _rows;

	for(int i = 0;i < maxNum;i++){
		std::shared_ptr<IkaParticle>  ika(new IkaParticle(ofVec2f(ofRandomWidth(), ofRandomHeight())));
		//ika.setPos(ofRandomWidth(), ofRandomHeight());
		particles.push_back( ika);
	}
}

IkaAnimParticleSystem::~IkaAnimParticleSystem(void)
{
}

void IkaAnimParticleSystem::setup(){
	std::vector<std::shared_ptr<IkaParticle>>::iterator itr;
	
	for(itr = particles.begin(); itr != particles.end(); ++itr)
	{
		(*itr)->setPos(ofRandomWidth(),ofRandomHeight()); // すべてのイカをランダムに配置
		pointSize.push_back((*itr)->getPointSize());
		rotation.push_back((*itr)->getRotation());
		alpha.push_back((*itr)->getAlpha());
		pos.push_back((*itr)->getPos());
		frame.push_back((*itr)->getAnimFrame());
	}

	vbo.setVertexData(&pos.at(0), maxNum, GL_DYNAMIC_DRAW);

	shader->begin();
	int pointAttLoc = shader->getAttributeLocation("pointSize");
	vbo.setAttributeData(pointAttLoc, &pointSize.at(0), 1, maxNum, GL_DYNAMIC_DRAW);

	int rotationLoc = shader->getAttributeLocation("angle");
	vbo.setAttributeData(rotationLoc, &rotation.at(0), 1, maxNum, GL_DYNAMIC_DRAW);

	int alphaLoc = shader->getAttributeLocation("alpha");
	vbo.setAttributeData(alphaLoc, &alpha.at(0), 1, maxNum, GL_DYNAMIC_DRAW);

	int frameLoc = shader->getAttributeLocation("frame");
	vbo.setAttributeData(frameLoc, &frame.at(0), 1, maxNum, GL_DYNAMIC_DRAW);
	shader->end();

}

void IkaAnimParticleSystem::update(){
	//std::vector<std::shared_ptr<Particle>>::iterator itr;
	int c = 0; // イテレータ用カウンタ
	for(auto itr = particles.begin(); itr != particles.end(); ++itr)
	{
		(*itr)->update();
		(*itr)->addForce(VF.getForceFromPos((*itr)->getPos().x, (*itr)->getPos().y));
		pos[c] = (*itr)->getPos();
		alpha[c] = (*itr)->getAlpha();
		rotation[c] = (*itr)->getRotation();
		frame[c] = (*itr)->getAnimFrame();
		c++;
	}
}

void IkaAnimParticleSystem::draw(){

	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	shader->begin();
	shader->setUniformTexture("tex0", texture1->getTextureReference(), 0);
	shader->setUniform1f("cols", cols);
	shader->setUniform1f("rows", rows);


	ofEnablePointSprites();

	vbo.updateVertexData(&pos.at(0), maxNum);

	int rotationLoc = shader->getAttributeLocation("angle");
	vbo.updateAttributeData(rotationLoc, &rotation.at(0), maxNum);

	int alphaLoc = shader->getAttributeLocation("alpha");
	vbo.updateAttributeData(alphaLoc, &alpha.at(0), maxNum);

	int frameLoc = shader->getAttributeLocation("frame");
	vbo.updateAttributeData(frameLoc, &frame.at(0), maxNum);

	vbo.draw( GL_POINTS, 0, maxNum);

	ofDisablePointSprites();

	shader->end();

	ofDisableBlendMode();

}

void IkaAnimParticleSystem::setVectorField(vectorField _vf){
	VF = _vf;
}

void IkaAnimParticleSystem::resetIkaPos(){
	std::vector<std::shared_ptr<Particle>>::iterator itr;
	int c = 0; // イテレータ用カウンタ
	for(auto itr = particles.begin(); itr != particles.end(); ++itr)
	{
		(*itr)->setPos(ofRandomWidth(), ofRandomHeight());
		pos[c] = (*itr)->getPos();
		c++;
	}
}
