#include "testApp.h"


testApp::~testApp() {
    // deleting
    delete buffer;
}

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
	ofSetFrameRate(30);
	
    
    // video setup
    
    camWidth 		= 320;	// try to grab at this size. 
	camHeight 		= 240;
	
	//vidGrabber.videoSettings();
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	//interp.reset(ofPoint(100, ofGetHeight()/2), ofPoint(ofGetWidth()-100, ofGetHeight()/2));	
    
    int fps = 30;
    
    buffer = new ofxVideoBufferPlayer(camWidth, camHeight, OF_IMAGE_COLOR, fps, fps * 2);// * 5); //
    isBuffering = false;
        

	//interp.insert(ofPoint(ofGetWidth()/2,0));//ofGetHeight()/2));
	
	
    //	frameByframe = false;

	/*
	fingerMovie.loadMovie("movies/fingers.mov");
	fingerMovie.play();
	 */
}

//--------------------------------------------------------------
void testApp::update() {
    
   // fingerMovie.idleMovie();
    
    vidGrabber.grabFrame();
	
	if (vidGrabber.isFrameNew()){
        buffer->add(vidGrabber.getPixels(), camWidth,camHeight, OF_IMAGE_COLOR);
    }
    
    buffer->update(); // update the buffer!

}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(0xFFFFFF);
    vidGrabber.draw(20,20);

    //buffer->getFrame(-1).draw(20, 320);
    
    buffer->draw(20, 320);
    
    
    ofSetColor(0,0,0);
    ofDrawBitmapString(ofToString(buffer->getNumBufferedFrames()) + "/" + ofToString(buffer->getPosition()), 500,500);
    
    string s = ofToString(buffer->getLoopPointsStart()) + "/" + ofToString(buffer->getLoopPointsEnd());

    ofDrawBitmapString(s, 500, 550);
    
    
    
    /*
    if(buffer->peek(20)) {
        ofTexture* t = buffer->peek(0);
        t->draw(360,20);
    }
    */

	//ofSetColor(0,0,0);
	//interp.draw();
	
	//ofPoint o = interp.returnPoint(ofPoint(mouseX,mouseY));

    
    
    
	
/*

    fingerMovie.draw(20,20);
    ofSetColor(0x000000);
    unsigned char * pixels = fingerMovie.getPixels();
    // let's move through the "RGB" char array
    // using the red pixel to control the size of a circle.
    for (int i = 4; i < 320; i+=8){
        for (int j = 4; j < 240; j+=8){
            unsigned char r = pixels[(j * 320 + i)*3];
            float val = 1 - ((float)r / 255.0f);
            ofCircle(400 + i,20+j,10*val);
        }
    }


    ofSetColor(0x000000);
	ofDrawBitmapString("press f to change",20,320);
    if(frameByframe) ofSetColor(0xCCCCCC);
    ofDrawBitmapString("mouse speed position",20,340);
    if(!frameByframe) ofSetColor(0xCCCCCC); else ofSetColor(0x000000);
    ofDrawBitmapString("keys <- -> frame by frame " ,190,340);
    ofSetColor(0x000000);

    ofDrawBitmapString("frame: " + ofToString(fingerMovie.getCurrentFrame()) + "/"+ofToString(fingerMovie.getTotalNumFrames()),20,380);
    ofDrawBitmapString("duration: " + ofToString(fingerMovie.getPosition()*fingerMovie.getDuration(),2) + "/"+ofToString(fingerMovie.getDuration(),2),20,400);
    ofDrawBitmapString("speed: " + ofToString(fingerMovie.getSpeed(),2),20,420);

    if(fingerMovie.getIsMovieDone()){
        ofSetColor(0xFF0000);
        ofDrawBitmapString("end of movie",20,440);
    }
 */
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
   	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}

    if(key == ' ') {
        buffer->setBufferMode(VB_BUFFERING);
    }
    
    if(key == 'p') {
        buffer->setBufferMode(VB_PASSTHROUGH);
    }

    
    if(key == 'R') {
        buffer->clear();
    }
    
    if(key == '1') {
        buffer->setLoopState(OF_LOOP_NONE);
    } else if(key == '2') {
        buffer->setLoopState(OF_LOOP_NORMAL);
    } else if(key == '3') {
        buffer->setLoopState(OF_LOOP_PALINDROME);
    }
    
    if(key == 'q') {
        buffer->setLoopPointsStart( buffer->getLoopPointsStart()-1 );
    } else if(key == 'w') {
        buffer->setLoopPointsStart( buffer->getLoopPointsStart()+1 );
    } else if(key == 'e') {
        buffer->setLoopPointsEnd( buffer->getLoopPointsEnd()-1 );
    } else if(key == 'r') {
        buffer->setLoopPointsEnd( buffer->getLoopPointsEnd()+1 );
    }
    
    
/*
	switch(key){
        case 'f':
            frameByframe=!frameByframe;
            fingerMovie.setPaused(frameByframe);
        break;
        case OF_KEY_LEFT:
            fingerMovie.previousFrame();
        break;
        case OF_KEY_RIGHT:
            fingerMovie.nextFrame();
        break;
        case '0':
            fingerMovie.firstFrame();
        break;
    }
	*/
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
    int width = ofGetWidth();
    float pct = (float)x / (float)width;
    float speed = pct * 20;
    buffer->setSpeed(speed);
    
    /*
	if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        float speed = (2 * pct - 1) * 5.0f;
        fingerMovie.setSpeed(speed);
	}
	 */
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	/*
	if(!frameByframe){
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        fingerMovie.setPosition(pct);
	}
	 */
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
	
	//interp.insert(ofPoint(x,y));
	
	/*
	if(!frameByframe){
        fingerMovie.setPaused(true);
	}
	 */
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	/*
	if(!frameByframe){
        fingerMovie.setPaused(false);
	}
	 */
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){

}
