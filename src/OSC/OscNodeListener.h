#ifndef OSC_NODE_LISTENER_H
#define OSC_NODE_LISTENER_H

#include <map>
#include <set>


#include "ofxOsc.h"
//#include "OscManager.h"

class OscNodeListener {

public:
	
	// constructor should have a link to the parent or null
	//OscNodeListener();//OscManager* _manager, OscNodeListener* parent) {
					  //		manager = _manager;
					  //		manager.register(this);
					  //	};
	
    //virtual ~OscNodeListener() {}
    virtual void processOscMessage(string address, ofxOscMessage& m) = 0;
	
	
	
	// set parent
	// register child
	
	// string getOSCaddress();
	
	// a recursive function to build the address from a single node
	/*
	OscManager* getOscManager() { return manager; } ;
	void setOscManager(OscManager* manager) {
		this->manager = manager;
	};
	 */
	
private:
	
	set<string> registeredListeners; // if it is NOT in here, then it must be in the other?
	map<string, OscNodeListener*> children;
	
	// parent node
	// xyz 
	// children
	// 
	
	//OscManager* manager;
	
	
};

#endif /* INCLUDED_OSCNODELISTENER_H */