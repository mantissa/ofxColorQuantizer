#include "ofApp.h"

#include "ColorConverter.h"

bool comparePos( const colorNameMapping& s1, const colorNameMapping& s2 ) {
    return s1.pos < s2.pos;
}

bool compareBrightness( const colorNameMapping& s1, const colorNameMapping& s2 ) {
    return s1.color.getBrightness() < s2.color.getBrightness();
}

bool compareHue( const colorNameMapping& s1, const colorNameMapping& s2 ) {
    return s1.color.getHue() < s2.color.getHue();
}

bool compareSaturation( const colorNameMapping& s1, const colorNameMapping& s2 ) {
    return s1.color.getSaturation() < s2.color.getSaturation();
}


//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30);

    //-

    gui.setup();
    parameters.setName("COLOR QUANTIZER");
    parameters.add(numColors.set("number of colors", 10, 1, 50));
    parameters.add(sortedType.set("sort type", 1, 1, 4));
    parameters.add(labelStr.set(" ", labelStr));
    gui.add(parameters);
    gui.setPosition(400, 30);
    ofAddListener(parameters.parameterChangedE(), this, &ofApp::Changed_parameters);

    //-

    imageName = "0.jpg";
    getImagePalette(imageName, numColors);
}


//--------------------------------------------------------------
void ofApp::update(){}



//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(100,100,100);

    //-

    ofDrawBitmapStringHighlight("loaded image path/url: '"+imageName+"'", 10, 20, ofColor::black, ofColor::white);
    ofDrawBitmapStringHighlight("select image: [01234567][qwe][asd][zxc]", 10, 40, ofColor::black, ofColor::white);
    ofDrawBitmapStringHighlight("sorting: "+labelStr.get(), 10, 70, ofColor::black, ofColor::white);
    ofDrawBitmapStringHighlight("change sorting: [backspace]", 10, 90, ofColor::black, ofColor::white);

    ofPushMatrix();
    ofTranslate(50, 200);
    ofSetColor(255);

    if (image.getWidth()>500 || image.getHeight()>500)
        image.draw(0, 0, image.getWidth()/5, image.getHeight()/5);
    else
        image.draw(0, 0, image.getWidth(), image.getHeight());

    ofPushMatrix();

    if (image.getWidth()>500 || image.getHeight()>500)
        ofTranslate(0, image.getHeight()/5);
    else
        ofTranslate(0, image.getHeight());

    ofSetColor(255, 100);
    ofDrawBitmapString("(original sorting has colors weighted based on their areas, their order is based on their chroma values)", 0, 50);

    if (image.getWidth()>500 || image.getHeight()>500)
        ofTranslate(image.getWidth()/5 + 20,0);
    else
        ofTranslate(image.getWidth() + 20, 0);

    for(int i=0; i<colorQuantizer.getNumColors(); i++)
    {
        ofSetColor(0,50);
        ofDrawRectangle(i*(boxSize+boxPad), 0, boxSize, -image.getHeight()/5);
        ofSetColor(sortedColors[i].color);
        ofDrawRectangle(i*(boxSize+boxPad), 0, boxSize, ofMap(sortedColors[i].weight, 0, 1, 0, -image.getHeight()/5));
        ofSetColor(255);
        ofDrawBitmapString(ofToString(int(sortedColors[i].weight * 100)) + "%", i * (boxSize+boxPad),30);
    }

    ofTranslate(0, 100);
    draw_Palette_Preview();

    ofPopMatrix();
    ofPopMatrix();

    //-

    gui.draw();
}


