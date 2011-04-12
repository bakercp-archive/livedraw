#pragma once

#include "ofConstants.h"
#include "ofTexture.h"
#include "ofGraphics.h"
#include "ofTypes.h"

//#include "ofGstUtils.h"

class ofxVideoStreamer : public ofBaseVideo {

	public :

		ofxVideoStreamer();
		virtual ~ofxVideoStreamer(); // ofBaseVideo

		bool 			isFrameNew(); // ofBaseVideo
		void			close(); // ofBaseVideo
	
		bool			initStreamer(int w, int h, bool bTexture = true);

	
	void			grabFrame();
		unsigned char 	* getPixels();
		ofTexture &		getTextureReference();
		void 			setVerbose(bool bTalkToMe);
		void 			setUseTexture(bool bUse);
		void 			draw(float x, float y, float w, float h);
		void 			draw(float x, float y);
		void			update();

	//the anchor is the point the image is drawn around.
	//this can be useful if you want to rotate an image around a particular point.
	void			setAnchorPercent(float xPct, float yPct);	//set the anchor as a percentage of the image width/height ( 0.0-1.0 range )
	void			setAnchorPoint(int x, int y);				//set the anchor point in pixels
	void			resetAnchor();								//resets the anchor to (0, 0)
	
	float 			getHeight();
	float 			getWidth();

		int			height;
		int			width;

	protected:

		bool					bUseTexture;
		ofTexture 				tex;
		bool 					bVerbose;
		bool 					bStreamerInited;
		int						frameRate;
		bool 					bIsFrameNew;

		//--------------------------------- quicktime

		//ofGstUtils				gstUtils;

};


