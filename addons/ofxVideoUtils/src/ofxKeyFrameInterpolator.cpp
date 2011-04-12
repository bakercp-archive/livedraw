/*
 *  ofxKeyFrameInterpolator.cpp
 *  bufferedVideoPlayerExample
 *
 *  Created by Christopher P. Baker on 3/15/11.
 *  Copyright 2011 Murmur Labs LLC. All rights reserved.
 *
 */

#include "ofxKeyFrameInterpolator.h"

//--------------------------------------------------------------
ofxKeyFrameInterpolator::ofxKeyFrameInterpolator() {
    init(ofPoint(100,100), ofPoint(400,100));
	
}

//--------------------------------------------------------------
ofxKeyFrameInterpolator::ofxKeyFrameInterpolator(ofPoint _startPoint, ofPoint _endPoint) {		
    init(_startPoint, _endPoint);
}


//--------------------------------------------------------------
ofxKeyFrameInterpolator::~ofxKeyFrameInterpolator() {
    // killin it
}

//--------------------------------------------------------------
void ofxKeyFrameInterpolator::init(ofPoint _startPoint, ofPoint _endPoint) {
    reserve(DEFAULT_NUM_ITEMS);		// not essential, but good habit if you know how big its gonna be
    
    setVerbose(true);
    //		setLinearInterpolation();
    
    setCubicInterpolation();
    
    MSA::Vec2f sp = MSA::Vec2f(startPoint.x, startPoint.y);
    MSA::Vec2f ep = MSA::Vec2f(endPoint.x, endPoint.y);
    
    
    clear();
    push_back(sp);
    push_back(ep);
    setUseLength(false);
    
}



//--------------------------------------------------------------
void ofxKeyFrameInterpolator::draw() {
    int dotSize = 20;
    int lineWidth = 4;
    int numItems = size();
    
    /*
     int numSteps = numItems;//100;
     
     float spacing = 1.0/numSteps;
     if(lineWidth) {
     glLineWidth(lineWidth);
     
     GLfloat vertex[numSteps * 2];
     int i=0;
     for(float f=0; f<1; f+= spacing) {
     MSA::Vec2f v			= sampleAt(f);
     vertex[i*2]		= v.x;
     vertex[(i*2)+1] = v.y;
     i++;
     }
     glEnableClientState(GL_VERTEX_ARRAY);
     glVertexPointer(2, GL_FLOAT, 0, vertex);
     glDrawArrays(GL_LINE_STRIP, 0, numSteps);
     }
     
     if(dotSize) {
     glPointSize(dotSize);
     GLfloat vertex[numSteps * 2];
     int i=0;
     for(float f=0; f<1; f+= spacing) {
     MSA::Vec2f v			= sampleAt(f);
     vertex[i*2]		= v.x;
     vertex[(i*2)+1] = v.y;
     i++;
     }
     glEnableClientState(GL_VERTEX_ARRAY);
     glVertexPointer(2, GL_FLOAT, 0, vertex);
     glDrawArrays(GL_POINTS, 0, numSteps);
     }
     
     */
    
    
    if(lineWidth) {
        glLineWidth(lineWidth);
        GLfloat vertex[numItems * 2];
        for(int i=0; i<numItems; i++) {
            vertex[i*2]		= at(i).x;
            vertex[(i*2)+1] = at(i).y;
        }
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, vertex);
        glDrawArrays(GL_LINE_STRIP, 0, numItems);
    }
    
    if(dotSize) {
        glPointSize(dotSize);
        GLfloat vertex[numItems * 2];
        for(int i=0; i<numItems; i++) {
            vertex[i*2]		= at(i).x;
            vertex[(i*2)+1] = at(i).y;
        }
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, vertex);
        glDrawArrays(GL_POINTS, 0, numItems);
    }
    
    
}


//--------------------------------------------------------------
void ofxKeyFrameInterpolator::reset(ofPoint _startPoint, ofPoint _endPoint) {
    startPoint = _startPoint;	// save this for later
    endPoint = _endPoint;		// save this for later
    
    reset();
}

