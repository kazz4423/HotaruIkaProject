#include "vectorField.h"

//�R���X�g���N�^
vectorField::vectorField(){
    
}

//�x�N�g����̏�����
void vectorField::setupField(int innerW, int innerH, int outerW, int outerH){
	
	fieldWidth			= innerW;
	fieldHeight			= innerH;
	externalWidth		= outerW;
	externalHeight		= outerH;
	
	field.clear();
	 
	fieldSize = fieldWidth * fieldHeight;
	for (int i = 0; i < fieldSize; i++){
		ofVec2f pt;
		pt.set(0,0);
		field.push_back(pt);
	}
}

//����
void vectorField::clear(){
    for (int i = 0; i < fieldSize; i++){
        field[i].set(0,0);
    }
}

//���X�ɗ͂���܂�悤�ɂ���
void vectorField::fadeField(float fadeAmount){
	for (int i = 0; i < fieldSize; i++){
        field[i].set(field[i].x*fadeAmount,field[i].y*fadeAmount);
    }
}

//�S�Ẵx�N�g���������_���ɐ���
void vectorField::randomizeField(float scale){
	for (int i = 0; i < fieldSize; i++){
        // random between -1 and 1
        float x = (float)(ofRandom(-1,1)) * scale;
        float y = (float)(ofRandom(-1,1)) * scale;
        field[i].set(x,y);
    }
}

//�x�N�g����̗l�q��`��
void vectorField::draw(){
	
    float scalex = (float)externalWidth / (float)fieldWidth;
    float scaley = (float)externalHeight / (float)fieldHeight;
	
    for (int i = 0; i < fieldWidth; i++){
        for (int j = 0; j < fieldHeight; j++){
            int pos = j * fieldWidth + i;
            
            float px = 	i * scalex;
            float py = 	j * scaley;
            float px2 = px + field[pos].x * 5;
            float py2 = py + field[pos].y * 5;
			
            ofLine(px,py, px2, py2);
			
			ofVec2f line;
			line.set(px2-px, py2-py);
			float length = line.length();
			line.normalize();
			line.rotate(90);
			ofLine(px - line.x*length*0.2, py - line.y*length*0.2, px + line.x*length*0.2, py + line.y*length*0.2);
        }
    }
}

//���W���w�肵�āA���̒n�_�ł̃x�N�g���ꂩ��󂯂�͂��Z�o
ofVec2f vectorField::getForceFromPos(float xpos, float ypos){
	
	ofVec2f frc;
	frc.set(0,0);
	
	float xPct = xpos / (float)externalWidth;
	float yPct = ypos / (float)externalHeight;
	
	if ((xPct < 0 || xPct > 1) || (yPct < 0 || yPct > 1)){
		return frc;
	}
	
    int fieldPosX = (int)(xPct * fieldWidth);
    int fieldPosY = (int)(yPct * fieldHeight);
    
    fieldPosX = MAX(0, MIN(fieldPosX, fieldWidth-1));
    fieldPosY = MAX(0, MIN(fieldPosY, fieldHeight-1));
    
    int pos = fieldPosY * fieldWidth + fieldPosX;
	
	frc.set(field[pos].x * 0.1, field[pos].y * 0.1 );
	return frc;
}

//�������̗͂������� (�z��)
void vectorField::addInwardCircle(float x, float y, float radius, float strength){
	float pctx			= x / (float)externalWidth;
	float pcty			= y / (float)externalHeight;
	float radiusPct		= radius / (float)externalWidth;
    
    int fieldPosX		= (int)(pctx * (float)fieldWidth);
    int fieldPosY		= (int)(pcty * (float)fieldHeight);
	float fieldRadius	= (float)(radiusPct * fieldWidth);
	
	int startx	= MAX(fieldPosX - fieldRadius, 0);
	int starty	= MAX(fieldPosY - fieldRadius, 0);
	int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
	int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
	
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
			
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
			if (distance < 0.0001) distance = 0.0001;
			
			if (distance < fieldRadius){
				
				float pct = 1.0f - (distance / fieldRadius);
				
                float strongness = strength * pct;
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                field[pos].x += unit_px * strongness;
                field[pos].y += unit_py * strongness;
            }
        }
    }
}