//--------------------------------------------------------------
void ofApp::quantizeImage(string imgName, int numColors) {
    image.load(imgName);
    ofImage imageCopy;
    imageCopy.load(imgName);

    if (imageCopy.getWidth()>500 || imageCopy.getHeight()>500)
       imageCopy.resize(imageCopy.getWidth()/2, imageCopy.getHeight()/2);
    
    colorQuantizer.setNumColors(numColors);
    colorQuantizer.quantize(imageCopy.getPixels());
    
    sortedColors.clear();;
    sortedColors.resize(colorQuantizer.getNumColors());
    for(int i = 0; i < colorQuantizer.getNumColors(); i++)
    {
        ofFloatColor fc = ofFloatColor(colorQuantizer.getColors()[i].r/255.0, colorQuantizer.getColors()[i].g/255.0, colorQuantizer.getColors()[i].b/255.0);
        ofVec3f labCol = ColorConverter::rgbToLab(fc);
        
        sortedColors[i].distance = ColorConverter::calcChroma(labCol);
        sortedColors[i].color = colorQuantizer.getColors()[i];
        sortedColors[i].weight = colorQuantizer.getColorWeights()[i];
    }
    
    std::sort(sortedColors.begin(), sortedColors.end(), by_distance());

    //--

    map_setup();
}


//--------------------------------------------------------------
void ofApp::Changed_parameters(ofAbstractParameter &e) {
    string WIDGET_name = e.getName();

    ofLogNotice() << "Changed_parameters: " << WIDGET_name << ": " << e;

    if (WIDGET_name == "sort type")
    {
        switch (sortedType) {
            case 1:
                ofSort(colorNames, comparePos);
                labelStr = "Original";
                break;
            case 2:
                ofSort(colorNames, compareHue);
                labelStr = "Hue";
                break;
            case 3:
                ofSort(colorNames, compareBrightness);
                labelStr = "Brightness";
                break;
            case 4:
                ofSort(colorNames, compareSaturation);
                labelStr = "Saturation";
                break;
            default:
                break;
        }
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    //-

    // files

    if (key=='0')
    {
        imageName = "0.jpg";
        getImagePalette(imageName, numColors);
    }
    if (key=='1')
    {
        imageName = "1.jpg";
        getImagePalette(imageName, numColors);
    }
    if (key=='2')
    {
        imageName = "2.jpg";
        getImagePalette(imageName, numColors);
    }
    if (key=='3')
    {
        imageName = "3.jpg";
        getImagePalette(imageName, numColors);
    }
    if (key=='4')
    {
        imageName = "4.jpg";
        getImagePalette(imageName, numColors);
    }
    if (key=='5')
    {
        imageName = "5.jpg";
        getImagePalette(imageName, numColors);
    }
    if (key=='6')
    {
        imageName = "6.jpg";
        getImagePalette(imageName, numColors);
    }
    if (key=='7')
    {
        imageName = "7.jpg";
        getImagePalette(imageName, numColors);
    }

    //-

    // urls palettes

    if (key=='q')
    {
        imageName = "https://mk0learntocodew6bl5f.kinstacdn.com/wp-content/uploads/2016/01/material-palette.png";
        getImagePalette(imageName, numColors);
    }

    if (key=='w')
    {
        imageName = "https://as1.ftcdn.net/jpg/02/13/60/70/500_F_213607058_uz3KRA8ASgk89L1DahwlfHrfQ74T2g5n.jpg";
        getImagePalette(imageName, numColors);
    }

    if (key=='e')
    {
        imageName = "https://creativepro.com/wp-content/uploads/sites/default/files/styles/article-full-column-width/public/20140306-color1.jpg?itok=3oHDuKTN";
        getImagePalette(imageName, numColors);
    }

    //-

    // url pictures

    if (key=='a')
    {
        imageName = "https://www.eldiario.es/fotos/Paleta-colores-empleada-Her_EDIIMA20190731_0426_19.jpg";
        getImagePalette(imageName, numColors);
    }

    if (key=='s')
    {
        imageName = "https://www.eldiario.es/fotos/Paleta-San-Junipero-Black-Mirror_EDIIMA20190731_0485_19.jpg";
        getImagePalette(imageName, numColors);
    }

    if (key=='d')
    {
        imageName = "https://www.eldiario.es/fotos/Paleta-colores-verdes-escena-Land_EDIIMA20190731_0457_19.jpg";
        getImagePalette(imageName, numColors);
    }

    //-

    // more url

    if (key=='z')
    {
        imageName = "https://s3.amazonaws.com/images.gearjunkie.com/uploads/2018/05/matterhorn-3x2.jpg";
        getImagePalette(imageName, numColors);
    }

    if (key=='x')
    {
        imageName = "http://cdn.cnn.com/cnnnext/dam/assets/170407220916-04-iconic-mountains-matterhorn-restricted.jpg";
        getImagePalette(imageName, numColors);
    }

    if (key=='c')
    {
        imageName = "https://store-images.s-microsoft.com/image/apps.33776.13570837168441901.d8820ad6-c4ef-45a9-accb-c6dd763aee48.560134ce-5fa0-4486-95cd-b0ba8d4921ff?w=672&h=378&q=80&mode=letterbox&background=%23FFE4E4E4&format=jpg";
        getImagePalette(imageName, numColors);
    }

    //-

    // sort

    if (key==OF_KEY_BACKSPACE){
        sortedType++;
        if (sortedType>4)
            sortedType = 1;
    }

    //        if (key == '1'){
    //            if (sortedType != 1){
    //                sortedType = 1;
    //            }
    //        }
    //        if (key == '2'){
    //            if (sortedType != 2){
    //                sortedType = 2;
    //            }
    //        }
    //        else if (key == '3'){
    //            if (sortedType != 3){
    //                sortedType = 3;
    //            }
    //        }
    //        else if (key == '4'){
    //            if (sortedType != 4){
    //                sortedType = 4;
    //            }
    //        }


    //-

    // test kMeansTest
    if (key == 'k'){
        kMeansTest();
    }

}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){}



