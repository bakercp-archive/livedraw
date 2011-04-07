#ifndef OSC_MANAGER_H
#define OSC_MANAGER_H

//#include "ofMain.h"

#include <map>
#include "ofxOsc.h"
#include "OscNodeListener.h"

// listen on port 5433
#define PORT 5433
#define NUM_MSG_STRINGS 20


using namespace std;

//typedef map <string,OscManager> RootNodeMap;


//--------------------------------------------------------
class OscManager {
	
public:
	
	OscManager();
	~OscManager();
//	void OscManager(int port);
	void setup();
	void update();
	void draw();

	//void setPort(int port);
	
	// get the listeners
	//void registerListener(); // root listeners
	//void unregisterListener();
	
	
private:
	
	
	map<string, OscNodeListener*> rootNodes;
	
	
	ofxOscReceiver	receiver;
	ofTrueTypeFont		font;
	void distributeMessages(); // match and send the messages
	
	
	// listeners // a map of listeners with the root
	
	int mouseX;
	int mouseY;
	string mouseButtonState;
	int				current_msg_string;
	string			msg_strings[NUM_MSG_STRINGS];
	float			timers[NUM_MSG_STRINGS];
	
};

#endif