//�O�����̗͂������� (���o)
void vectorField::addOutwardCircle(float x, float y, float radius, float strength){
	
	float pctx			= x / (float)externalWidth;
	float pcty			= y / (float)externalHeight;
	float radiusPct		= radius / (float)externalWidth;
	
    int fieldPosX		= (int)(pctx * (float)fieldWidth);
    int fieldPosY		= (int)(pcty * (float)fieldHeight);
	float fieldRadius	= (float)(radiusPct * fieldWidth);
	
	int startx	= MAX(fieldPosX - fieldRadius, 0);
	int starty	= MAX(fieldPosY - fieldRadius, 0);
	int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
	int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
	
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
            
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
			if (distance < 0.0001) distance = 0.0001;
			
			if (distance < fieldRadius){
                
				float pct = 1.0f - (distance / fieldRadius);
                float strongness = strength * pct;
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                field[pos].x -= unit_px * strongness;
                field[pos].y -= unit_py * strongness;
            }
        }
    }
}

//���v���̉Q����
void vectorField::addClockwiseCircle(float x, float y, float radius, float strength){
	
	float pctx			= x / (float)externalWidth;
	float pcty			= y / (float)externalHeight;
	float radiusPct		= radius / (float)externalWidth;
	
	// then, use them here:
    int fieldPosX		= (int)(pctx * (float)fieldWidth);
    int fieldPosY		= (int)(pcty * (float)fieldHeight);
	float fieldRadius	= (float)(radiusPct * fieldWidth);
	
	int startx	= MAX(fieldPosX - fieldRadius, 0);
	int starty	= MAX(fieldPosY - fieldRadius, 0);
	int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
	int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
	
	
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
			
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
			if (distance < 0.0001) distance = 0.0001;
			
			if (distance < fieldRadius){
				
				float pct = 1.0f - (distance / fieldRadius);
				
                float strongness = strength * pct;
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                field[pos].x += unit_py * strongness;
                field[pos].y -= unit_px * strongness;
            }
        }
    }
}

//�����v���̉Q����
void vectorField::addCounterClockwiseCircle(float x, float y, float radius, float strength){
    
	float pctx			= x / (float)externalWidth;
	float pcty			= y / (float)externalHeight;
	float radiusPct		= radius / (float)externalWidth;
	
    int fieldPosX		= (int)(pctx * (float)fieldWidth);
    int fieldPosY		= (int)(pcty * (float)fieldHeight);
	float fieldRadius	= (float)(radiusPct * fieldWidth);
	
	int startx	= MAX(fieldPosX - fieldRadius, 0);
	int starty	= MAX(fieldPosY - fieldRadius, 0);
	int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
	int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
	
	
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
			
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
			if (distance < 0.0001) distance = 0.0001;
			
			if (distance < fieldRadius){
				
				float pct = 1.0f - (distance / fieldRadius);
				
                float strongness = strength * pct;
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                field[pos].x -= unit_py * strongness;
                field[pos].y += unit_px * strongness;
            }
        }
    }
}

//�~�`�̗͂�������
void vectorField::addVectorCircle(float x, float y, float vx, float vy, float radius, float strength){
	
	float pctx			= x / (float)externalWidth;
	float pcty			= y / (float)externalHeight;
	float radiusPct		= radius / (float)externalWidth;
	
    int fieldPosX		= (int)(pctx * (float)fieldWidth);
    int fieldPosY		= (int)(pcty * (float)fieldHeight);
	float fieldRadius	= (float)(radiusPct * fieldWidth);
	
	int startx	= MAX(fieldPosX - fieldRadius, 0);
	int starty	= MAX(fieldPosY - fieldRadius, 0);
	int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
	int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
	
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
			
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
			if (distance < 0.0001) distance = 0.0001;
			
			if (distance < fieldRadius){
				
				float pct = 1.0f - (distance / fieldRadius);
                float strongness = strength * pct;
                field[pos].x += vx * strongness;
                field[pos].y += vy * strongness;
            }
        }
    }
}

