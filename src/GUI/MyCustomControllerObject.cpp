/*
 *  MyCustomControllerObject.cpp
 *  ofxGui_Example
 *
 *  Created by Christopher P. Baker on 1/31/11.
 *  Copyright 2011 Murmur Labs LLC. All rights reserved.
 *
 */

#include "MyCustomControllerObject.h"

MyCustomControllerObject::MyCustomControllerObject(ofxGui* gui) {
	this->gui = gui; // set it

	//ofxGuiPanel	*buttonsAndMatrix = gui->addPanel("butt", 200, 200);

	///myOtherButton = buttonsAndMatrix->addButtonTrigger("trigbutt");
	//myButton = buttonsAndMatrix->addButtonSwitch("swtichbutt");
	
	//ofxGuiPanel	*other = gui->addPanel("xxxx", 280, 230);

	
	ofxGuiPanel	*q = gui->addPanel("1:(Y/Y/N)", 500, 250);
	q->isDragMoveable = true;
	q->isDropSender = true;
	q->isDropReceiver = false;
	
	ofxGuiPanel	*r = gui->addPanel("2:(N/N/N)", 540, 230);
	r->isDragMoveable = false;
	r->isDropSender = false;
	r->isDropReceiver = false;
	
	 
	ofxGuiPanel	*dragTarget = gui->addPanel("3:(Y/N/Y)", 100, 100);
	dragTarget->set(ofxPoint2f(100,100), 200, 200);
	dragTarget->isDragMoveable = true;
	dragTarget->isDropSender = false;
	dragTarget->isDropReceiver = true;
	
	//cout << "Adding listeners "<< endl;
    //ofAddListener(myButton->ofxGuiButtonEvent, this, &MyCustomControllerObject::newButtonEvent);
	//ofAddListener(myOtherButton->ofxGuiButtonEvent, this, &MyCustomControllerObject::newButtonEvent);
	
}
MyCustomControllerObject::~MyCustomControllerObject() {
	cout << "removing listeners " << endl;
    //ofRemoveListener(myButton->genericOfxGuiEvent, this, &MyCustomControllerObject::newButtonEvent);
	//ofRemoveListener(myOtherButton->genericOfxGuiEvent, this, &MyCustomControllerObject::newButtonEvent);
}


void MyCustomControllerObject::newButtonEvent(const void * sender, int &i) {
	cout << "got a button method!" << endl;
}

void MyCustomControllerObject::newSliderEvent(const void * sender, int &i) {	
	cout << "got a slide event " << endl;
}

