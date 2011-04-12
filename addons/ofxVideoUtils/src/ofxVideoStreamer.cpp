#include "ofxVideoStreamer.h"
#include "ofUtils.h"




//--------------------------------------------------------------------
ofxVideoStreamer::ofxVideoStreamer(){
/*
	// common
	bIsFrameNew				= false;
	bVerbose 				= false;
	bGrabberInited 			= false;
	bUseTexture				= true;
	bChooseDevice			= false;
	deviceID				= 0;
	width 					= 320;	// default setting
	height 					= 240;	// default setting
	pixels					= NULL;
	attemptFramerate		= -1;
 */
}


//--------------------------------------------------------------------
ofxVideoStreamer::~ofxVideoStreamer(){

	close();

}


//--------------------------------------------------------------------
void ofxVideoStreamer::setVerbose(bool bTalkToMe){
	bVerbose = bTalkToMe;
}

//---------------------------------------------------------------------------
unsigned char * ofxVideoStreamer::getPixels(){
//	return gstUtils.getPixels();
}

//------------------------------------
//for getting a reference to the texture
ofTexture & ofxVideoStreamer::getTextureReference(){
	
	if(!tex.bAllocated() ){
		ofLog(OF_LOG_WARNING, "ofVideoGrabber - getTextureReference - texture is not allocated");
	}
	return tex;
}

//---------------------------------------------------------------------------
bool  ofxVideoStreamer::isFrameNew(){
	return bIsFrameNew;
}

//--------------------------------------------------------------------
void ofxVideoStreamer::update(){
	grabFrame();
}

//--------------------------------------------------------------------
void ofxVideoStreamer::grabFrame(){

	/*
	if (bGrabberInited){
		gstUtils.update();
		bIsFrameNew = gstUtils.isFrameNew();
		if(bIsFrameNew) {
			if (bUseTexture){
				tex.loadData(gstUtils.getPixels(), width, height, GL_RGB);
			}
		}
	}
	 */

}

//--------------------------------------------------------------------
void ofxVideoStreamer::close(){
	
//	gstUtils.close();
	tex.clear();

}

//--------------------------------------------------------------------
bool ofxVideoStreamer::initStreamer(int w, int h, bool setUseTexture){
	bUseTexture = setUseTexture;

/*
		gstUtils.setDeviceID(deviceID);

		if(gstUtils.initGrabber(w,h,attemptFramerate)){
			width 	= w;
			height 	= h;
			if (bUseTexture){
				// create the texture, set the pixels to black and
				// upload them to the texture (so at least we see nothing black the callback)
				tex.allocate(width,height,GL_RGB);
				tex.loadData(gstUtils.getPixels(), width, height, GL_RGB);
			}
			bGrabberInited = true;
			ofLog(OF_LOG_VERBOSE, "ofVideoGrabber: initied");
		}else{
			bGrabberInited = false;
			ofLog(OF_LOG_ERROR, "ofVideoGrabber: couldn't init");
		}
		return bGrabberInited;

*/
	
}

//------------------------------------
void ofxVideoStreamer::setUseTexture(bool bUse){
	bUseTexture = bUse;
}

//we could cap these values - but it might be more useful
//to be able to set anchor points outside the image

//----------------------------------------------------------
void ofxVideoStreamer::setAnchorPercent(float xPct, float yPct){
    if (bUseTexture)tex.setAnchorPercent(xPct, yPct);
}

//----------------------------------------------------------
void ofxVideoStreamer::setAnchorPoint(int x, int y){
    if (bUseTexture)tex.setAnchorPoint(x, y);
}

//----------------------------------------------------------
void ofxVideoStreamer::resetAnchor(){
   	if (bUseTexture)tex.resetAnchor();
}

//------------------------------------
void ofxVideoStreamer::draw(float _x, float _y, float _w, float _h){
	if (bUseTexture){
		tex.draw(_x, _y, _w, _h);
	}
}

//------------------------------------
void ofxVideoStreamer::draw(float _x, float _y){
	draw(_x, _y, (float)width, (float)height);
}


//----------------------------------------------------------
float ofxVideoStreamer::getHeight(){
	return (float)height;
}

//----------------------------------------------------------
float ofxVideoStreamer::getWidth(){
	return (float)width;
}
