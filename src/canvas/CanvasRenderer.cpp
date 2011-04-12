/*
 *  CanvasRenderer.cpp
 *  livedraw
 *
 *  Created by Christopher P. Baker on 12/3/10.
 *  Copyright 2010 Murmur Labs LLC. All rights reserved.
 *
 */

#include "CanvasRenderer.h"

void CanvasRenderer::update() {
	for(int i = 0; i < layers.size(); i++) {
		layers[i]->update();
	}
}

void CanvasRenderer::draw() {
	
	for(int i = 0; i < layers.size(); i++) {
		
		CanvasLayer* layer = layers[i];
		
		
		CanvasLayerTransform* xform = layer->getTransform();
		ofPoint p = xform->getPosition();
		ofPoint r = xform->getRotation();
		ofPoint s = xform->getScale();
		
		glPushMatrix();
		
		glTranslated(p.x, p.y, p.z);
		glRotated(r.x, 1, 0, 0);
		glRotated(r.y, 0, 1, 0);
		glRotated(r.z, 0, 0, 1);
		glScaled(s.x, s.y, s.z);

		// do effects
		
		// get image reference and draw it
		//layer->getSource()->getImage()->draw(0,0);
		
		glPopMatrix();
		
		
		
	}
}

void CanvasRenderer::processOscMessage(string address, ofxOscMessage& m) {
    
}

