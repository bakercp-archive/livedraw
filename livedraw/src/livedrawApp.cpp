#include "livedrawApp.h"

//--------------------------------------------------------------
void livedrawApp::setup(){
	// main window setup
	ofSetFrameRate(60);
	ofBackground(0);
    
	ofSetLogLevel(OF_LOG_NOTICE);

	guiManager.setup();
    sessionManager.setup();
    assetManager.setup();
	effectsManager.setup();
    
    canvas.setup();
    canvas.setAssetManager(&assetManager);
    canvas.setEffectsManager(&effectsManager);
    
	oscManager.setup(PORT);
    oscManager.addOscChild(&canvas);
    oscManager.addOscChild(&effectsManager); 
    oscManager.addOscChild(&sessionManager); 
    
    
    /******** GENERATE SOME TEST DATA **********/
    
      
}

//--------------------------------------------------------------
void livedrawApp::update(){
    // OSC gets checked first
    oscManager.update();  

    // session manager
    sessionManager.update();
    
    // run asset manager updates (look for new files, etc)
    assetManager.update();

    // updated effects
    effectsManager.update();
	
    // canvas gets updated
    canvas.update();
    
    // GUI gets checked last to reflect any changes in state
    guiManager.update();

}

//--------------------------------------------------------------
void livedrawApp::draw(){
    
    
    ofSetColor(255,0,0);
    ofFill();
    ofRect(0,0, 300,300);


    canvas.render(); // accumulate everything onto the fbo.
    
    // here is where we can do the transformations before projection
    canvas.draw();
    
    // draw the gui
    guiManager.draw();

    ofSetColor(255);

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

//--------------------------------------------------------------
void livedrawApp::dragEvent(ofDragInfo dragInfo) {
    
}

//--------------------------------------------------------------
void livedrawApp::gotMessage(ofMessage msg) {

}
