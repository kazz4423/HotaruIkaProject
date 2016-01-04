#pragma once

#include "ofMain.h"
//#include "ofxVectorMath.h"

class vectorField {
	
public:
	
	//---------- �v���p�e�B�[  -------------------------
	
	//�x�N�g����̃O���b�h�̐����w�� (��F60x40)
	int fieldWidth;
	int fieldHeight;
	//�x�N�g���̐� (= fieldWidth x fieldHeight)
	int fieldSize;
	//�x�N�g���ꂪ�`�悳����ʂ̑傫��
	int externalWidth;
	int externalHeight;
	//�x�N�g���̔z��
	vector <ofVec2f> field;
	

	//---------- ���\�b�h  -----------------------------
	
	//�R���X�g���N�^�ƃf�X�g���N�^
	vectorField();
	virtual ~vectorField();
	//�x�N�g����̏�����
	void setupField(int innerW, int innerH, int outerW, int outerH);
	//����
	void clear();
	//���X�Ƀx�N�g����ɌW��͂���܂�悤�ɂ���
	void fadeField(float fadeAmount);
	//�S�Ẵx�N�g���������_���ɐ���
	void randomizeField(float scale);
	//�x�N�g����̗l�q��`��
	void draw();
	//���W���w�肵�āA���̒n�_�ł̃x�N�g���ꂩ��󂯂�͂��Z�o
	ofVec2f	getForceFromPos(float xpos, float ypos);

	//�O�����̗͂������� (���o)
	void addOutwardCircle(float x, float y, float radius, float strength);	
	//�������̗͂������� (�z��)
	void addInwardCircle(float x, float y, float radius, float strength);
	//���v���̉Q����
	void addClockwiseCircle(float x, float y, float radius, float strength);
	//�����v���̉Q��
	void addCounterClockwiseCircle(float x, float y, float radius, float strength);
	//�~�`�̗͂�������
	void addVectorCircle(float x, float y, float vx, float vy, float radius, float strength);
	//�������̗͂�������(������)
	void addInwardCircleKai(float x, float y, float radius, float strength);
	// depth�f�[�^����x�N�g����𐶐�����B512*384����
	void createVectorFieldByDepth(int* buffer,int filter,int power,int powerFilter, float size);
protected:
private:
};