#include "ofApp.h"

float complexity = 12; // wind complexity
float pollenMass = .8; // pollen mass
float timeSpeed = .02; // wind variation speed
float phase = TWO_PI; // separate u-noise from v-noise
float windSpeed = 3; // wind vector magnitude for debug



ofVec2f ofApp::getField(ofVec2f position) {
	float normx = ofNormalize(position.x, 0, ofGetWidth());
	float normy = ofNormalize(position.y, 0, ofGetHeight());
	float u = ofNoise(t + phase, normx * complexity + phase, normy * complexity + phase);
	float v = ofNoise(t - phase, normx * complexity - phase, normy * complexity + phase);
	return ofVec2f(u, v);
}
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackgroundGradient(ofColor(100), ofColor(255));

	for (int i = 0; i < NUM_BILLBOARDS; i++){
		pos[i].x = ofRandomWidth();
		pos[i].y = ofRandomHeight();
		vel[i].x = 0; //ofRandomf();
		vel[i].y = 0; //ofRandomf();
		acc[i].x = 0;
		acc[i].y = 0;
 		pointSizes[i] = 64.0f;
		rotations[i] = ofRandom(0, 360);
		alphas[i] = 1.0f;
		def[i] = (int)ofRandom(0, 360);

	}

	// set the vertex data
	//vbo.setVertexData(pos, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
	if (ofGetGLProgrammableRenderer()){
		shader.load("shaderGL3/Billboard");
	}
	else{
		shader.load("shaderGL2/Billboard");
	}

	ofDisableArbTex();

	imgResource.setResource("Ika1","img/ika1.png");
	imgResource.setResource("Ika1_back", "img/ikal1.png");
	imgResource.setResource("BlueLight", "img/blueLight.png");

	//Ika.loadImage("img/ika1.png");
	//Light.loadImage("img/ikal1.png");

	ikaParticleSystem = new IkaParticleSystem(NUM_BILLBOARDS, &shader, imgResource.getResourcePtr("Ika1"), imgResource.getResourcePtr("Ika1_back")); // new

	/*
	shader.begin();
	int pointAttLoc = shader.getAttributeLocation("pointSize");
	vbo.setAttributeData(pointAttLoc, pointSizes, 1, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);

	int angleLoc = shader.getAttributeLocation("angle");
	vbo.setAttributeData(angleLoc, rotations, 1, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);

	int alphaLoc = shader.getAttributeLocation("alpha");
	vbo.setAttributeData(alphaLoc, alphas, 1, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);

	int tex0 = glGetUniformLocation(shader.getProgram(),"tex1");
	*/

	ikaParticleSystem->setup();

}

//--------------------------------------------------------------
void ofApp::update(){

	ikaParticleSystem->update();

	/*
	t = ofGetFrameNum() * timeSpeed;
	ofVec2f mousePos;
	mousePos.x = ofGetMouseX();
	mousePos.y = ofGetMouseY();

	for (int i = 0; i < NUM_BILLBOARDS; i++){
		int count = ofGetFrameNum() + def[i];
		if (count % 120 == 0){
			acc[i].x = ofRandom(-3, 3);
			acc[i].y = ofRandom(-3, 3);
		}

		ofVec2f field = getField(pos[i]);
		float speed = (1 + ofNoise(t, field.x, field.y)) / pollenMass;
		acc[i] += ofVec2f(ofLerp(-speed, speed, field.x), ofLerp(-speed, speed, field.y))*0.03f;

		if (pos[i].distance(mousePos) <= 200){
			ofVec2f direction = pos[i] - mousePos;
			direction /= pos[i].distance(mousePos);
			if (flag) direction = -direction;
			acc[i] += (200 - pos[i].distance(mousePos)) * direction * 0.005f;
		}

		acc[i] -= vel[i] * 0.05;

		vel[i] += acc[i];

		if (pos[i].x + vel[i].x < 0) vel[i].x *= -1;
		if (pos[i].y + vel[i].y < 0) vel[i].y *= -1;
		if (pos[i].x + vel[i].x > ofGetWidth()) vel[i].x *= -1;
		if (pos[i].y + vel[i].y > ofGetHeight()) vel[i].y *= -1;
		
		
		pos[i] += vel[i];

		acc[i] = ofVec2f(0, 0);
		/*
		if (pos[i].x < 0-100) pos[i].x = ofGetWidth()+100;
		if (pos[i].x > ofGetWidth()+100) pos[i].x = 0-100;
		if (pos[i].y < 0-100) pos[i].y = ofGetHeight() + 100;
		if (pos[i].y > ofGetHeight()+100) pos[i].y = 0 - 100;
		
		float a = min(0.5f+(float)sin( ofDegToRad(count % 360)),1.0f);
		alphas[i] = a;
		

	}
	*/
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(0, 32, 70), ofColor(0,64,135));
	
	/*
	ofEnableBlendMode(OF_BLENDMODE_ADD); // ‰ÁŽZ‡¬‚É•ÏX
	shader.begin();

	shader.setUniformTexture("tex0",Ika.getTextureReference(),0);
	shader.setUniformTexture("tex1",Light.getTextureReference(),1);

	ofEnablePointSprites();
	
	//Ika.getTextureReference().bind();
	vbo.updateVertexData(pos, NUM_BILLBOARDS);

	int angleLoc = shader.getAttributeLocation("angle");
	vbo.updateAttributeData(angleLoc, rotations, NUM_BILLBOARDS);

	int alphaLoc = shader.getAttributeLocation("alpha");
	vbo.updateAttributeData(alphaLoc, alphas, NUM_BILLBOARDS);

	vbo.draw(GL_POINTS, 0, NUM_BILLBOARDS);

	//Ika.getTextureReference().unbind();
	ofDisablePointSprites();

	shader.end();
	ofDisableBlendMode();
	
	ofDrawBitmapStringHighlight("  FPS: " + ofToString(ofGetFrameRate()), 30, 20);
	ofDrawBitmapStringHighlight("  ALPHA: " + ofToString(max((float)sin(ofDegToRad(ofGetFrameNum() % 360)),0.0f)), 30, 40);

	ofImage* img = imgResource.getResourcePtr("Ika1");
	img->draw(20,20);
	*/

	ikaParticleSystem->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'f'){
		ofToggleFullscreen();
	}
	if (key == 'r'){
		for (int i = 0; i < NUM_BILLBOARDS; i++){
			pos[i].x = ofRandomWidth();
			pos[i].y = ofRandomHeight();
			vel[i].x = 0; //ofRandomf();
			vel[i].y = 0; //ofRandomf();
			acc[i].x = 0;
			acc[i].y = 0;
 			pointSizes[i] = 25.0f;
			rotations[i] = ofRandom(0, 360);
			alphas[i] = 1.0f;
			def[i] = (int)ofRandom(0, 360);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	flag = true;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	flag = false;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

ofApp::~ofApp(){
	delete ikaParticleSystem;
}