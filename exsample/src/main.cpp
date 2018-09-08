#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    
    ofGLWindowSettings settings;
    settings.setGLVersion(1, 2);
    ofCreateWindow(settings);
    
    ofRunApp(new ofApp());

}
