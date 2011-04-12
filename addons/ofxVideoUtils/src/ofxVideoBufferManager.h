//
//  ofxVideoBufferManager.h
//  bufferedVideoPlayerExample
//
//  Created by Christopher P. Baker on 3/29/11.
//  Copyright 2011 Murmur Labs LLC. All rights reserved.
//

#pragma once

#include "ofMain.h"

#include "ofxVideoBuffer.h"


class ofxVideoBufferManager {
    
public:
    
    ofxVideoBuffer* bufferVideo(string videoFile) {
        
        ofVideoPlayer vid;
        vid.loadMovie(videoFile);
        
        int numFrames = vid.getTotalNumFrames();
        
        //ofxVideoBuffer* buffer = new ofxVideoBuffer(numFrames);
    }
    
    
private:
    
    vector<ofxVideoBuffer*> buffers;
    
};