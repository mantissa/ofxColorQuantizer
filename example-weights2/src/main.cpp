//#include "ofMain.h"
//#include "ofApp.h"
//#include "ofAppGlutWindow.h"
//
//int main( ){
//
//    ofAppGlutWindow window;
//    ofSetupOpenGL(&window, 1024,500, OF_WINDOW);
//    ofRunApp( new ofApp());
//
//}
#include "ofApp.h"

int main(){
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:

    ofSetupOpenGL(1440, 900, OF_WINDOW);

    ofRunApp(new ofApp());
}