//--------------------------------------------------------------
void ofApp::map_setup()
{
    palette.clear();
    int palSize = colorQuantizer.getNumColors();
    palette.resize(palSize);

    //palette = colorQuantizer.getColors();


    for(int i=0; i<sortedColors.size(); i++)
    {
        palette[i] = sortedColors[i].color;
    }

    colorNameMap.clear();
    colorNames.clear();

    for (int i=0; i<palSize; i++)
    {
        colorNameMap[i] = palette[i];
    }

    for (unsigned int i = 0; i < palSize; i++){//colorNameMap

         map<int, ofColor>::iterator mapEntry = colorNameMap.begin();
        std::advance( mapEntry, i );

        colorNameMapping mapping;
        mapping.pos = mapEntry->first;
        mapping.color = mapEntry->second;
        colorNames.push_back(mapping);
    }

    switch (sortedType) {
        case 1:
            ofSort(colorNames, comparePos);
            labelStr = "Original";
            break;
        case 2:
            ofSort(colorNames, compareHue);
            labelStr = "Hue";
            break;
        case 3:
            ofSort(colorNames, compareBrightness);
            labelStr = "Brightness";
            break;
        case 4:
            ofSort(colorNames, compareSaturation);
            labelStr = "Saturation";
            break;
        default:
            break;
    }
}


//--------------------------------------------------------------
void ofApp::getImagePalette(string path, int num){
    quantizeImage(path, num);
}


//--------------------------------------------------------------
void ofApp::getImageFromURLPalette(string url, int num){

    quantizeImage(url, num);
}


//--------------------------------------------------------------
void ofApp::draw_Palette_Preview()
{
    ofRectangle r;
    ofPushMatrix();
    ofPushStyle();

    string str = "sorted palette preview ("+ofToString(labelStr)+")";
    ofDrawBitmapStringHighlight(str, 5, -20, ofColor::black, ofColor::white);

    for (int col=0; col<palette.size(); col++)
    {
        r = ofRectangle(0, 0, boxSize, boxSize);
        ofFill();

        ofSetColor(colorNames[col].color);
        //ofSetColor(palette[col]);

        ofDrawRectangle(r);
        ofTranslate ( boxSize+boxPad, 0);
    }

    ofPopStyle();
    ofPopMatrix();
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

