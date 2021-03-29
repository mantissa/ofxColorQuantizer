#include "ofApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	// load our image
	image.loadImage("photo.jpg");
	
	// for speedz sake, quantize a smaller copy of the image
	ofImage imageCopy;
	imageCopy.loadImage("photo.jpg");
	imageCopy.resize(imageCopy.getWidth()/2, imageCopy.getHeight()/2);
	
	// get our colors
	colorQuantizer.setNumColors(24);
	colorQuantizer.quantize(imageCopy.getPixelsRef());
	
	// resize the window to match the image
	ofSetWindowShape(image.getWidth(), image.getHeight());
}

//--------------------------------------------------------------
void testApp::update(){
	

}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(100,100,100);

	ofSetColor(255);

	image.draw(0, 0);
	
	colorQuantizer.draw(ofPoint(0, image.getHeight()-20));	
}

//--------------------------------------------------------------
void testApp::kMeansTest(){

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

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}
