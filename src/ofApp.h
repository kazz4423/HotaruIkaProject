#pragma once

#include "ofMain.h"
#include "ofVbo.h"
#include "ImageResource.h"
#include "ShaderResource.h"
#include "IkaParticleSystem.h"
#include "IkaAnimParticleSystem.h"
#include "vectorField.h"
#include "kinectSDK4Ofx.h"
#include "ofxGui.h"

#define NUM_BILLBOARDS 100

class ofApp : public ofBaseApp{

	public:
		~ofApp();
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofVec2f getField(ofVec2f position);
	
	private:
		ofImage Ika;
		ofImage Light;

		ImageResource imgResource;

		//ShaderResource shaderResource;

		IkaParticleSystem* ikaParticleSystem;
		IkaAnimParticleSystem* ikaAnimParticleSystem;

		kinectSDK4Ofx kinect;
		vectorField VF;
		ofVbo vbo;
		ofShader shader, animShader;

		ofVec2f pos[NUM_BILLBOARDS]; // �ʒu�x�N�g��
		ofVec2f vel[NUM_BILLBOARDS]; // ���x�x�N�g��
		ofVec2f acc[NUM_BILLBOARDS]; // �����x�x�N�g��
		float pointSizes[NUM_BILLBOARDS];
		float rotations[NUM_BILLBOARDS];
		float alphas[NUM_BILLBOARDS];
		int def[NUM_BILLBOARDS];

		float t;
		bool flag;

		// GUI
		ofxPanel gui;
		ofxIntSlider power;
		ofxIntSlider range;
		ofxIntSlider maxRange;
		ofxToggle button;
		ofxLabel fps;
		ofxFloatSlider scale;
};
