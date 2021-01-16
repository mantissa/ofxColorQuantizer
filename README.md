# [FORK]
forked from mantissa/ofxColorQuantizer  
I recommend to check this helper too:  
https://github.com/moebiussurfing/ofxColorQuantizerHelper

## added example-weights and ColorConverter.h by stc
copied from the stc user fork: https://github.com/stc/ofxColorQuantizer/
This example can get colors weighted based on their areas, their order is based on their chroma values.

## added example-weights2 by moebiussurfing
This current fork has another example that can sort the palette colors by Hue, Saturation, Brightness or the above method.
It has a gui panel too to change the number of colors, the sorting type, rebuild when changing number of colors... on the fly.
There's some images loading from url too.
![Alt text](/screenshots/screenshot1.png?raw=true "MoebiusSurfing")
![Alt text](/screenshots/screenshot2.png?raw=true "MoebiusSurfing")
![Alt text](/screenshots/screenshot3.png?raw=true "MoebiusSurfing")

### TODO:
- drag and drop image files to process
- threaded image load
- speed up process or downsize image to process 
- use some http API to searching and image browsing



~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 

ofxColorQuantizer

Extract a color palette from an image using the K-means algorithm.

Based on the ocvColorQuantize demo that ships with Cinder:
https://github.com/cinder/Cinder-OpenCV/blob/master/samples/ocvColorQuantize

This add-on uses ofxOpenCv.

by Jeremy Rotsztain 

http://www.mantissa.ca
