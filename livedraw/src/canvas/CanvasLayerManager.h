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

class CanvasLayer;

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

	CanvasLayer* newLayer(string layerName, ofPoint point);
	bool deleteLayer(string layerName);

    bool hasLayer(string name);

    CanvasLayer* getLayerByName(string name);
    
    int  getLayerIndex(string layerName);
    
    
    
    
    
    
    bool bringLayerForward(CanvasLayer* layer);
    bool sendLayerBackward(CanvasLayer* layer);
    bool sendLayerToBack(CanvasLayer* layer);
    bool bringLayerToFront(CanvasLayer* layer);
    bool sendLayerTo(CanvasLayer* layer, int targetLayerIndex);
    
    void setLayerSolo(CanvasLayer* layer, bool solo);
    void setLayerLock(CanvasLayer* layer, bool lock);
    
    
private:
    AssetManager* assetManager;
    EffectsManager* effectsManager;
    
    vector<CanvasLayer*>::iterator it;
    vector<CanvasLayer*> layers;
    
    vector<CanvasLayer*> renderTree;
    

};