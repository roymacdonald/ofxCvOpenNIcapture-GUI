#include "testApp.h"  


//--------------------------------------------------------------  
void testApp::setup(){  
	
	cual=1;
	iRGB.allocate(640,480);
	iDepth.allocate(640,480);
	dMask.allocate(640,480);
	iDepth16.allocate(640,480);
	
	try{
		capture.open(CV_CAP_OPENNI);
	}
	catch(exception e){
		cout << endl << "No existen dispositivos disponibles." << endl;
		return;
	}
	if( !capture.isOpened() )
    {
        cout << "No se pudo abrir el dispositivo de captura." << endl;
        return ;
    }
    cout << "OpenNI capture opened." << endl;
	cout << "FPS Nominal : " << capture.get(CV_CAP_PROP_FPS) << endl;
	
	farThreshold  = 65535;
	nearThreshold = 0;
	
	showThresholds=true;
	
	//cout<<"imgDepth rows: "<< ofToString(imgDepth.rows)<<"  cols: "<<ofToString(imgDepth.cols)<<endl;
	cout << "iDepth widthStep"<<ofToString(iDepth.getCvImage()->widthStep)<<endl;
	cout << "iDepth depth"<<ofToString(iDepth.getCvImage()->depth)<<"  channels: "<<ofToString(iDepth.getCvImage()->nChannels)<<endl;
	cout << "iDepth16 depth"<<ofToString(iDepth16.getCvImage()->depth)<<"  channels: "<<ofToString(iDepth16.getCvImage()->nChannels)<<endl;
	//---------------------------GUI----------------------------------------------------------------
	
	gui = new MyGUI();
	MyPanel* settingsPanel = new MyPanel("Settings", 640, 500);
	gui->addControl( settingsPanel );
	
	MySlider* farThresholdSlider = new MySlider("Far Threshold", 10, 30, 500, 20, &farThreshold, 0, 65535);
	settingsPanel->addControl( farThresholdSlider );
	
	MySlider* nearThresholdSlider = new MySlider("Near Threshold", 10, 60, 500, 20, &nearThreshold, 0,65535);
	settingsPanel->addControl( nearThresholdSlider );
}
//--------------------------------------------------------------
void testApp::update(){
	if( !capture.grab() )
	{
		cout << "Can not grab images." << endl;
		return;
	}
	else
	{
		capture.retrieve( imgDepth, CV_CAP_OPENNI_DEPTH_MAP);
		capture.retrieve( depthMask, CV_CAP_OPENNI_VALID_DEPTH_MASK);
		capture.retrieve (imgRGB, CV_CAP_OPENNI_BGR_IMAGE);
		
		*iRGB.getCvImage()=imgRGB;
		*dMask.getCvImage()=depthMask;
		if (showThresholds) {
			int min=0; int max=0;
			for(int i = 0; i < imgDepth.rows; i++) {
				const ushort* Mi = imgDepth.ptr<ushort>(i); 
				uchar * ptr = (uchar*)(iDepth.getCvImage()->imageData + i * iDepth.getCvImage()->widthStep);
				for(int j = 0; j < imgDepth.cols; j++){ 
					ushort pix = Mi[j];
						if (pix>farThreshold) {
							pix=farThreshold;
						}
						if (pix<nearThreshold) {
							pix=nearThreshold;
						}
						pix-=nearThreshold;
					
						ptr[j]= (uchar)floor(pix*255.0f/(farThreshold-nearThreshold));
				}
			}
			cout << "iDepth min val: "<<ofToString(min)<<"  max: "<<ofToString(max)<<endl;
			
			iDepth.flagImageChanged();
		}else {
			*iDepth16.getCvImage()=imgDepth;
			iDepth16.flagImageChanged();
			
		}
		iRGB.flagImageChanged();
		dMask.flagImageChanged();
	}
}
//--------------------------------------------------------------
void testApp::draw(){
	gui->draw();	
	ofBackground(0,0, 0);
	ofSetColor(255, 255, 255);
	iRGB.draw(0, 0);
	if (showThresholds) {
			iDepth.draw(640, 0);
	}else{
	iDepth16.draw(640, 0);
	}
	dMask.draw(0,480,320,240);
}  
//--------------------------------------------------------------  
void testApp::keyPressed  (int key){
	switch (key) {
		case 't':
		case 'T':
			showThresholds ^=true;
		break;
		case 's':
		case 'S':
	//		showShortImg ^=true;
			break;
		default:
		break;
	}
}  
//--------------------------------------------------------------  
void testApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------  
void testApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------  
void testApp::mousePressed(int x, int y, int button){}
//--------------------------------------------------------------  
void testApp::mouseReleased(int x, int y, int button){}
//--------------------------------------------------------------  
void testApp::resized(int w, int h){}