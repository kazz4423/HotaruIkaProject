#include "IkaParticleSystem.h"


IkaParticleSystem::IkaParticleSystem(void)
{
}

IkaParticleSystem::IkaParticleSystem(int _maxNum, ofShader* _shader, ofImage* _texture1, ofImage* _texture2)
{
	maxNum = _maxNum;
	shader = _shader;
	texture1 = _texture1;
	texture2 = _texture2;

	for(int i = 0;i < maxNum;i++){
		std::shared_ptr<IkaParticle>  ika(new IkaParticle(ofVec2f(ofRandomWidth(), ofRandomHeight())));
		//ika.setPos(ofRandomWidth(), ofRandomHeight());
		particles.push_back( ika);
	}
}

IkaParticleSystem::~IkaParticleSystem(void)
{
	//delete texture1;
	//delete texture2;
}

void IkaParticleSystem::setup(){
	std::vector<std::shared_ptr<Particle>>::iterator itr;
	
	for(auto itr = particles.begin(); itr != particles.end(); ++itr)
	{
		(*itr)->setPos(ofRandomWidth(),ofRandomHeight()); // すべてのイカをランダムに配置
		pointSize.push_back((*itr)->getPointSize());
		rotation.push_back((*itr)->getRotation());
		alpha.push_back((*itr)->getAlpha());
		pos.push_back((*itr)->getPos());
	}

	vbo.setVertexData(&pos.at(0), maxNum, GL_DYNAMIC_DRAW);

	shader->begin();
	int pointAttLoc = shader->getAttributeLocation("pointSize");
	vbo.setAttributeData(pointAttLoc, &pointSize.at(0), 1, maxNum, GL_DYNAMIC_DRAW);

	int rotationLoc = shader->getAttributeLocation("angle");
	vbo.setAttributeData(rotationLoc, &rotation.at(0), 1, maxNum, GL_DYNAMIC_DRAW);

	int alphaLoc = shader->getAttributeLocation("alpha");
	vbo.setAttributeData(alphaLoc, &alpha.at(0), 1, maxNum, GL_DYNAMIC_DRAW);

	shader->end();

}

void IkaParticleSystem::update(){
	std::vector<std::shared_ptr<Particle>>::iterator itr;
	int c = 0; // イテレータ用カウンタ
	for(auto itr = particles.begin(); itr != particles.end(); ++itr)
	{
		(*itr)->update();
		(*itr)->addForce(VF.getForceFromPos((*itr)->getPos().x, (*itr)->getPos().y));
		pos[c] = (*itr)->getPos();
		alpha[c] = (*itr)->getAlpha();
		rotation[c] = (*itr)->getRotation();
		c++;
	}
}

void IkaParticleSystem::draw(){

	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	shader->begin();
	shader->setUniformTexture("tex0", texture1->getTextureReference(), 0);
	shader->setUniformTexture("tex1", texture2->getTextureReference(), 1);

	ofEnablePointSprites();

	vbo.updateVertexData(&pos.at(0), maxNum);

	int rotationLoc = shader->getAttributeLocation("angle");
	vbo.updateAttributeData(rotationLoc, &rotation.at(0), maxNum);

	int alphaLoc = shader->getAttributeLocation("alpha");
	vbo.updateAttributeData(alphaLoc, &alpha.at(0), maxNum);

	vbo.draw( GL_POINTS, 0, maxNum);

	ofDisablePointSprites();

	shader->end();

	ofDisableBlendMode();

}

void IkaParticleSystem::setVectorField(vectorField _vf){
	VF = _vf;
}
