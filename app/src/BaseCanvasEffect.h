/*
 *  BaseCanvasEffect.h
 *  livedraw
 *
 *  Created by Christopher P. Baker on 3/6/11.
 *  Copyright 2011 Murmur Labs LLC. All rights reserved.
 *
 */

#ifndef _BASE_CANVAS_EFFECT_H
#define _BASE_CANVAS_EFFECT_H

#include "EnablerInterface.h"

class BaseCanvasEffect : public Enabler {
	
public:
	
	BaseCanvasEffect();
	virtual ~BaseCanvasEffect() = 0;
	
	virtual void begin() = 0;
	virtual void end() = 0;
	
	
	
};


#include "ofxShader.h"

class BaseShaderEffect : public BaseCanvasEffect {
	
public:
	
	
	
	ofxShader shader;

};





#endif
