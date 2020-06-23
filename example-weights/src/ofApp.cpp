#include "ofApp.h"
#include "ColorConverter.h"

void ofApp::setup(){
    quantizeImage(ofToString(index) + ".jpg", 10);
}

void ofApp::update(){}

void ofApp::draw(){
	ofBackground(100,100,100);
	
    ofPushMatrix();
    ofTranslate(50,50);
    ofSetColor(255);
	image.draw(0, 0, image.getWidth()/5, image.getHeight()/5);
	
    ofPushMatrix();
    ofTranslate(0, image.getHeight()/5);
    ofDrawBitmapString("hit space to change image", 0, 30);
    ofSetColor(255,100);
    ofDrawBitmapString("colors are weighted based on their areas, their order is based on their chroma values", 0, 50);
    
    ofTranslate(image.getWidth()/5 + 20,0);
    
    for(int i=0; i<colorQuantizer.getNumColors(); i++) {
        ofSetColor(0,50);
        ofDrawRectangle(i*60, 0, 50, -image.getHeight()/5);
        ofSetColor(sortedColors[i].color);
        ofDrawRectangle(i*60, 0, 50, ofMap(sortedColors[i].weight, 0, 1, 0, -image.getHeight()/5));
        ofSetColor(255);
        ofDrawBitmapString(ofToString(int(sortedColors[i].weight * 100)) + "%", i * 60,30);
    }
    
    ofPopMatrix();
    ofPopMatrix();
}

void ofApp::quantizeImage(string imgName, int numColors) {
    image.load(imgName);
    ofImage imageCopy;
    imageCopy.load(imgName);
    imageCopy.resize(imageCopy.getWidth()/2, imageCopy.getHeight()/2);
    
    colorQuantizer.setNumColors(numColors);
    colorQuantizer.quantize(imageCopy.getPixels());
    
    sortedColors.clear();;
    sortedColors.resize(colorQuantizer.getNumColors());
    for(int i = 0; i < colorQuantizer.getNumColors(); i++) {
        ofFloatColor fc = ofFloatColor(colorQuantizer.getColors()[i].r/255.0, colorQuantizer.getColors()[i].g/255.0, colorQuantizer.getColors()[i].b/255.0);
        ofVec3f labCol = ColorConverter::rgbToLab(fc);
        
        sortedColors[i].distance = ColorConverter::calcChroma(labCol);
        sortedColors[i].color = colorQuantizer.getColors()[i];
        sortedColors[i].weight = colorQuantizer.getColorWeights()[i];
    }
    
    std::sort(sortedColors.begin(), sortedColors.end(), by_distance());
}

void ofApp::keyPressed(int key){
    index++;
    if(index>2) index = 0;
    quantizeImage(ofToString(index) + ".jpg", 10);
}
void ofApp::keyReleased(int key){}