//--------------------------------------------------------------
void ofxKeyFrameInterpolator::reset() {
    
    init(startPoint,endPoint);
    
}


//--------------------------------------------------------------
void ofxKeyFrameInterpolator::movePoint(int pointIndex, ofPoint newPosition) {
    // find the old point
    // set it to the new point
    // should be limited by the first or last point and the indexes to the left and the right
    
}

//--------------------------------------------------------------
void ofxKeyFrameInterpolator::addPoint(ofPoint _point) {
    // this should intelligentyly insert, rather than just add the point
    // not permitted to add a point before or after
    
    
    
}

//--------------------------------------------------------------
void ofxKeyFrameInterpolator::removePoint(ofPoint _point) {
    // this should inteligently remove the point and shift everything around
    // not permitted to delete the first or last points
}



ofPoint ofxKeyFrameInterpolator::returnPoint(ofPoint point) {
    
    MSA::Vec2f v = _data[getIndexToLeft(point)];
    return ofPoint(v.x,v.y);
    
}


//--------------------------------------------------------------
int ofxKeyFrameInterpolator::getIndexToLeft(ofPoint _point) {
    MSA::Vec2f s = _data.front();
    MSA::Vec2f e = _data.back();
    
    float t = ofNormalize(_point.x, s.x, e.x);
    
    float mu;
    int leftIndex;
    
    //findPosition(t, leftIndex, mu);
    
    findArrayPositionForX(_point.x, leftIndex);

    //cout << t << " " << leftIndex << endl;;
    
    return leftIndex;
}

//--------------------------------------------------------------
void ofxKeyFrameInterpolator::insert(ofPoint _point) {
    MSA::Vec2f s = _data.front();
    MSA::Vec2f e = _data.back();
    
    
    _point.x = CLAMP(_point.x, s.x, e.x);
    
    int i = getIndexToLeft(_point);
    
    data_iter = _data.begin();
    data_iter = _data.insert ( data_iter+i+1 ,MSA::Vec2f(_point.x, _point.y) );
    
    if(getUseLength()) {
        // TODO: this could just update from insert position forward? // if linear yes, if not no
        dist_iter = _dist.begin();
        dist_iter = _dist.insert ( dist_iter+i+1 ,-1 ); // must be updated
        updateAllLengths();
    }
    
    
    /*
     _data.push_back(newData);						// add data
     
     if(getUseLength()) {
     float segmentLength;
     float totalLength;
     
     if(size() > 1) {
     //				T distT		= newData - _data.at(prevIndex);	// get offset to previous node
     //				float dist		= lengthOf(distT);					// actual Length to node
     
     segmentLength	= calcSegmentLength(size()-1);
     totalLength		= segmentLength + _dist.at(size()-2);
     } else {
     segmentLength	= 0;
     totalLength		= 0;
     }
     
     _dist.push_back(totalLength);
     
     //				if(verbose) printf("segment length = %f | total length = %f\n", segmentLength, totalLength);
     }
     */
}


//--------------------------------------------------------------
void ofxKeyFrameInterpolator::setLinearInterpolation() {
    setInterpolation(MSA::kInterpolationLinear);
}

//--------------------------------------------------------------
void ofxKeyFrameInterpolator::setCubicInterpolation() {
    setInterpolation(MSA::kInterpolationCubic);
}

//--------------------------------------------------------------
void ofxKeyFrameInterpolator::setVerbose(bool verbose) {
    verbose = verbose;
}

//--------------------------------------------------------------
void ofxKeyFrameInterpolator::findArrayPositionForX(float xPosition, int &leftIndex) {
    int numItems = size();
    
    leftIndex = numItems - 2; // it can never go past the last one
    
    for(int i = 1; i < numItems-1; i++) {
        MSA::Vec2f pnt = at(i);
        
        if(xPosition < pnt.x) {
            leftIndex = i - 1;
            break;
        }
        
    }
}


