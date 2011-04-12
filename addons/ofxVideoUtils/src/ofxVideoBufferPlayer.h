/* christopher baker */
/* http://christopherbaker.net */

#pragma once

#include "ofMain.h"
#include "ofxVideoBuffer.h"

class ofxVideoBufferPlayer : public ofxVideoBuffer {

public:
	
    ofxVideoBufferPlayer(int width, int height, int imageType, float fps, int size); 
       
    
    virtual ~ofxVideoBufferPlayer();
    
	void update(); // like idle

    void draw(int x, int y); // straight up!
    
    // frame based loop control
	void setLoopPoints(int start, int end);
    bool setLoopPointsStart(int frame);
    bool setLoopPointsEnd(int frame);

	int getLoopPointsStart();
    int getLoopPointsEnd();

    // normalized loop points
    void setLoopPointsNorm(float start, float end);
    void setLoopPointsStartNorm(int pct);
    void setLoopPointsEndNorm(int pct);
    
	float getLoopPointsStartNorm();
    float getLoopPointsEndNorm();

    // frame based positioning
    void setPosition(int frame);
    void setPositionInLoop(int frame);
    
    // getting position
    int getPosition();
    float getPositionNorm();
    
    // normalized positioning
    void setPositionNorm(float pct);
    void setPositionInLoop(float pct);
    
    // clear loops!
    void clearLoopPoints();

    int getNumFramesInLoop();
    
    void clear();
    
    // loop modes!
    //OF_LOOP_NONE
    //OF_LOOP_NORMAL
    //OF_LOOP_PALINDROME
    void setLoopState(int state);
	
    void  setSpeed(float speed);
    float getSpeed();
    
private:
    
    float speed; 
    bool  playForward; // forward or backward (palindrome)
    float lastFramePush;   // ms
    float frameDuration; // ms
    float lastFrameFraction;
    
    int currentFrame;
    int loopState;
    
	//bool loopPointsEnabled;
	int loopPointsStart; // INCLUSIVE
	int loopPointsEnd;   // INCLUSIVE
	
    // our buffer
	//ofxVideoBuffer* buffer;
	
};

