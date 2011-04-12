/*
 *  CanvasLayerTransform.h
 *  livedraw
 *
 *  Created by Christopher P. Baker on 1/1/11.
 *  Copyright 2011 Murmur Labs LLC. All rights reserved.
 *
 */

#pragma once 

#include "ofMain.h"
#include "ofEvents.h"
#include "EnablerInterface.h"
#include "ofxLimitedPoint.h"

class CanvasLayerTransform : public Enabler {
	
public:
	
	CanvasLayerTransform(ofPoint _position, ofPoint _anchorPoint, ofPoint _rotation) {
		position = ofxLimitedPoint(_position);
		anchorPoint = ofxLimitedPoint(_anchorPoint);
		rotation = ofxLimitedPoint(_rotation);
		
		opacity = 1;
	}

	CanvasLayerTransform(ofPoint _position) {
		position = ofxLimitedPoint(_position);
		opacity = 1;
	}
	
	CanvasLayerTransform() {
		opacity = 1;
	};
	
	virtual ~CanvasLayerTransform();

	ofPoint getPosition() { return position.getLimitedPoint(); };
	void setPosition(ofPoint p) {this->position.set(p.x, p.y, p.z);onSetPosition();}
	void setPositionX(float x) {this->position.x = x; onSetPosition();}
	void setPositionY(float y) {this->position.y = y; onSetPosition();}
	void setPositionZ(float z) {this->position.z = z; onSetPosition();}
	
	ofPoint getAnchorPoint() { return anchorPoint.getLimitedPoint(); };
	void setAnchorPoint(ofPoint p) {this->anchorPoint.set(p.x, p.y, p.z); onSetAnchorPoint();}
	void setAnchorPointX(float x) {this->anchorPoint.x = x; onSetAnchorPoint();}
	void setAnchorPointY(float y) {this->anchorPoint.y = y; onSetAnchorPoint();}
	void setAnchorPointZ(float z) {this->anchorPoint.z = z; onSetAnchorPoint();}
	
	ofPoint getRotation()	 { return rotation.getLimitedPoint(); };
	void setRotation(ofPoint p) {this->rotation.set(p.x, p.y, p.z);onSetRotation();}
	void setRotationX(float x) {this->rotation.x = x; onSetRotation();}
	void setRotationY(float y) {this->rotation.y = y; onSetRotation();}
	void setRotationZ(float z) {this->rotation.z = z; onSetRotation();}
	
	ofPoint getOrientation()	 { return orientation.getLimitedPoint(); };
	void setOrientation(ofPoint p) {this->orientation.set(p.x, p.y, p.z);onSetOrientation();}
	void setOrientationX(float x) {this->orientation.x = x; onSetOrientation();}
	void setOrientationY(float y) {this->orientation.y = y; onSetOrientation();}
	void setOrientationZ(float z) {this->orientation.z = z; onSetOrientation();}
	
	ofPoint getScale()	 { return scale.getLimitedPoint(); };
	void setScale(ofPoint p) {this->scale.set(p.x, p.y, p.z);onSetScale();}
	void setScaleX(float x) {this->scale.x = x; onSetScale();}
	void setScaleY(float y) {this->scale.y = y; onSetScale();}
	void setScaleZ(float z) {this->scale.z = z; onSetScale();}
	
	float getOpacity()	{ return opacity;}
	void setOpacity(float o) { this->opacity = o; onSetOpacity();};
	
	void onSetPosition() {
		//ofNotifyEvent(newPositionEvent,&position,this);
	}

	void onSetAnchorPoint() {
		//ofNotifyEvent(newAnchorPointEvent,&anchorPoint,this);
	}

	void onSetRotation() {
		//ofNotifyEvent(newRotationEvent, &rotation, this);
	}
	
	void onSetOrientation() {
		//ofNotifyEvent(newRotationEvent, &rotation, this);
	}
	
	
	void onSetScale() {
		//ofNotifyEvent(newRotationEvent, &rotation, this);
	}

	void onSetOpacity() {
		//ofNotifyEvent(newOpacityEvent, &opacity, this);
	}
	
	void onSetPositionLimit() {
		//ofNotifyEvent(newOpacityEvent, &position, this);
	}
	
	void onSetAnchorPointLimit() {
		//ofNotifyEvent(newOpacityEvent, &anchorPoint, this);
	}

	void onSetRotationLimit() {
		//ofNotifyEvent(newOpacityEvent, &rotation, this);
	}
	
	void onEnabled() {
		ofLog(OF_LOG_NOTICE, "Transform enabled");
	}
	
	void onDisabled() {
		ofLog(OF_LOG_NOTICE, "Transform diabled");
	}
	
//protected:
	
	ofxLimitedPoint position;
	ofxLimitedPoint anchorPoint;
	ofxLimitedPoint rotation;
	
	// A NOTE ON ORIENTATION 
	// http://help.adobe.com/en_US/aftereffects/cs/using/WS3878526689cb91655866c1103906c6dea-7e33a.html
	
	ofxLimitedPoint orientation;
	ofxLimitedPoint scale;

	// materials options ... ?
	
	float opacity;
	
	/*
	ofEvent<ofxLimitedPoint*> newPositionEvent;
	ofEvent<ofxLimitedPoint*> newAnchorPointEvent;
	ofEvent<ofxLimitedPoint*> newRotationEvent;
	ofEvent<float>	newOpacityEvent;
	
	ofEvent<ofxLimitedPoint*> newPositionLimitEvent;
	ofEvent<ofxLimitedPoint*> newAnchorPointLimitEvent;
	ofEvent<ofxLimitedPoint*> newRotationLimitEvent;
	*/
};
