/*
 *  CanvasLayer.h
 *  livedraw
 *
 *  Created by Christopher P. Baker on 12/3/10.
 *  Copyright 2010 Murmur Labs LLC. All rights reserved.
 *
 */

#pragma once

#include "OscNodeListener.h"
#include "BaseMediaSource.h"
#include "ofTexture.h"
#include "CanvasLayerTransform.h"
#include "BaseCanvasEffect.h"
#include "EnablerInterface.h"
#include "Samplers.h"

class CanvasLayer : public OscNodeListener, public Enabler {
	
public:
	
	CanvasLayer();
	virtual ~CanvasLayer();
	
	void setup();
	void update();
	// void draw(); // they can't draw themselves.  the view has to draw them ...
	
	void setSource(MediaSampler* source);
	void setMask(MediaSampler* mask);

	MediaSampler* getSource();
	MediaSampler* getMask();
	
	CanvasLayerTransform* getTransform() { return &transform; };
	
	
	bool addEffect(BaseCanvasEffect* effect);
	bool removeEffect(BaseCanvasEffect* effect);
	
	bool enableEffect(BaseCanvasEffect* effect);
	bool disableEffect(BaseCanvasEffect* effect);
	
	void pullEffectForward(BaseCanvasEffect* effect);
	void pushEffectBack(BaseCanvasEffect* effect);
	
	void sendEffectToFront(BaseCanvasEffect* effect);
	void sendEffectToBack(BaseCanvasEffect* effect);
	
	vector<BaseCanvasEffect*> getEffectsChain() { return effects;};

	// settings	
	bool isSolo() {return solo;};
	bool setSolo(bool solo) {this->solo = solo;};

	bool isLocked() {return locked;};
	bool setLocked(bool locked) {this->locked = locked;};
	
	
private:
	
	MediaSampler* source;
	MediaSampler* maskSource;


	// Masker compositer;
	// width / height are all taken from the source
	CanvasLayerTransform transform;
	vector<BaseCanvasEffect*> effects;
	
	bool solo;
	bool locked;
	
	// -> should this be in the gui?
	//ofColor labelColor;
	
	
	
};