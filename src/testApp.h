#ifndef _TEST_APP  
#define _TEST_APP  

#include "ofMain.h"  
#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/highgui/highgui.hpp"

#include "ofxOpenCv.h"

#include "MyGUI.h"

class testApp : public ofBaseApp{  
	
public:  
	
	void setup();  
	void update();  
	void draw();  
	
	void keyPressed  (int key);  
	void mouseMoved(int x, int y );  
	void mouseDragged(int x, int y, int button);  
	void mousePressed(int x, int y, int button);  
	void mouseReleased(int x, int y, int button);  
	void resized(int w, int h);  
	
	int cual;
	
	ofxCvColorImage iRGB;
	ofxCvShortImage iDepth16;
	ofxCvGrayscaleImage dMask;
	ofxCvGrayscaleImage iDepth;
	
	cv::Mat imgRGB, imgDepth, depthMask;
	cv::VideoCapture capture;	
	
	MyGUI * gui;
	
	int farThreshold;
	int nearThreshold;
	
	bool showThresholds;
	
};  

#endif  