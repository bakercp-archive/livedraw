#ifndef _CUSTOM_CONTROLLER_OBJECT
#define _CUSTOM_CONTROLLER_OBJECT


//#include "ofMain.h"
//#include "ofxGui.h"


class MyCustomControllerObject {// : public ofxGuiApp {
	
public:
	
	MyCustomControllerObject(ofxGui* gui);
	~MyCustomControllerObject();
	
	void newButtonEvent(const void * sender, int &i);
	void newSliderEvent(const void * sender, int &i);

	ofxGuiPanel* myPanel;
	//ofxGuiSlider* mySlider;
	ofxGuiButton* myButton;
	ofxGuiButton* myOtherButton;
	
private:
	//ofxGui* gui;
		
};

#endif

