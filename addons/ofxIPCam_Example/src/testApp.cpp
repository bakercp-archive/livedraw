#include "testApp.h"





//--------------------------------------------------------------
void testApp::setup(){	 
	
	camWidth 		= 320;	// try to grab at this size. 
	camHeight 		= 240;
	
	//cam.execute("http://poipubeach.serveftp.net:5001/axis-cgi/mjpg/video.cgi?resolution=320x240",camWidth,camHeight);
	//videoTexture.allocate(camWidth,camHeight, GL_RGBA) ;//GL_RGBA);

	
	cam0.execute("http://210.236.173.198/axis-cgi/mjpg/video.cgi?camera=&resolution=320x240",camWidth,camHeight);
    
	/*
	 http://134.84.229.45:5000/
	 http://134.84.229.45:5001/
	 http://134.84.229.45:5002/
	 http://134.84.229.45:5003/

	 */
	
	//cam0.execute("http://134.84.229.45:5001/videostream.cgi",camWidth,camHeight);

	
	videoTexture0.allocate(camWidth,camHeight, GL_RGBA) ;//GL_RGBA);

    ofSetFrameRate(30);
}


//--------------------------------------------------------------
void testApp::update(){
	ofBackground(100,100,100);
	//unsigned char * pixels = cam.getPixels();
	//if (pixels != NULL){
	//	videoTexture.loadData(pixels, camWidth, camHeight, GL_BGR);
	//}

	//printf("new frame = %d",cam0.newFrame);
	
	if(true) {//cam0.isNewFrame()) {
		unsigned char * pixels = cam0.getPixels();
		if (pixels != NULL){
			videoTexture0.loadData(pixels, camWidth, camHeight, GL_BGR);
		}
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0xffffff);
	//videoTexture.draw(0,0);
	videoTexture0.draw(camWidth,0);

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	if (key == 's' || key == 'S'){
	//	vidGrabber.videoSettings();
	}
	
	
}


//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
