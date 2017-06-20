#include "ofApp.h"

void ofApp::setup(){
	image.load("carcio.jpg");
	ofImage imageCopy;
	imageCopy.load("carcio.jpg");
	imageCopy.resize(imageCopy.getWidth()/2, imageCopy.getHeight()/2);
	
	// get our colors
	colorQuantizer.setNumColors(6);
	colorQuantizer.quantize(imageCopy.getPixels());
	
	// resize the window to match the image
	ofSetWindowShape(image.getWidth(), image.getHeight());
}

void ofApp::update(){}

void ofApp::draw(){
	ofBackground(100,100,100);
	
    ofPushMatrix();
    ofTranslate(50,50);
    ofSetColor(255);
	image.draw(0, 0, image.getWidth()/5, image.getHeight()/5);
	
    ofPushMatrix();
    ofTranslate(image.getWidth()/5 + 20, image.getHeight()/5);
    for(int i=0; i<colorQuantizer.getNumColors(); i++) {
        ofSetColor(0,50);
        ofDrawRectangle(i*60, 0, 50, -image.getHeight()/5);
        ofSetColor(colorQuantizer.getColors()[i]);
        ofDrawRectangle(i*60, 0, 50, ofMap(colorQuantizer.getColorWeights()[i], 0, 1, 0, -image.getHeight()/5));
        ofSetColor(255);
        ofDrawBitmapString(ofToString(int(colorQuantizer.getColorWeights()[i]*100)) + "%", i * 60,30);
    }
    ofPopMatrix();
    ofPopMatrix();
    
}

void ofApp::kMeansTest(){
	cv::Mat samples = (cv::Mat_<float>(8, 1) << 31 , 2 , 10 , 11 , 25 , 27, 2, 1);
	cv::Mat labels;
	
	// double kmeans(const Mat& samples, int clusterCount, Mat& labels,
	cv::TermCriteria termcrit;
	int attempts, flags;
	cv::Mat centers;
	double compactness = cv::kmeans(samples, 3, labels, cv::TermCriteria(), 2, cv::KMEANS_PP_CENTERS, centers);
	
	cout<<"labels:"<<endl;
	for(int i = 0; i < labels.rows; ++i)
	{ 
		cout<<labels.at<int>(0, i)<<endl;
	}
	
	cout<<"\ncenters:"<<endl;
	for(int i = 0; i < centers.rows; ++i)
	{
		cout<<centers.at<float>(0, i)<<endl;
	}
	
	cout<<"\ncompactness: "<<compactness<<endl;
}

void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key){}
