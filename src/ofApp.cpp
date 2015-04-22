#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ondaDump.setup(ofGetWidth(), ofGetHeight(), ofGetHeight() / 2, 40, 40);
	setupGui();
}

void ofApp::setupGui()
{
	paramReset.addListener(this, &ofApp::resetPressed);

	gui.setup("params");
    gui.add(paramReset.setup("reset",false));
	gui.add(ondaDump.paramSpring.setup("spring", 0.1, 0.01, 2));
    gui.add(ondaDump.paramAttractionForce.setup("attractionForce", 0.1, 0.01, 10));

}

void ofApp::resetPressed()
{
	ondaDump.setup(ofGetWidth(), ofGetHeight(), ofGetHeight() / 2, 40, 40);
}

//--------------------------------------------------------------
void ofApp::update(){
	ondaDump.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0,0,0);
	ofSetColor(255,255,255);
	gui.draw();
	ondaDump.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	ondaDump.addForce(ofPoint(x,y),ofVec2f(0,10));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	ondaDump.addForce(ofPoint(x,y),ofVec2f(0,10));

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
