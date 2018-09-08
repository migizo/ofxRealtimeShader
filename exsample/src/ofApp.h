#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxRealtimeShader.h"

class ofApp : public ofBaseApp{
    
public:
    //    void mouseDragged(int x, int y, int button);
    //    void mousePressed(int x, int y, int button);
    //    void mouseReleased(int x, int y, int button);

    //    void windowResized(int w, int h);

    
    
    ofxPanel gui;
    ofParameterGroup param;
    ofParameter<float> test_value_01;
    ofParameter<float> test_value_02;
    ofParameter<float> test_value_03;
    ofParameter<float> test_value_04;
    bool isDrawInfo = true;
    
    ofxRealtimeShader shader;
    
    
    const float INFO_DRAW_OFFSET = 20;
    
    void setupInfo() {
        param.add(test_value_01.set("test_value_01", 0.0f, 0.0f, 1.0f));
        param.add(test_value_02.set("test_value_02", 0.0f, 0.0f, 1.0f));
        param.add(test_value_03.set("test_value_03", 0.0f, 0.0f, 1.0f));
        param.add(test_value_04.set("test_value_04", 0.0f, 0.0f, 1.0f));
        gui.setup(param);
        gui.setPosition(ofGetWidth() - (gui.getWidth() + INFO_DRAW_OFFSET), 0);
    }
    void drawInfo() {
        ofPushStyle();
        ofSetColor(ofColor::white);
        gui.draw();

        ofSetColor(ofColor::green);
        string str;
        str += "FPS     : "    + ofToString(ofGetFrameRate()) + "\n";
        str += "MOUSE   : "  + ofToString(ofGetMouseX(), 2, 4, 0) + ", " + ofToString(ofGetMouseY(), 2, 4, 0) + "\n";
        ofDrawBitmapString(str, INFO_DRAW_OFFSET, INFO_DRAW_OFFSET);
        ofPopStyle();
    }
    
    void setup() override {
        ofSetFrameRate(30);
        ofSetVerticalSync(true);
        ofBackground(0);
        setupInfo();
        
        shader.load("shader/shader.vert", "shader/shader.frag");
    }
    
    void update() override{
        shader.update();
    }
    
    void draw() override{
        ofVec2f res = ofVec2f(ofGetWidth(), ofGetHeight());
        shader.begin();
        shader.setUniform1f("test_value_01",    test_value_01);
        shader.setUniform1f("test_value_02",    test_value_02);
        shader.setUniform1f("test_value_03",    test_value_03);
        shader.setUniform1f("test_value_04",    test_value_04);
        shader.setUniform1f("time",             ofGetElapsedTimef());
        shader.setUniform1f("millis",           ofGetElapsedTimeMillis());
        shader.setUniform2f("res",              ofGetWidth(), ofGetHeight());
        shader.setUniform2f("mouse",            ofGetMouseX(), ofGetMouseX());
        
        
        ofDrawRectangle(0, 0, res.x, res.y);
        shader.end();
        
        
        if (isDrawInfo) drawInfo();
    }
    
    void keyReleased(int key) override {
        if (key == 'g') isDrawInfo = !isDrawInfo;
    }

};
