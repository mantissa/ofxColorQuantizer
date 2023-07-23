#include "ofApp.h"

#include "ColorConverter.h"

bool comparePos(const colorMapping& s1, const colorMapping& s2) {
	return s1.pos < s2.pos;
}

bool compareBrightness(const colorMapping& s1, const colorMapping& s2) {
	return s1.color.getBrightness() < s2.color.getBrightness();
}

bool compareHue(const colorMapping& s1, const colorMapping& s2) {
	return s1.color.getHue() < s2.color.getHue();
}

bool compareSaturation(const colorMapping& s1, const colorMapping& s2) {
	return s1.color.getSaturation() < s2.color.getSaturation();
}


//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);

	//-

	gui.setup();
	parameters.setName("COLOR QUANTIZER");
	parameters.add(numColors.set("number of colors", 10, 1, 50));
	parameters.add(sortedType.set("sort type", 1, 1, 4));
	parameters.add(labelStr.set(" ", labelStr));
	parameters.add(bReBuild.set("re build", false));
	gui.add(parameters);
	gui.setPosition(450, 50);
	ofAddListener(parameters.parameterChangedE(), this, &ofApp::Changed_parameters);

	//-

	imageName = "0.jpg";
	buildFromImageFile(imageName, numColors);
}


//--------------------------------------------------------------
void ofApp::update() {}



//--------------------------------------------------------------
void ofApp::draw()
{
	drawBg();

	int x = 50;//x pad for left/right window
	boxPad = 2;

	//-

	// debug text
	ofDrawBitmapStringHighlight("Loaded image path/url: '" + imageName + "'", 10, 20, ofColor::black, ofColor::white);
	ofDrawBitmapStringHighlight("Select image: [01234567][qwe][asd][zxc]", 10, 40, ofColor::black, ofColor::white);
	ofDrawBitmapStringHighlight("Sorting: " + labelStr.get(), 10, 70, ofColor::black, ofColor::white);
	ofDrawBitmapStringHighlight("Change sorting: [backspace]", 10, 90, ofColor::black, ofColor::white);
	ofDrawBitmapStringHighlight("Last Process Time: " + ofToString(timeForLastProcess) +"ms", 10, 110, ofColor::black, ofColor::white);

	ofPushMatrix();
	ofTranslate(x, 200);
	ofSetColor(255);

	// draw original image but resized to ImgW pixels width, same aspect ratio
	float imgRatio = image.getHeight() / image.getWidth();
	int ImgW = 200;
	int imgH = imgRatio * ImgW;

	image.draw(0, 0, ImgW, imgH);

	wPal = ofGetWidth() - (x + ImgW + x);
	boxW = wPal / colorQuantizer.getNumColors();
	boxSize = boxW - boxPad;

	ofPushMatrix();
	ofTranslate(0, imgH);

	ofSetColor(255, 100);
	ofDrawBitmapString("(Original sorting has colors weighted based on their areas, their order is based on their chroma values)", 0, 50);

	ofTranslate(ImgW + 20, 0);

	// all colors % bars
	for (int i = 0; i < colorQuantizer.getNumColors(); i++)
	{
		ofSetColor(0, 50);
		ofDrawRectangle(i * (boxSize + boxPad), 0, boxSize, -imgH);
		ofSetColor(sortedColors[i].color);
		ofDrawRectangle(i * (boxSize + boxPad), 0, boxSize, ofMap(sortedColors[i].weight, 0, 1, 0, -imgH));
		ofSetColor(255);
		ofDrawBitmapString(ofToString(int(sortedColors[i].weight * 100)) + "%", i * (boxSize + boxPad), 30);
	}

	// palette preview
	ofTranslate(0, 100);
	draw_Palette_Preview();

	ofPopMatrix();
	ofPopMatrix();

	//-

	gui.draw();
}
//--------------------------------------------------------------
void ofApp::drawBg()
{
	if (bError)
	{
		// Red if error.
		float v = glm::cos(10 * ofGetElapsedTimef());
		float a1 = ofMap(v, -1, 1, 100, 200, true);
		ofColor c = ofColor(a1, 0, 0);
		ofClear(c);
	}
	else if (bWait)
	{
		// Fade blink when waiting. 
		ofColor c = colorBg.get();
		//ofColor c = bigTextInput.getColor();
		auto br = c.getBrightness();
		float g = 30; //amplitude
		float v = glm::cos(10 * ofGetElapsedTimef());
		float a1 = ofMap(v, -1, 1, br - g, br, true);
		//float a1 = ofMap(v, -1, 1, 100, 150, true);
		c.setBrightness(a1);
		ofClear(c);
	}
	else
	{
		// Flash when submit
		if (v > 0) v -= 0.05f;
		else v = 0;
		int bgMin = 100;
		if (v > 0) ofClear(bgMin + (255 - bgMin) * v);
		else
		{
			ofClear(colorBg.get());
		}
	}
}

