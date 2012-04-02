#pragma once

#include "ofMain.h"
#include "OscManager.h"
#include "ControllerManager.h"
#include "GuiManager.h"
#include "AssetManager.h"
#include "CanvasRenderer.h"
#include "SessionManager.h"
//#include "ofxGui.h"
//#include "MyCustomControllerObject.h"
#include "EffectsManager.h"

#define PORT 5433


//--------------------------------------------------------
class livedrawApp : public ofBaseApp { //, public ofxFensterListener {

public:

    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);		

private:


    OscManager      oscManager;
    AssetManager    assetManager;
    EffectsManager  effectsManager;
    
    CanvasRenderer  canvas;
        
    SessionManager  sessionManager;
    GuiManager      guiManager;

};
