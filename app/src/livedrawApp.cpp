#include "livedrawApp.h"

//--------------------------------------------------------------
void livedrawApp::setup(){
	// main window setup
	ofSetFrameRate(60);
	
	// render window setup
	//fenster->setFPS(60);
	//fenster->setBounds(924, 100, 400, 300);
	
	
	ofSetLogLevel(OF_LOG_NOTICE);

	// TODO ... hack.  Why can't source manager get it's own?
	assetManager.setDirList(&aaa);
	assetManager.loadAssets();
	
	
    oscManager.setup();
    guiManager.setup();

	
	fbo.setup(1024, 768);

	
	//of.loadImage("application/cache/media/images/default_image.png");
	//of.loadImage("application/cache/media/videos/default_video.png");
	//of.loadImage("application/cache/media/streams/default_stream.png");
	//of.loadImage("application/cache/media/grabbers/default_grabber.png");

	
}

//--------------------------------------------------------------
void livedrawApp::update(){
	oscManager.update();
    guiManager.update();
	


}


//--------------------------------------------------------------
void livedrawApp::draw(){
    oscManager.update();
    guiManager.draw();

	
}


//--------------------------------------------------------------
void livedrawApp::keyPressed (int key){
	if(key == ' ')
		ofToggleFullscreen();
	if(key == 'a') 
	{
		ofLog(OF_LOG_NOTICE, "NUM IMAGES: " + ofToString(assetManager.getNumImageAssets()));
		ofLog(OF_LOG_NOTICE, "NUM VIDEOS: " + ofToString(assetManager.getNumVideoAssets()));
		ofLog(OF_LOG_NOTICE, "NUM GRABBERS: " + ofToString(assetManager.getNumGrabberAssets()));
		ofLog(OF_LOG_NOTICE, "NUM STREAMS: " + ofToString(assetManager.getNumStreamAssets()));
		
	}
	
}

//--------------------------------------------------------------
void livedrawApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void livedrawApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void livedrawApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void livedrawApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void livedrawApp::windowResized(int w, int h){

}

/*

//--------------------------------------------------------------
void livedrawApp::fensterUpdate(){
}

//--------------------------------------------------------------
void livedrawApp::fensterDraw(){
	
	//fbo.begin();
	ofDrawBitmapString("FBO contents", 100,100);
	//fbo.end();
	
	
	//fbo.draw(0,0);
	
	
}

//--------------------------------------------------------------
void livedrawApp::fensterKeyPressed  (int key){
	if(key == ' ')
		fenster->toggleFullscreen();

	
		
}

//--------------------------------------------------------------
void livedrawApp::fensterKeyReleased(int key){
	
}

//--------------------------------------------------------------
void livedrawApp::fensterMouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
//drag is not yet implemented
void livedrawApp::fensterMouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void livedrawApp::fensterMousePressed(int x, int y, int button){
	
};

//--------------------------------------------------------------
void livedrawApp::fensterMouseReleased(int x, int y, int button){
	
};

//--------------------------------------------------------------
void livedrawApp::fensterWindowResized(int w, int h){
	
	ofLog(OF_LOG_NOTICE, "Render window resized to " + ofToString(w) + "x" + ofToString(h));
	
};
 */
