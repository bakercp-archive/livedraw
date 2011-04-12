#include "ofxVideoBufferPlayer.h"
#include "ofUtils.h"


//--------------------------------------------------------------
ofxVideoBufferPlayer::ofxVideoBufferPlayer(int width, int height, int imageType, float fps, int size)
    : ofxVideoBuffer(width,height,imageType,fps,size)
{
    currentFrame = 0;
    playForward = true;
    
    speed = 1;
    lastFramePush = FLT_MIN;
    frameDuration = 1.0f / fps * getSpeed(); // invert! *in ms
    lastFrameFraction = 0.0f;
    
    clearLoopPoints();
    setLoopState(OF_LOOP_PALINDROME);
    
}

//--------------------------------------------------------------
ofxVideoBufferPlayer::~ofxVideoBufferPlayer() {}



//--------------------------------------------------------------
void ofxVideoBufferPlayer::update() {
    
    int maxFrame = getLoopPointsEnd();   // already accounts for loop enabled
    if(maxFrame <= 0) return;
    int minFrame = getLoopPointsStart(); // already accounts for loop enabled
    
    float now = ofGetElapsedTimef();

    // if this is the first time
    if(lastFramePush == FLT_MIN) {
        lastFramePush = now;
    }
    
    float elapsedTime = (now - lastFramePush); // elapsedtime seconds
    
    float numFramesToPush = 0;
    float frameDuration = 0;
    
    if(getSpeed() != 0) {
        
        frameDuration = 1 / (bufferFps * getSpeed());
        numFramesToPush = elapsedTime / frameDuration;
        numFramesToPush += lastFrameFraction; // add on any leftovers from last frame
        
        lastFrameFraction = floor(numFramesToPush); // set to whole part
        lastFrameFraction = (numFramesToPush - lastFrameFraction); // save fractional part for next time
        numFramesToPush -= lastFrameFraction;
        
    }
        
    // we mark time if there is a frame to push
    if(numFramesToPush != 0) { 
        lastFramePush = now;

        if(loopState == OF_LOOP_NONE) {
            currentFrame += numFramesToPush; // may not be w/in range 
            currentFrame = CLAMP(currentFrame, minFrame, maxFrame);
    
        } else if(loopState == OF_LOOP_NORMAL) {
            currentFrame += numFramesToPush; // may not be w/in range 
            // check range and loop appropraitely
            if(currentFrame > maxFrame) {
                currentFrame = minFrame + (currentFrame - maxFrame) % (maxFrame - minFrame);
            } else if(currentFrame < minFrame) {
                currentFrame = maxFrame - (minFrame - currentFrame) % (maxFrame - minFrame);
            }

        } else if(loopState == OF_LOOP_PALINDROME) {

            // directionality is controld not by speed vector but by palindrome state
            int absNumFramesToPush = ABS(numFramesToPush);
            
            currentFrame += (playForward) ? absNumFramesToPush : -absNumFramesToPush;
            
            // we are outside of the range!
            if(currentFrame < minFrame || currentFrame > maxFrame) {
                 
                int overshoot = 0;

                if(currentFrame > maxFrame) {
                    overshoot = (currentFrame - maxFrame);
                } else {
                    overshoot = (minFrame - currentFrame);
                }
                
                // recursively reduce overshoot by folding
                int loopDuration = (maxFrame - minFrame);
                while (overshoot > loopDuration) {
                    overshoot -= loopDuration;
                    playForward = !playForward;
                }
                 
                if(playForward) {
                    currentFrame = (maxFrame - overshoot);
                } else {
                    currentFrame = (minFrame + overshoot); 
                }

                playForward = !playForward;
                
            } else {
                // just stick with it!
            }
        
        }
    }
}
                   
//--------------------------------------------------------------
void ofxVideoBufferPlayer::draw(int x, int y) {
    int frame = (bufferMode == VB_PASSTHROUGH) ? 0 : currentFrame;
    buffer[frame].draw(x,y);
}

//--------------------------------------------------------------
// frame based loop control
void ofxVideoBufferPlayer::setLoopPoints(int start, int end) {
    setLoopPointsStart(start);
    setLoopPointsEnd(end);
}