void vectorField::addInwardCircleKai(float x, float y, float radius, float strength){
	float pctx			= x / (float)externalWidth;
	float pcty			= y / (float)externalHeight;
	float radiusPct		= radius / (float)externalWidth;
    
    int fieldPosX		= (int)(pctx * (float)fieldWidth);
    int fieldPosY		= (int)(pcty * (float)fieldHeight);
	float fieldRadius	= (float)(radiusPct * fieldWidth);
	
	int startx	= MAX(fieldPosX - fieldRadius, 0);
	int starty	= MAX(fieldPosY - fieldRadius, 0);
	int endx	= MIN(fieldPosX + fieldRadius, fieldWidth);
	int endy	= MIN(fieldPosY + fieldRadius, fieldHeight);
	
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
			
            int pos = j * fieldWidth + i;
            float distance = (float)sqrt((fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
			if (distance < 0.0001) distance = 0.0001;
			
			if (distance < fieldRadius && distance > fieldRadius -10){
				
				float pct = 1.0f + (fieldRadius/ distance);
				
                float strongness = strength *pct;
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                field[pos].x += unit_px *strongness;
                field[pos].y += unit_py * strongness;
            }
        }
    }
}

// depth�f�[�^����x�N�g����𐶐�����BDepth 512*384 ���� ������128*87�����łȂ��Ǝg���Ȃ�
void vectorField::createVectorFieldByDepth(int* buffer,int filter,int power,int powerFilter, float size){
	if(buffer != NULL){
		ofVec2f* tmpField = new ofVec2f[128*87]; //�Վ����I�z��

		for(int y = 0; y < 87; y++){
			for(int x = 0; x < 128; x++){
				float powerX, powerY;
				powerX = 0;
				powerY = 0;
				// ��̐���
				int depthStd = (buffer[(y*128*16)+((1*128+x)*4)+1]+buffer[(y*128*16)+((1*128+x)*4)-1]+
					buffer[(y*128*16)+((-1*128+x)*4)+1]+buffer[(y*128*16)+((-1*128+x)*4)-1])/4; 

				if( 100 < depthStd &&  depthStd < filter){ // ���鋫�E
					for(int j=0;j<4;j++){
						for(int i=0;i<4;i++){
							int depth = buffer[(y*128*16)+((j*128+x)*4)+i];
							if(depth == 0){
								continue;
							}
							depth -= depthStd;
							// ������ �d�݂�
							switch (i)
							{
							case 0:
								powerX += depth * -2;
								break;
							case 1:
								powerX += depth * -1;
								break;
							case 2:
								powerX += depth * 1;
								break;
							case 3:
								powerX += depth * 2;
								break;
							default:
								break;
							}

							switch (j)
							{
							case 0:
								powerY += depth * -2;
								break;
							case 1:
								powerY += depth * -1;
								break;
							case 2:
								powerY += depth * 1;
								break;
							case 3:
								powerY += depth * 2;
								break;
							default:
								break;
							}
						}	
					}
				}

				// ���ς��Ƃ�
				powerX = powerX/16; 
				powerY = powerY/16;

				// ���ʂɑ傫�ȗ͂͏��O
				if( abs( powerX) > powerFilter  || abs(powerY) > powerFilter){
					powerX = 0;
					powerY = 0;
				}

				tmpField[y*128+x].x = powerX/power;
				tmpField[y*128+x].y = powerY/power;
			}
		}
		 // �C�ӊg�又��
		int offsetX = 128/2 * (1 - size);
		int offsetY = 87/2 * (1 - size);

		for(int y = 0; y < 87; y++){
			for(int x = 0; x < 128; x++){

				int sx = x*size; 
				int sy = y*size;
				field[y*128+x] = tmpField[(sy+offsetY)*128+sx+offsetX] ;
			}
		}


		delete[] tmpField;
	}
}

//�f�X�g���N�^
vectorField::~vectorField(){
    
}
