#pragma once

#include <map>
#include <set>

#include "ofMain.h"
#include "ofxOsc.h"
#include "OscNodeListener.h"
#include "Poco/RegularExpression.h"
#include "Poco/String.h"

extern "C" {    
    #include "osc_match.h"
}

using namespace std;
using Poco::RegularExpression;
using Poco::toUpper;
using Poco::toLower;
using Poco::icompare;

class OscNodeListener {

public:
	
    OscNodeListener() {
        parent = NULL;
        nodeName = "/";
    }
    
    OscNodeListener(string _nodeName) {
        nodeName = _nodeName;
    }

	OscNodeListener(OscNodeListener* _parent, string _nodeName) {
        parent = _parent;
        nodeName = _nodeName;
    }
    
    virtual ~OscNodeListener() {}
    
    // the address here is the remaining bit of the address, as it is processed and pruned
    virtual void processOscMessage(string pattern, ofxOscMessage& m) = 0;
	
    
    
    void routeOscMessage(string pattern, ofxOscMessage& m) {
        
        
        ofLog(OF_LOG_VERBOSE, "OscNodeListener: " + getNodeName() + " processing : " +  m.getAddress());
        
        
        int pattrOffset,addrOffset,matchResult;

        char* _pattern = (char*)pattern.c_str();
        char* _thisAddress = (char*)nodeName.c_str();

        matchResult = osc_match(_pattern, _thisAddress, &pattrOffset, &addrOffset);
         
        //cout << m.getAddress() << "<<< " << endl;
        
        if(matchResult == 0) {
            ofLog(OF_LOG_VERBOSE, "OscNodeListener: No match for: " + m.getAddress());
            return;
        } else if(matchResult == OSC_MATCH_ADDRESS_COMPLETE) {
            pattern = pattern.substr(pattrOffset);
            
            if(hasCommand(pattern)) {// || children.size() <= 0) {
                ofLog(OF_LOG_VERBOSE, "\t\t\t" + getNodeName() + " had the command : " +  m.getAddress());
                processOscMessage(pattern, m);
            } else {
                for(int i = 0; i < children.size(); i++) { 
                    children[i]->routeOscMessage(pattern, m);
                }
            }
            
            // otherwise, it gets ignored

        } else if(matchResult == OSC_MATCH_PATTERN_COMPLETE) {
            cout << "PATTERN COMPLETE ++ PROCESSING." << endl;
            processOscMessage(pattern, m);
        } else if(matchResult == OSC_MATCH_ADDRESS_AND_PATTERN_COMPLETE) {
           cout << "ADDRESS AND PATTERN COMPLETE : PERFECT MATCH ++ PROCESSING" << endl;
            processOscMessage(pattern, m);
        } else {
            ofLog(OF_LOG_ERROR, "OscNodeListener: Unknown osc_match result.");
        }
         
                
    }
    
    void setParent(OscNodeListener* _parent) {
        parent = _parent;
    }
    
    OscNodeListener* getParent() {
        return parent;
    }
    
    // TODO: this doesn't seem very efficient ... must be a better way ...
    vector<OscNodeListener*> getSiblings() {
        
        vector<OscNodeListener*> siblings;

        
        if(parent != NULL) {
            vector<OscNodeListener*> allChildrenFromParent = parent->getChildren();
            vector<OscNodeListener*>::iterator it;
            
            // iterator to vector element:
            it = find (allChildrenFromParent.begin(), allChildrenFromParent.end(), this);

            if(it != allChildrenFromParent.end()) {
                allChildrenFromParent.erase(it);
            }   
            
            siblings = allChildrenFromParent;
            
            return siblings;
            
        } else {
            return siblings;
        }
        

        
    }
    
    // recursively locate the root node
    OscNodeListener* getRoot() {
        return parent != NULL ? parent->getRoot() : parent;
    }
    
    // currently broken
    /*
    void getFullOscNodeAddress(string &fullAddress) {
        // if it hasn't been cached yet
        if(parent != NULL) {
            getFullOscNodeAddress(fullAddress);
        } else {
            // nothing
        }
        fullAddress = nodeName + fullAddress;
    }
     */
    
