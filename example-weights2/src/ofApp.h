#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxColorQuantizer.h"
#include "ofxGui.h"

typedef struct {
    int pos;
    ofColor color;
} colorMapping;

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
    ofImage imageCopy;

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

    void build();

    //-

    void buildFromImageFile(string path, int num);
    void buildFromImageUrl(string rul, int num);

    void map_setup();
    map < int, ofColor > colorMap;
    vector < colorMapping > colorNames;

    ofxPanel gui;
    ofParameter<int> sortedType;
    ofParameter<int> numColors;
    ofParameter<string> labelStr;
    ofParameter<bool> bReBuild;
    ofParameterGroup parameters;
    void Changed_parameters(ofAbstractParameter &e);

    vector<ofColor> palette;

    void draw_Palette_Preview();

    int boxSize;
    int boxPad;
    int boxW;
    int wPal;

    void kMeansTest();

    string imageName;

};

