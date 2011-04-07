/*
 *  CanvasRenderer.h
 *  livedraw
 *
 *  Created by Christopher P. Baker on 12/3/10.
 *  Copyright 2010 Murmur Labs LLC. All rights reserved.
 *
 */

// a collection of convas layers
// communication between layers

#ifndef _CANVAS_RENDERER_H
#define _CANVAS_RENDERER_H

#include "OscNodeListener.h"
#include "CanvasLayer.h"

class CanvasRenderer : public OscNodeListener {
	
public:
	
	CanvasRenderer();
	~CanvasRenderer();

	void update();
	void draw();
	
	
	
	// /livedraw/canvas/fullscreen
	void setFullscreen(bool fullscreen);
	bool getFullscreen() {return fullscreen;};
	
	// /livedraw/canvas/background
	void setBackground(ofColor color);
	ofColor getBackground() { return bgColor; };

	// /livedraw/canvas/size
	void setSize(int width, int height);

	// /livedraw/canvas/position
	void setPosition(int x, int y);
	
	// /livedraw/canvas/fps
	void setFPS(int fps);
	
	
	
	// /livedraw/canvas/layer/new      LAYER_NAME [X_POSITION Y_POSITION [Z_POSITION]]
	CanvasLayer* newLayer(string layerName, ofPoint point);
	bool deleteLayer(string layerName, ofPoint point);
	
	void soloLayer(CanvasLayer* layer);
	void removeSolo(CanvasLayer* layer);
	void lockLayer(CanvasLayer* layer); // send in 
	void unloackLayer(CanvasLayer* layer);
	
	// /livedraw/canvas/layer/delete   LAYER_NAME
	
	
	
private:
	vector<CanvasLayer*> layers;
	
	// canvas group is a kind of canvas layer
	
	
	
	
	ofColor		bgColor; // 
	ofRectangle	rectangle; // position of the render window
	
	bool		fullscreen;
	
	
};

#endif