    void setNodeName(string _nodeName) {
        nodeName = _nodeName;
    }
    
    string getNodeName() {
        return nodeName;
    }
    
    
    vector<OscNodeListener*> getChildren() {
        return children;
    }
    
    void addChild(OscNodeListener* child) {
        // TODO: should this be auto sorted:: std::sort
        child->setParent(this);
        children.push_back(child);
    }
    
    bool removeChild(OscNodeListener* child) {
        vector<OscNodeListener*>::iterator it;
        
        // iterator to vector element:
        it = find (children.begin(), children.end(), child);
        
        if(it != children.end()) {
            //it->setParent(NULL); // TODO: is this a problem?
            children.erase(it);
            return true;
        } else {
            return false;
        }
        
    }
    
    bool hasCommand(string _command) {
        vector<string>::iterator it;
        // iterator to vector element:
        it = find (commands.begin(), commands.end(), _command);
        return it != commands.end();
    }
    
    void addCommand(string _command) {
        commands.push_back(_command);
    }
    
    bool removeCommand(string _command) {
        vector<string>::iterator it;
        
        // iterator to vector element:
        it = find (commands.begin(), commands.end(), _command);
        
        if(it != commands.end()) {
            commands.erase(it);
            return true;
        } else {
            return false;
        }    
    }
    
    
    bool isMatch(string s0, string s1) {
        return icompare(s0,s1) == 0;
    }
    
    bool validateOscSignature(string signature, ofxOscMessage& m) {
        
        string mSignature = "";
        // make the signature
        for(int i=0; i < m.getNumArgs(); i++) {
            mSignature+=m.getArgTypeName(i).at(0);
        }

        RegularExpression re(signature);
        bool match = re.match(mSignature);
        
        if(!match) {
            ofLog(OF_LOG_ERROR, "Signature: " + signature + " did not match mSignature= " + mSignature);
        }
        
        return match;
        
        
        /*

         // signature code
         // S : string (strict!)
         // f : float (not strict, can be an int)
         // F : float (strict, must be an int)
         // i : int (not strict, can be a float, but will be cast)
         // I : int (strict, must be an int)

         if(signature.length() != m.getNumArgs()) {
            for(int i=0; i < m.getNumArgs(); i++) {
                int t = m.getArgType(i);
                char c = signature[i];
                
                if(c == 's' && t != OFXOSC_TYPE_STRING) {
                    ofLog(OF_LOG_ERROR, "OscNodeListener: ValidateOscSignature Failed: expected [STRING] at position " 
                          + ofToString(i) + " [" +m.getAddress() + "]");
                    return false;
                }
                
                if((c == 'f' || c == 'i') && (t == OFXOSC_TYPE_INT32 || t == OFXOSC_TYPE_FLOAT)) {
                    ofLog(OF_LOG_ERROR, "OscNodeListener: ValidateOscSignature Failed: expected [float or int] at position " 
                          + ofToString(i) + " [" +m.getAddress() + "]");
                    return false;
                } 
                if(c == 'F' && t != OFXOSC_TYPE_FLOAT) {
                    ofLog(OF_LOG_ERROR, "OscNodeListener: ValidateOscSignature Failed: expected [FLOAT] at position " 
                          + ofToString(i) + " [" +m.getAddress() + "]");
                    return false;
                }
                
                if(c == 'I' && t != OFXOSC_TYPE_INT32) {
                    ofLog(OF_LOG_ERROR, "OscNodeListener: ValidateOscSignature Failed: expected [INT] at position " 
                          + ofToString(i) + " [" +m.getAddress() + "]");
                 return false;   
                }
            }
            
            return true;
            
        } else {
            ofLog(OF_LOG_ERROR, "OscNodeListener: ValidateOscSignature Failed: invalid # args. " + m.getAddress());
            return false;
        }
        */
        
        
        
    }
    
    
protected:
	
    string nodeName;
    
    OscNodeListener* parent;
    vector<OscNodeListener*> children;
    vector<string> commands;
	
	
	
	
};
