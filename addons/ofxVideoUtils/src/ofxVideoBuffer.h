/*
 *  ofxVideoBuffer.h
 *  bufferedVideoPlayerExample
 *
 *  Created by Christopher P. Baker on 3/13/11.
 *  Copyright 2011 Murmur Labs LLC. All rights reserved.
 *
 */

// TODO : could this be a just a typedef? 

#pragma once

#include "RingBuffer.h"
#include "ofMain.h"

#define DEFAULT_BUFFER_SIZE 1
#define DEFAULT_EMPTY_VALUE NULL

enum VideoBufferMode {
    VB_WAITING,
    VB_BUFFERING,
    VB_PASSTHROUGH
};


class ofxVideoBuffer {
	
public:
	
	ofxVideoBuffer(int width, int height, int imageType, float fps, int size) {
        init(width, height, imageType, fps, size);
    };

	virtual ~ofxVideoBuffer() {
        ofLog(OF_LOG_VERBOSE, "ofxVideoBuffer: Releasing Buffer");
        delete[] buffer;
    };    
    
    void clear() {
        bufferPosition = 0;
        bufferMode = VB_WAITING;
    }
    
    // returns was buffered
    bool add(unsigned char * data, int w, int h, int imageType) {
        if(bufferMode == VB_BUFFERING) {
            if(bufferPosition < bufferSize) {
                buffer[bufferPosition].setFromPixels(data,w,h,imageType);
                bufferPosition++; 
            }
            return true;
        
        } else if(bufferMode == VB_PASSTHROUGH) {
            buffer[0].setFromPixels(data,w,h,imageType);
            return false;
        }

        return false;
    }
    
    
    int getFrameByPosition(float i) {
        i = CLAMP(i,0,1);
        int frameNum = (int)(i * bufferSize);
        
    }
    
    ofImage get(int index) {
        index = CLAMP(index, 0, bufferPosition);
        return buffer[index];//getPlayheadOffset(index)];
    }
    
    /*
    
    int getPlayheadOffset(int i) {
        int indexOffset = 0;
        int proposedLocation = bufferPosition + CLAMP(i,-bufferSize,bufferSize);
        
        
        // off the end
        if( proposedLocation < bufferSize && proposedLocation >= 0) {
            return proposedLocation;
        } else if (proposedLocation < 0) {
            
            
        } else {
            int diff = proposedLocation - bufferSize;
            return diff;
        }
    }
     */
    
    void setBufferMode(VideoBufferMode mode) {
        bufferMode = mode;
    }
    
    VideoBufferMode getBufferMode() {
        return bufferMode;
    }
    
    bool isBuffering() {
        return bufferMode == VB_BUFFERING;
    }
    
    bool isWaiting() {
        return bufferMode == VB_WAITING;
    }

    bool isPassthrough() {
        return bufferMode == VB_PASSTHROUGH;
    }
        
    bool isBufferFull() {
        return bufferPosition == bufferSize;
    }
    
    // returns the current count
	int getNumBufferedFrames() {
        return bufferPosition;
	}


	
protected:
	
    void init(int width, int height, int type, float fps, int size) {
        bufferWidth = width;
        bufferHeight = height;
        bufferFps = fps;
        bufferSize = size;
        imageType = type;
        
        // init the array and allocate
        buffer = new ofImage[bufferSize];

        for(int i = 0; i < bufferSize; i++) {
            buffer[i] = ofImage(); // empty
            buffer[i].allocate(bufferWidth,bufferHeight,imageType);
        }
        
        clear();
        
    }
		
    int bufferWidth, bufferHeight;
    int imageType;
    
    ofImage* buffer;    // the buffer array
    int bufferSize;     // the maximum size of the buffer
    int bufferPosition; // the current size of the buffer
    
    VideoBufferMode bufferMode;     // is this currently buffering
	
    float bufferFps;
};




