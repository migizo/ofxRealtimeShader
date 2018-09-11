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
    string gName = "";
    
    int last_check_time = 0;
    time_t vLast_saved_time;
    time_t fLast_saved_time;
    time_t gLast_saved_time;

    bool isAutoReload = true;
public:
    bool load(string vertName, string fragName, string geomName="") {
        this->vName = vertName;
        this->fName = fragName;
        this->gName = geomName;
        ofShader::load(vName, fName, gName);
    }
    
    void update() {
        if(! isAutoReload) return;
        
        int check_interval = 1000;
        if (ofGetElapsedTimeMillis() - last_check_time > check_interval) {
            last_check_time = ofGetElapsedTimeMillis();

            auto vSaved_time = filesystem::last_write_time(ofToDataPath(this->vName));
            if (vSaved_time != vLast_saved_time) {
                this->load(vName, fName, gName);
                vLast_saved_time = vSaved_time;
            }
            
            auto fSaved_time = filesystem::last_write_time(ofToDataPath(this->fName));
            if (fSaved_time != fLast_saved_time) {
                this->load(vName, fName, gName);
                fLast_saved_time = fSaved_time;
            }
            
            auto gSaved_time = filesystem::last_write_time(ofToDataPath(this->gName));
            if (gSaved_time != gLast_saved_time) {
                this->load(vName, fName, gName);
                gLast_saved_time = gSaved_time;
            }
        }
    }
    
    void setEnable() {
        isAutoReload = true;
    }
    
    void setDisable() {
        isAutoReload = false;
    }
};


#endif /* ofxRealtimeShader_hpp */
