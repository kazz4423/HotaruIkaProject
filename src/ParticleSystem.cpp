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
		// 指定した値が最大値より小さい場合は個数分削除
		for(int i=0; i<= maxNum - num; i++)
		{
			particles.pop_back();
		}
	}
	else
	{
		// 指定した値が最大値より大きい場合は個数分追加
		for(int i=0; i<= num - maxNum; i++){
			//particles.push_back( particles[0]->copy()); // 追加するときは最初の要素のパーティクルからコピーする
			//particles[particles.size()]->setPos(ofRandomWidth(), ofRandomHeight()); // 追加位置はランダム
		}
	}

}