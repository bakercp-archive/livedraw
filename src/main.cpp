#include "ofMain.h"
#include "livedrawApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 2048,768, OF_WINDOW);			// <-------- setup the GL context

	
	livedrawApp* app = new livedrawApp;
	
	//ofxFenster fenster;
	//fenster.init(app);
	
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(app);

}
