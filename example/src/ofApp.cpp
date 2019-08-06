#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);

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
//    ofSetWindowShape(image.getWidth(), image.getHeight());
}


//--------------------------------------------------------------
void ofApp::getImagePalette(string path, int num){

    // load our image
    image.loadImage(path);

    // for speedz sake, quantize a smaller copy of the image
    ofImage imageCopy;
    imageCopy.loadImage(path);
    imageCopy.resize(imageCopy.getWidth()/2, imageCopy.getHeight()/2);

    // get our colors
    colorQuantizer.setNumColors(num);
    colorQuantizer.quantize(imageCopy.getPixelsRef());

    // resize the window to match the image
//    ofSetWindowShape(image.getWidth(), image.getHeight());
}


//--------------------------------------------------------------
void ofApp::getImageFromURLPalette(string url, int num){

    // load our image
    image.loadImage(url);
    
    if(image.getWidth()>1000 || image.getHeight()>600 )
    image.resize(image.getWidth()/3, image.getHeight()/3);

    // for speedz sake, quantize a smaller copy of the image
    ofImage imageCopy;
    imageCopy.loadImage(url);
    imageCopy.resize(imageCopy.getWidth()/3, imageCopy.getHeight()/3);

    // get our colors
    colorQuantizer.setNumColors(num);
    colorQuantizer.quantize(imageCopy.getPixelsRef());

    // resize the window to match the image
    //    ofSetWindowShape(image.getWidth(), image.getHeight());
}


//--------------------------------------------------------------
void ofApp::update(){
	

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofBackground(100,100,100);

	ofSetColor(255);

	image.draw(0, 0);
	
//    colorQuantizer.draw(ofPoint(0, image.getHeight()-20));
    colorQuantizer.draw(ofPoint(20, image.getHeight()+20));

}

//--------------------------------------------------------------
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    // files
    if (key=='0')
        getImagePalette("0.jpg", 12);
    if (key=='1')
        getImagePalette("1.jpg", 12);
    if (key=='2')
        getImagePalette("2.jpg", 12);
    if (key=='3')
        getImagePalette("3.jpg", 12);

    // urls palettes
    if (key=='q')
        getImageFromURLPalette("https://mk0learntocodew6bl5f.kinstacdn.com/wp-content/uploads/2016/01/material-palette.png", 12);
    if (key=='w')
        getImageFromURLPalette("https://as1.ftcdn.net/jpg/02/13/60/70/500_F_213607058_uz3KRA8ASgk89L1DahwlfHrfQ74T2g5n.jpg", 12);
    if (key=='e')
        getImageFromURLPalette("https://creativepro.com/wp-content/uploads/sites/default/files/styles/article-full-column-width/public/20140306-color1.jpg?itok=3oHDuKTN", 12);
    if (key=='r')
        getImageFromURLPalette("http://www.newdesignfile.com/postpic/2011/11/flat-ui-design-colors_104577.jpg", 12);
    if (key=='t')
        getImageFromURLPalette("https://cmkt-image-prd.global.ssl.fastly.net/0.1.0/ps/211731/910/607/m1/fpnw/wm0/main-.jpg?1413717475&s=845b5e05fb5961018c74a2ca8ae4d3dc", 12);
    if (key=='y')
        getImageFromURLPalette("https://www.sketchappsources.com/resources/source-image/material-color-palette-egorfedorov.png", 12);
    if (key=='u')
        getImageFromURLPalette("https://cdn.dribbble.com/users/282234/screenshots/4135500/flat_ui_colors_by_anwaltzzz.png", 12);
    if (key=='i')
        getImageFromURLPalette("https://pbs.twimg.com/media/DlXu-iDVAAEHQmL.jpg", 12);

// url pictures
    if (key=='a')
        getImageFromURLPalette("https://www.eldiario.es/fotos/Paleta-colores-empleada-Her_EDIIMA20190731_0426_19.jpg", 12);
    if (key=='s')
        getImageFromURLPalette("https://www.eldiario.es/fotos/Paleta-San-Junipero-Black-Mirror_EDIIMA20190731_0485_19.jpg", 12);
    if (key=='d')
        getImageFromURLPalette("https://www.eldiario.es/fotos/Paleta-colores-verdes-escena-Land_EDIIMA20190731_0457_19.jpg", 12);
    if (key=='f')
        getImageFromURLPalette("https://www.eldiario.es/fotos/Escala-monocromatica-Roma_EDIIMA20190731_0438_19.jpg", 12);
    if (key=='g')
        getImageFromURLPalette("https://www.eldiario.es/fotos/Paleta-colores-John-Wick_EDIIMA20190731_0490_19.jpg", 12);
    if (key=='h')
        getImageFromURLPalette("https://www.eldiario.es/fotos/Paleta-colores-John-Wick_EDIIMA20190731_0490_19.jpg", 12);

    //field scapes
    if (key=='z')
        getImageFromURLPalette("https://s3.amazonaws.com/images.gearjunkie.com/uploads/2018/05/matterhorn-3x2.jpg", 12);
    if (key=='x')
        getImageFromURLPalette("http://cdn.cnn.com/cnnnext/dam/assets/170407220916-04-iconic-mountains-matterhorn-restricted.jpg", 12);
    if (key=='c')
        getImageFromURLPalette("https://store-images.s-microsoft.com/image/apps.33776.13570837168441901.d8820ad6-c4ef-45a9-accb-c6dd763aee48.560134ce-5fa0-4486-95cd-b0ba8d4921ff?w=672&h=378&q=80&mode=letterbox&background=%23FFE4E4E4&format=jpg", 12);
    if (key=='v')
        getImageFromURLPalette("https://www.mountainphotography.com/images/xl/20120928-Cimarron-Sunset-Panorama.jpg", 12);
    if (key=='b')
        getImageFromURLPalette("https://www.mountainphotography.com/images/640/20130608-Alpenglow-on-Mt.-Sneffels.jpg", 12);
    if (key=='n')
        getImageFromURLPalette("https://image.shutterstock.com/image-vector/large-number-mountains-vast-landscapes-260nw-1389573218.jpg", 12);
    if (key=='m')
        getImageFromURLPalette("https://www.telegraph.co.uk/content/dam/Travel/galleries/travel/activityandadventure/The-worlds-most-beautiful-mountains/mountains-eiger_3374107a.jpg", 12);



}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
