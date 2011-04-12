/*
 *  AxisCameraPatch.h
 *  AxisCameraPatch
 *
 *  Created by Christopher Wright on 11/5/08.
 *  Copyright (c) 2008 Kosada Incorporated. All rights reserved.
 *
 */
//#include <Cocoa/Cocoa.h>

#include "ofMain.h"


class AxisCameraPatch{

	public:
		void setSize(int width, int height);
		void loadRequest();
		void cancelLoad();
		void end();
		void execute(string camUrl, int width, int height);
		unsigned char * getPixels();
		bool getReceiveAnyData();
	float getFps();
	
		int imageWidth;
		int imageHeight;
	bool isNewFrame();
//	bool newFrame;
		
	private:
		unsigned char* RGB_Axispixels;
		int fps;
		long lastFrame;
		
	
	
};



//http://thebends.googlecode.com/svn/trunk/ypeer/peers.cpp

