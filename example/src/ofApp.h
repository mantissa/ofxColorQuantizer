#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxColorQuantizer.h"

typedef struct {
//    string name;
    int pos;
    ofColor color;
} colorNameMapping;

class ofApp : public ofBaseApp{

	public:
	
		void setup();
		void update();
		void draw();
	
		void kMeansTest();
		
		void keyPressed(int key);
		void keyReleased(int key);

    void getImagePalette(string path, int num);
    void getImageFromURLPalette(string path, int num);

		ofImage image;
	
		ofxColorQuantizer colorQuantizer;

    void map_setup();
//    map < string, ofColor > colorNameMap;
    map < int, ofColor > colorNameMap;
    vector < colorNameMapping > colorNames;

    vector<ofColor> palette;

    int sortedType;

    void draw_PaleteMINI();
};

