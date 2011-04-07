#ifndef _LIVEDRAW_APP
#define _LIVEDRAW_APP


#include "ofMain.h"
#include "ofxFenster.h"

#include "OscManager.h"
#include "ControllerManager.h"
#include "AssetManager.h"
#include "CanvasRenderer.h"
#include "ofxDirList.h"
#include "ofxGui.h"
#include "MyCustomControllerObject.h"
#include "ofxFbo.h"

//--------------------------------------------------------
class livedrawApp : public ofBaseApp, public ofxFensterListener {

	public:

		void setup();
	
		// gui window
		void update();
		void draw();

		// render window
		void fensterDraw();
		void fensterUpdate();
	
	
		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);


		// render window
		void fensterKeyPressed  (int key);
		void fensterKeyReleased(int key);
		void fensterMouseMoved(int x, int y );
		void fensterMouseDragged(int x, int y, int button);
		void fensterMousePressed(int x, int y, int button);
		void fensterMouseReleased(int x, int y, int button);
		void fensterWindowResized(int w, int h);
	
	
	
	private:
	ofImage of;
	
		//ofxFbo	fbo;
		//ContollerManager	controller;
		//CanvasRenderer	canvas;
		AssetManager	assetManager;
		int nImages, nVideos;
		ofxDirList aaa;
		
		void newButtonEvent(const void * sender, int & i);
		
		ofxGui* gui;
		
		MyCustomControllerObject* guiObj;
	
	
};

#endif
