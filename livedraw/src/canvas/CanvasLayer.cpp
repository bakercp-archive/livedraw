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
CanvasLayer::CanvasLayer(CanvasLayerManager* _parent, string name, ofPoint pos) : OscNodeListener("/"+name) {
    parent = _parent;
    layerName = name;
    setPosition(pos);
}

//--------------------------------------------------------------
CanvasLayer::CanvasLayer(CanvasLayerManager* _parent, string name) : OscNodeListener("/"+name) {
    parent = _parent;
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
    addChild(&effectsChain); // add the associated effects chain as a child
    
    addCommand("/input");
    addCommand("/mask");
        
    addCommand("/order");
    
    addCommand("/lock");
    addCommand("/solo");
    addCommand("/label");
    
    fbo = new ofFbo();

    fbo->allocate(getTransform()->getWidth(), getTransform()->getHeight());
    
    source = new ofVideoPlayer();
    mask = new ofImage();
}

//--------------------------------------------------------------
bool CanvasLayer::bringFoward() {
    return parent->bringLayerForward(this);
}
//--------------------------------------------------------------
bool CanvasLayer::sendBackward() {
    return parent->sendLayerBackward(this);
}
//--------------------------------------------------------------
bool CanvasLayer::bringToFront() {
    return parent->bringLayerToFront(this);    
}
//--------------------------------------------------------------
bool CanvasLayer::sendToBack() {
    return parent->sendLayerToBack(this);
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
    } else if(isMatch(address, "/order")) {
        
        cout << "IN HERE " << endl;
        
        if(validateOscSignature("[sfi]", m)) {
            if(m.getArgType(0) == OFXOSC_TYPE_STRING) {
                string command = toLower(m.getArgAsString(0));
                if(isMatch(command, "forward")) {
                    bringFoward();
                } else if(isMatch(command,"backward")) {
                    sendBackward();
                } else if(isMatch(command,"front")) {
                    bringToFront();
                } else if(isMatch(command,"back")) {
                    sendToBack();
                }
            } else {
                
                int targetLayer = m.getArgAsInt32(0);
                
                cout << "moving to " << targetLayer << endl;
                
            }

            
        }
    } else if(isMatch(address, "/lock")) {
        if(validateOscSignature("[fi]", m)) {
            int val = m.getArgAsInt32(0);
            locked = (val == 1);
            parent->setLayerLock(this, locked);
        }
    } else if(isMatch(address, "/solo")) {
        if(validateOscSignature("[fi]", m)) {
            int val = m.getArgAsInt32(0);
            solo = (val == 1);
            parent->setLayerSolo(this, solo);
        }
    } else if(isMatch(address, "/label")) {
        if(validateOscSignature("[fi][fi][fi][fi]?", m)) {
            label.r = m.getArgAsFloat(0);
            label.g = m.getArgAsFloat(1);
            label.b = m.getArgAsFloat(2);
            if(m.getNumArgs() < 4) {
                label.a = m.getArgAsFloat(3);
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