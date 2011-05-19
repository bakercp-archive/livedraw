//
//  CanvasLayerManager.h
//  livedraw
//
//  Created by Christopher P. Baker on 5/17/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "OscNodeListener.h"
#include "CanvasLayer.h"
#include "AssetManager.h"
#include "EffectsManager.h"

class CanvasLayerManager : public OscNodeListener {
public:
    
    CanvasLayerManager();
    virtual ~CanvasLayerManager();
    
    void setup();
    void update();
    void draw();
    
    void setAssetManager(AssetManager* _assetManager);
    void setEffectsManager(EffectsManager* _effectsManager);
    
    void processOscMessage(string pattern, ofxOscMessage& m);

	// /livedraw/canvas/layer/new      LAYER_NAME [X_POSITION Y_POSITION [Z_POSITION]]
	CanvasLayer* newLayer(string layerName, ofPoint point);
	bool deleteLayer(string layerName);
    bool hasLayer(string name);

    CanvasLayer* getLayerByName(string name);
    
    
private:
    AssetManager* assetManager;
    EffectsManager* effectsManager;
    
    vector<CanvasLayer*> layers;

};