//--------------------------------------------------------------
void ofApp::build() {
	bWait = true;
	v = 1;
	auto t = ofGetElapsedTimeMillis();

	colorQuantizer.setNumColors(numColors);
	colorQuantizer.quantize(imageCopy.getPixels());

	sortedColors.clear();;
	sortedColors.resize(colorQuantizer.getNumColors());
	for (int i = 0; i < colorQuantizer.getNumColors(); i++)
	{
		ofFloatColor fc = ofFloatColor(colorQuantizer.getColors()[i].r / 255.0, colorQuantizer.getColors()[i].g / 255.0, colorQuantizer.getColors()[i].b / 255.0);
		ofVec3f labCol = ColorConverter::rgbToLab(fc);

		sortedColors[i].distance = ColorConverter::calcChroma(labCol);
		sortedColors[i].color = colorQuantizer.getColors()[i];
		sortedColors[i].weight = colorQuantizer.getColorWeights()[i];
	}

	std::sort(sortedColors.begin(), sortedColors.end(), by_distance());

	//--

	map_setup();

	timeForLastProcess = ofGetElapsedTimeMillis() - t;
}

//--------------------------------------------------------------
void ofApp::quantizeImage(string imgName, int _numColors) {
	numColors = _numColors;

	image.load(imgName);

	imageCopy.clear();
	imageCopy = image;//speed up
	//imageCopy.load(imgName);

	// resize to speed up
	imageCopy.resize(imageCopy.getWidth() / 4, imageCopy.getHeight() / 4);

	build();
}


