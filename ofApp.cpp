#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(200, 7);
	this->mesh = ico_sphere.getMesh();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clearColors();
	this->noise_param = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.035), 0, 1, 0.0005, 0.02);

	ofColor color;
	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		auto noise_value = ofMap(ofNoise(glm::vec4(this->mesh.getVertex(i) * this->noise_param, ofGetFrameNum() * 0.015)), 0, 1, 0, 10);
		int int_noise_value = (int)noise_value;
		
		noise_value = noise_value - int_noise_value;
		auto value = ofMap(abs(noise_value - 0.5), 0, 0.5, 39, 255);
		color = ofColor(value);
		this->mesh.addColor(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->mesh.drawFaces();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}