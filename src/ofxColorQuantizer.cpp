
#include "ofxColorQuantizer.h"

ofxColorQuantizer::ofxColorQuantizer(){
	
	// set default # of colors
	numColors = 12;
}

vector<ofColor> & ofxColorQuantizer::quantize(ofPixels inputImage){
	
	const int colorCount = numColors;
	const int sampleCount = inputImage.getHeight() * inputImage.getWidth();
	cv::Mat colorSamples( sampleCount, 1, CV_32FC3 );
	
	// get our pixels
	unsigned char * pixels = inputImage.getPixels();
	
	// clear our list of colors
	colors.clear();
	
	// build our matrix of samples
	cv::MatIterator_<cv::Vec3f> sampleIt = colorSamples.begin<cv::Vec3f>();
	for(int i=0; i<sampleCount; i++){
		int pos = i * 3;
		*sampleIt = cv::Vec3f( pixels[pos], pixels[pos+1], pixels[pos+2] );
		sampleIt++;
	}
	
	// call kmeans
	cv::Mat labels, clusters;
	cv::kmeans( colorSamples, colorCount, labels, cv::TermCriteria(), 2, cv::KMEANS_RANDOM_CENTERS, clusters ); //cv::TermCriteria::COUNT, 8, 0 
	
	// clear our list of colors
	colors.clear();
	
	for( int i = 0; i < colorCount; ++i ){
		ofColor clusterColor = ofColor( clusters.at<cv::Vec3f>(i,0)[0], clusters.at<cv::Vec3f>(i,0)[1], clusters.at<cv::Vec3f>(i,0)[2] );
		colors.push_back(clusterColor);
	}
	
	/*
	
	// add colors from labelz
	unsigned char * p = temp.getPixels();
	cv::MatIterator_<int> labelIt = labels.begin<int>();
	for(int i=0; i<colorCount; i++){
		
		ofColor newColor;
		newColor.r = clusterColors[*labelIt].r;
		newColor.g = clusterColors[*labelIt].g;
		newColor.b = clusterColors[*labelIt].b;
		 
		++labelIt;
		//cout << i << " " << colors[i] << endl;
	}
	
	*/
	
	return colors;
}

void ofxColorQuantizer::draw(ofPoint pos){

	int swatchSize = 20;
	int swatchID = 0;
	
	ofPushMatrix();
	
	ofTranslate(pos);
	
	vector<ofColor>::iterator cIter = colors.begin();
	while( cIter != colors.end() ){
	
		ofSetColor(*cIter);
		ofRect(0, 0, swatchSize, swatchSize);
		ofTranslate(swatchSize, 0, 0);
		cIter++;
	}
	
	ofPopMatrix();
}

void ofxColorQuantizer::draw(int x, int y){

	draw(ofPoint(x, y));
}

vector<ofColor> & ofxColorQuantizer::getColors(){
	
	return colors;
}

void ofxColorQuantizer::setNumColors(unsigned int nColors){
	
	numColors = nColors;
}

int ofxColorQuantizer::getNumColors(){

	return numColors;
}