//--------------------------------------------------------------
void ofApp::Changed_parameters(ofAbstractParameter& e) {
	string WIDGET_name = e.getName();

	ofLogNotice() << "Changed_parameters: " << WIDGET_name << ": " << e;

	if (WIDGET_name == "sort type")
	{
		switch (sortedType) {
		case 1:
			ofSort(colorMapSortable, comparePos);
			labelStr = "Original";
			break;
		case 2:
			ofSort(colorMapSortable, compareHue);
			labelStr = "Hue";
			break;
		case 3:
			ofSort(colorMapSortable, compareBrightness);
			labelStr = "Brightness";
			break;
		case 4:
			ofSort(colorMapSortable, compareSaturation);
			labelStr = "Saturation";
			break;
		default:
			break;
		}
	}
	else if (WIDGET_name == "re build")
	{
		if (bReBuild)
		{
			bReBuild = false;
			build();
		}
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	//-

	// files

	if (key == '0')
	{
		imageName = "0.jpg";
		buildFromImageFile(imageName, numColors);
	}
	if (key == '1')
	{
		imageName = "1.jpg";
		buildFromImageFile(imageName, numColors);
	}
	if (key == '2')
	{
		imageName = "2.jpg";
		buildFromImageFile(imageName, numColors);
	}
	if (key == '3')
	{
		imageName = "3.jpg";
		buildFromImageFile(imageName, numColors);
	}
	if (key == '4')
	{
		imageName = "4.jpg";
		buildFromImageFile(imageName, numColors);
	}
	if (key == '5')
	{
		imageName = "5.jpg";
		buildFromImageFile(imageName, numColors);
	}
	if (key == '6')
	{
		imageName = "6.jpg";
		buildFromImageFile(imageName, numColors);
	}
	if (key == '7')
	{
		imageName = "7.jpg";
		buildFromImageFile(imageName, numColors);
	}

	//-

	// urls palettes

	if (key == 'q')
	{
		imageName = "https://media.gettyimages.com/photos/argentina-buenos-aires-dawn-at-center-with-rush-hour-picture-id667138246?k=6&m=667138246&s=612x612&w=0&h=PTpexeaqMB-gYmImToxeV2cMGrRAPImeLkws6fFKfh0=";
		buildFromImageFile(imageName, numColors);
	}

	if (key == 'w')
	{
		imageName = "https://as1.ftcdn.net/jpg/02/13/60/70/500_F_213607058_uz3KRA8ASgk89L1DahwlfHrfQ74T2g5n.jpg";
		buildFromImageFile(imageName, numColors);
	}

	if (key == 'e')
	{
		imageName = "https://creativepro.com/wp-content/uploads/sites/default/files/styles/article-full-column-width/public/20140306-color1.jpg?itok=3oHDuKTN";
		buildFromImageFile(imageName, numColors);
	}

	//-

	// url pictures

	if (key == 'a')
	{
		imageName = "https://hips.hearstapps.com/esq.h-cdn.co/assets/16/20/blade-runner_1.jpg";
		buildFromImageFile(imageName, numColors);
	}

	if (key == 's')
	{
		imageName = "https://www.eldiario.es/fotos/Paleta-San-Junipero-Black-Mirror_EDIIMA20190731_0485_19.jpg";
		buildFromImageFile(imageName, numColors);
	}

	if (key == 'd')
	{
		imageName = "https://www.eldiario.es/fotos/Paleta-colores-verdes-escena-Land_EDIIMA20190731_0457_19.jpg";
		buildFromImageFile(imageName, numColors);
	}

	if (key == 'f')
	{
		imageName = "http://mymodernmet.com/wp/wp-content/uploads/2017/08/palette-maniac-15.jpg";
		buildFromImageFile(imageName, numColors);
	}

	//-

	// more url

	if (key == 'z')
	{
		imageName = "https://s3.amazonaws.com/images.gearjunkie.com/uploads/2018/05/matterhorn-3x2.jpg";
		buildFromImageFile(imageName, numColors);
	}

	if (key == 'x')
	{
		imageName = "http://cdn.cnn.com/cnnnext/dam/assets/170407220916-04-iconic-mountains-matterhorn-restricted.jpg";
		buildFromImageFile(imageName, numColors);
	}

	if (key == 'c')
	{
		imageName = "https://store-images.s-microsoft.com/image/apps.33776.13570837168441901.d8820ad6-c4ef-45a9-accb-c6dd763aee48.560134ce-5fa0-4486-95cd-b0ba8d4921ff?w=672&h=378&q=80&mode=letterbox&background=%23FFE4E4E4&format=jpg";
		buildFromImageFile(imageName, numColors);
	}

	//-

	// sort types

	if (key == OF_KEY_BACKSPACE) {
		sortedType++;
		if (sortedType > 4)
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
	if (key == 'k') {
		kMeansTest();
	}

}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}



//--------------------------------------------------------------
void ofApp::map_setup()
{
	palette.clear();
	int palSize = colorQuantizer.getNumColors();
	palette.resize(palSize);

	//palette = colorQuantizer.getColors();
	for (int i = 0; i < sortedColors.size(); i++)
	{
		palette[i] = sortedColors[i].color;
	}

	colorMap.clear();
	colorMapSortable.clear();

	for (int i = 0; i < palSize; i++)
	{
		colorMap[i] = palette[i];
	}

	for (unsigned int i = 0; i < palSize; i++) {//colorNameMap

		map<int, ofColor>::iterator mapEntry = colorMap.begin();
		std::advance(mapEntry, i);

		colorMapping mapping;
		mapping.pos = mapEntry->first;
		mapping.color = mapEntry->second;
		colorMapSortable.push_back(mapping);
	}

	switch (sortedType) {
	case 1:
		ofSort(colorMapSortable, comparePos);
		labelStr = "Original";
		break;
	case 2:
		ofSort(colorMapSortable, compareHue);
		labelStr = "Hue";
		break;
	case 3:
		ofSort(colorMapSortable, compareBrightness);
		labelStr = "Brightness";
		break;
	case 4:
		ofSort(colorMapSortable, compareSaturation);
		labelStr = "Saturation";
		break;
	default:
		break;
	}
}


//--------------------------------------------------------------
void ofApp::buildFromImageFile(string path, int num) {
	//TODO: improve with threading load..
	quantizeImage(path, num);
	build();
}


//--------------------------------------------------------------
void ofApp::buildFromImageUrl(string url, int num) {
	//TODO: improve with threading load and some HTTP image browsing api..
	quantizeImage(url, num);
	build();
}


//--------------------------------------------------------------
void ofApp::draw_Palette_Preview()
{
	ofPushMatrix();
	ofPushStyle();

	ofRectangle r;
	string str = "sorted palette preview (" + ofToString(labelStr) + ")";
	ofDrawBitmapStringHighlight(str, 5, -10, ofColor::black, ofColor::white);

	for (int col = 0; col < palette.size(); col++)
	{
		r = ofRectangle(0, 0, boxSize, boxSize);
		ofFill();

		ofSetColor(colorMapSortable[col].color);
		//ofSetColor(palette[col]);

		ofDrawRectangle(r);
		ofTranslate(boxSize + boxPad, 0);
	}

	ofPopStyle();
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::kMeansTest() {
	// for testing

	cv::Mat samples = (cv::Mat_<float>(8, 1) << 31, 2, 10, 11, 25, 27, 2, 1);
	cv::Mat labels;

	// double kmeans(const Mat& samples, int clusterCount, Mat& labels,
	cv::TermCriteria termcrit;
	int attempts, flags;
	cv::Mat centers;
	double compactness = cv::kmeans(samples, 3, labels, cv::TermCriteria(), 2, cv::KMEANS_PP_CENTERS, centers);

	cout << "labels:" << endl;
	for (int i = 0; i < labels.rows; ++i)
	{
		cout << labels.at<int>(0, i) << endl;
	}

	cout << "\ncenters:" << endl;
	for (int i = 0; i < centers.rows; ++i)
	{
		cout << centers.at<float>(0, i) << endl;
	}

	cout << "\ncompactness: " << compactness << endl;
}

