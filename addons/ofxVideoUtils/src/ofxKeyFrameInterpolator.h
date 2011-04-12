/*
 *  ofxKeyFrameInterpolator.h
 *  bufferedVideoPlayerExample
 *
 *  Created by Christopher P. Baker on 3/15/11.
 *  Copyright 2011 Murmur Labs LLC. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "MSAInterpolator.h"
#include "Vector.h"

#define DEFAULT_NUM_ITEMS 5


class ofxKeyFrameInterpolator : public MSA::Interpolator2D 
{
	
public:
	
	ofxKeyFrameInterpolator();
	ofxKeyFrameInterpolator(ofPoint _startPoint, ofPoint _endPoint);
	
	virtual ~ofxKeyFrameInterpolator();
	void init(ofPoint _startPoint, ofPoint _endPoint);

	void draw();

	void reset(ofPoint _startPoint, ofPoint _endPoint);
	void reset();
	
	void movePoint(int pointIndex, ofPoint newPosition);
	void addPoint(ofPoint _point);	
	void removePoint(ofPoint _point);
	
	ofPoint returnPoint(ofPoint point);
	
	int getIndexToLeft(ofPoint _point);
	void insert(ofPoint _point);
	
    void setLinearInterpolation();
    void setCubicInterpolation();
	
    void setVerbose(bool verbose);
    
    void findArrayPositionForX(float xPosition, int &leftIndex);

    
    
	
private:
	
	float currentTime;
	float currentPosition;
	
	//MSA::Interpolator2D				spline2D;
	//MSA::InterpolationType			interpolationType;
	
	

	vector<MSA::Vec2f>::iterator data_iter;
	vector<float>::iterator dist_iter;

	
	/*
	vector<int> myvector (3,100);
	
	for (it=myvector.begin(); it<myvector.end(); it++)
		cout << " " << *it;
		cout << endl;
	*/
	
	ofPoint startPoint;
	ofPoint endPoint;
};