//--------------------------------------------------------------
bool ofxVideoBufferPlayer::setLoopPointsStart(int frame) {
    // make sure it is a valid start point
    // left condition, right condition
    if(frame >= 0 && frame < getLoopPointsEnd()) {
        loopPointsStart = frame;
        return true;
    }
    
    return false;
}

//--------------------------------------------------------------
bool ofxVideoBufferPlayer::setLoopPointsEnd(int frame) {
    // make sure it is a valid end point
    // left condition, right condition
    if(frame > getLoopPointsStart() && frame < bufferPosition) { // make sure we have buffered this
        loopPointsEnd = frame;
        return true;
    }    
    
    return false;
}

//--------------------------------------------------------------
int ofxVideoBufferPlayer::getLoopPointsStart() {
        return (loopPointsStart > -1) ? loopPointsStart : 0;
}

//--------------------------------------------------------------
int ofxVideoBufferPlayer::getLoopPointsEnd() {
    return (loopPointsEnd > -1) ? loopPointsEnd : (bufferPosition - 1);
}

//--------------------------------------------------------------
// normalized loop points
void ofxVideoBufferPlayer::setLoopPointsNorm(float start, float end) {
    setLoopPointsStartNorm(start);
    setLoopPointsEndNorm(end);
}

//--------------------------------------------------------------
void ofxVideoBufferPlayer::setLoopPointsStartNorm(int pct) {
    int l0 = (int)ofMap(pct, 0, 1, 0, bufferPosition - 1, true); // clamp it!
    setLoopPointsStart(l0);
}

//--------------------------------------------------------------
void ofxVideoBufferPlayer::setLoopPointsEndNorm(int pct) {
    int l0 = (int)ofMap(pct, 0, 1, 0, bufferPosition - 1, true); // clamp it!
    setLoopPointsEnd(l0);
}

//--------------------------------------------------------------
float ofxVideoBufferPlayer::getLoopPointsStartNorm() {
    return ofMap(loopPointsStart, 0, bufferPosition - 1, 0, 1);
}

//--------------------------------------------------------------
float ofxVideoBufferPlayer::getLoopPointsEndNorm() {
    return ofMap(getLoopPointsEnd(), 0, bufferPosition - 1, 0, 1);
}

//--------------------------------------------------------------
// frame based positioning
void ofxVideoBufferPlayer::setPosition(int frame) {
    currentFrame = (frame % bufferPosition); // be friendly 
}

//--------------------------------------------------------------
int ofxVideoBufferPlayer::getNumFramesInLoop() {
    return getLoopPointsEnd() - getLoopPointsStart();
}

//--------------------------------------------------------------
void ofxVideoBufferPlayer::setPositionInLoop(int frame) {
    int pos = frame % getNumFramesInLoop(); 
    setPosition(loopPointsStart + pos);
}

//--------------------------------------------------------------
// normalized positioning
void ofxVideoBufferPlayer::setPositionNorm(float pct) {
    int l0 = (int)ofMap(pct, 0, 1, 0, bufferPosition - 1, true); // clamp it!
    setPosition(l0);
}

//--------------------------------------------------------------
int ofxVideoBufferPlayer::getPosition() {
    return currentFrame;
}

//--------------------------------------------------------------
float ofxVideoBufferPlayer::getPositionNorm() {
    return currentFrame / (bufferPosition - 1);
}

//--------------------------------------------------------------
void ofxVideoBufferPlayer::setPositionInLoop(float pct) {
    int pos = (int)(pct * getNumFramesInLoop());
    setPositionInLoop(pos);
}

//--------------------------------------------------------------
void ofxVideoBufferPlayer::clear() {
    ofxVideoBuffer::clear(); // super clear 
    clearLoopPoints();
}

//--------------------------------------------------------------
// clear loops!
void ofxVideoBufferPlayer::clearLoopPoints() {
    loopPointsStart = -1;
    loopPointsEnd = -1;
}

//--------------------------------------------------------------
// loop modes!
void ofxVideoBufferPlayer::setLoopState(int state) {
    if(state == OF_LOOP_PALINDROME) playForward = (getSpeed() > 0); // reset
    loopState = state;
}

//--------------------------------------------------------------
void ofxVideoBufferPlayer::setSpeed(float _speed) {
    speed = _speed;
}

//--------------------------------------------------------------
float ofxVideoBufferPlayer::getSpeed() {
    // TODO: this speed setting could pull from a more complex speed graph
    return speed;
}