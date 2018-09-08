#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxRealtimeShader.h"

class ofApp : public ofBaseApp{
    
public:
    const float INFO_DRAW_OFFSET = 20;

    ofxPanel gui;
    ofParameterGroup param;
    ofParameter<float> test_value_01;
    ofParameter<float> test_value_02;
    ofParameter<float> test_value_03;
    ofParameter<float> test_value_04;
    bool isDrawInfo = true;
    
    ofxRealtimeShader shader;
    bool isEnableShader = true;
    
    ofVboMesh vboMesh;
    ofEasyCam cam;
    
    void setupInfo() {
        param.add(test_value_01.set("test_value_01", 0.0f, 0.0f, 1.0f));
        param.add(test_value_02.set("test_value_02", 0.0f, 0.0f, 1.0f));
        param.add(test_value_03.set("test_value_03", 0.0f, 0.0f, 1.0f));
        param.add(test_value_04.set("test_value_04", 0.0f, 0.0f, 1.0f));
        gui.setup(param);
        gui.setPosition(ofGetWidth() - (gui.getWidth() + INFO_DRAW_OFFSET), 0);
    }
    
    void drawInfo() {
        ofDisableDepthTest();

        //gui
        ofPushStyle();
        ofSetColor(ofColor::white);
        gui.draw();
        
        //info text
        ofSetColor(ofColor::green);
        string str;
        str += "FPS     : "    + ofToString(ofGetFrameRate()) + "\n";
        str += "MOUSE   : "  + ofToString(ofGetMouseX(), 2, 4, 0) + ", " + ofToString(ofGetMouseY(), 2, 4, 0) + "\n";
        ofDrawBitmapString(str, INFO_DRAW_OFFSET, INFO_DRAW_OFFSET);
        ofPopStyle();
        
        ofEnableDepthTest();
    }
    
    void setup() override {
        ofSetLogLevel(OF_LOG_VERBOSE);

        ofSetFrameRate(30);
        ofSetVerticalSync(true);
        ofBackground(50, 50, 50);
        ofEnableAlphaBlending();
        setupInfo();
        
        shader.setGeometryInputType(GL_POINTS);
        shader.setGeometryOutputType(GL_LINE_STRIP);
        shader.setGeometryOutputCount(2);
        shader.load("shader/shader.vert", "shader/shader.frag", "shader/shader.geom");
        cout << "maximum number of supported vertices " << shader.getGeometryMaxOutputCount() << endl;
        vboMesh.setMode(OF_PRIMITIVE_POINTS);

        float r = ofGetHeight()/2;
        for(int i=0; i<100; i++) {
            vboMesh.addVertex(ofPoint(ofRandomf() * r, ofRandomf() * r, ofRandomf() * r));
            vboMesh.addColor(ofColor(255 * i / 100, 255 * (1.0f -i / 100), 255));
        }
        ofEnableDepthTest();
        
        cam.setNearClip(0);
        cam.setFarClip(1500);
    }
    
    void update() override{
        shader.update();
    }
    
    void draw() override{
        cam.begin();

        ofVec2f res = ofVec2f(ofGetWidth(), ofGetHeight());
        if (isEnableShader) {
            shader.begin();
            shader.setUniform1f("test_value_01",    test_value_01);
            shader.setUniform1f("test_value_02",    test_value_02);
            shader.setUniform1f("test_value_03",    test_value_03);
            shader.setUniform1f("test_value_04",    test_value_04);
            shader.setUniform1f("time",             ofGetElapsedTimef());
            shader.setUniform1f("millis",           ofGetElapsedTimeMillis());
            shader.setUniform2f("res",              res.x, res.y);
            shader.setUniform2f("mouse",            mouseX, mouseY);
        }
        vboMesh.draw();
        if (isEnableShader) shader.end();
        
        cam.end();
        if (isDrawInfo) drawInfo();
    }
    
    void keyReleased(int key) override {
        if (key == 'g') isDrawInfo = !isDrawInfo;
        if (key == 's') isEnableShader = !isEnableShader;
    }

};
