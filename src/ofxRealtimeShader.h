//
//  ofxRealtimeShader.hpp
//  Created by migizo on 2018/09/08.
//
//

#ifndef ofxRealtimeShader_hpp
#define ofxRealtimeShader_hpp

#include "ofMain.h"

class ofxRealtimeShader : public ofShader{
private:
    string vName = "";
    string fName = "";
    
    int last_check_time = 0;
    time_t vLast_saved_time;
    time_t fLast_saved_time;

public:
    bool load(string vertName, string fragName, string geomName="") {
        this->vName = vertName;
        this->fName = fragName;
        ofShader::load(vertName, fragName);
    }
    void update() {
        int check_interval = 1000;
        if (ofGetElapsedTimeMillis() - last_check_time > check_interval) {
            auto vSaved_time = filesystem::last_write_time(ofToDataPath(this->vName));
            if (vSaved_time != vLast_saved_time) {
                this->load(vName, fName);
                vLast_saved_time = vSaved_time;
            }
            
            auto fSaved_time = filesystem::last_write_time(ofToDataPath(this->fName));
            if (fSaved_time != fLast_saved_time) {
                this->load(vName, fName);
                fLast_saved_time = fSaved_time;
            }
            last_check_time = ofGetElapsedTimeMillis();
        }
    }
};


#endif /* ofxRealtimeShader_hpp */
