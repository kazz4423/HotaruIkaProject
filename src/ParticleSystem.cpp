#include "ParticleSystem.h"


ParticleSystem::ParticleSystem(void)
{
}


ParticleSystem::~ParticleSystem(void)
{
	//delete shader;
}

void ParticleSystem::changeParticleNum(int num)
{
	if(num <= 0 || num == maxNum)return;

	if(num < maxNum)
	{
		// �w�肵���l���ő�l��菬�����ꍇ�͌����폜
		for(int i=0; i<= maxNum - num; i++)
		{
			particles.pop_back();
		}
	}
	else
	{
		// �w�肵���l���ő�l���傫���ꍇ�͌����ǉ�
		for(int i=0; i<= num - maxNum; i++){
			//particles.push_back( particles[0]->copy()); // �ǉ�����Ƃ��͍ŏ��̗v�f�̃p�[�e�B�N������R�s�[����
			//particles[particles.size()]->setPos(ofRandomWidth(), ofRandomHeight()); // �ǉ��ʒu�̓����_��
		}
	}

}