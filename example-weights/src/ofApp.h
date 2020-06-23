#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxColorQuantizer.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
	
		void keyPressed(int key);
		void keyReleased(int key);
	
		ofxColorQuantizer colorQuantizer;
        void quantizeImage(string imageName, int numColors);
    
        ofImage image;
        int index = 0;
    
        struct weightedColor {
            ofColor color;
            float weight;
            float distance;
        };
    
        vector< weightedColor > sortedColors;
    
        struct by_distance {
            bool operator()(weightedColor const &a, weightedColor const &b) {
                return a.distance > b.distance;
            }
        };
};

