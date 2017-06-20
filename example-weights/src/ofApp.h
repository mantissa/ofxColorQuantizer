#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxColorQuantizer.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
	
		void kMeansTest();
		
		void keyPressed(int key);
		void keyReleased(int key);
	
		ofImage image;
		ofxColorQuantizer colorQuantizer;
};

