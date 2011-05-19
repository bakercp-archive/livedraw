#include "ofMain.h"
#include "livedrawApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 800,600, OF_WINDOW);			// <-------- setup the GL context

	
	livedrawApp* app = new livedrawApp;
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(app);

}
