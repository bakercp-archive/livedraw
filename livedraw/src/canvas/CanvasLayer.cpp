/*
 *  CanvasLayer.cpp
 *  livedraw
 *
 *  Created by Christopher P. Baker on 12/3/10.
 *  Copyright 2010 Murmur Labs LLC. All rights reserved.
 *
 */

#include "CanvasLayer.h"

//--------------------------------------------------------------
CanvasLayer::CanvasLayer(string name, ofPoint pos) : OscNodeListener("/"+name) {
    layerName = name;
    setPosition(pos);
}

//--------------------------------------------------------------
CanvasLayer::CanvasLayer(string name) : OscNodeListener("/"+name) {
    layerName = name;
}

//--------------------------------------------------------------
CanvasLayer::~CanvasLayer() {
    if(source != NULL) delete source;
    if(mask != NULL) delete mask;
    if(fbo != NULL) delete fbo;
}

//--------------------------------------------------------------
void CanvasLayer::setAssetManager(AssetManager* _assetManager) {
    assetManager = _assetManager;
}

//--------------------------------------------------------------
void CanvasLayer::setEffectsManager(EffectsManager* _effectsManager) {
    effectsManager = _effectsManager;
    effectsChain.setEffectsManager(effectsManager);
}

//--------------------------------------------------------------

void CanvasLayer::setup() {
    
    effectsChain.setup();
    
    solo = false;
    locked = false;
    
    // fbo
    useMSAA = true;
    
    getTransform()->setWidth(640);
    getTransform()->setHeight(480); // standard canvas layer size
    
    addChild(&transform); // add the transform as an OSC child
    addChild(&effectsChain);
    
    addCommand("/input");
    addCommand("/mask"); 

    fbo = new ofFbo();

    fbo->allocate(getTransform()->getWidth(), getTransform()->getHeight());
    
    source = new ofVideoPlayer();
    mask = new ofImage();
}

//--------------------------------------------------------------
void CanvasLayer::setPosition(ofPoint pos) {
    getTransform()->setPosition(pos);
}

//--------------------------------------------------------------
void CanvasLayer::setSize(int width, int height) {
    getTransform()->setSize(ofPoint(width,height));
}

//--------------------------------------------------------------
void CanvasLayer::setRectangle(ofRectangle rect) {
    getTransform()->setPosition(ofPoint(rect.x,rect.y));
    getTransform()->setSize(ofPoint(rect.width,rect.height));
}

//--------------------------------------------------------------
void CanvasLayer::processOscMessage(string address, ofxOscMessage& m) {
    
    cout << "layer out " << address << endl;
    
    if(isMatch(address, "/input")) {
        if(validateOscSignature("s",m)) {
            VideoMediaAsset* src = NULL;
            string assetId = m.getArgAsString(0);
            src = assetManager->getVideoAsset(assetId);
            
            if(src != NULL) {
                setSource(src);
            } else {
                ofLog(OF_LOG_ERROR, "CanvasLayer: [" + assetId + "] does not exist."); 
            }
        }
        
    } else if(isMatch(address, "/mask")) {
        if(validateOscSignature("s",m)) {
            ImageMediaAsset* src = NULL;
            string assetId = m.getArgAsString(0);
            src = assetManager->getImageAsset(assetId);
            
            if(src != NULL) {
                setMask(src);
            } else {
                ofLog(OF_LOG_ERROR, "CanvasLayer: [" + assetId + "] does not exist."); 
            }
        }
    }
    
}



//--------------------------------------------------------------
void CanvasLayer::setSource(VideoMediaAsset* src) {
    if(source->isLoaded()) {
        delete source;
        source = new ofVideoPlayer();
    }
    
    source->loadMovie(src->getAssetURI().toString());
    source->play();
}

//--------------------------------------------------------------
void CanvasLayer::setMask(ImageMediaAsset* src) {
    mask->loadImage(src->getAssetURI().toString());
}

//--------------------------------------------------------------
string CanvasLayer::getName() {
    return layerName;
}

//--------------------------------------------------------------
void CanvasLayer::setName(string _name) {
    layerName = _name;
    setNodeName("/"+layerName);
}

//--------------------------------------------------------------
void CanvasLayer::update()
{
    source->update();
}

//--------------------------------------------------------------
void CanvasLayer::onEnabled() {}

//--------------------------------------------------------------
void CanvasLayer::onDisabled() {}