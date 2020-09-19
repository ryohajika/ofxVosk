#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int bufferSize = 256;
    
    sound_stream.printDeviceList();
    ofSoundStreamSettings settings;
    auto devices = sound_stream.getDeviceList();
    cout << devices[2].name << endl;
    settings.setApi(ofSoundDevice::Api::OSX_CORE);
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 1;
    //settings.numBuffers = 2;
    settings.bufferSize = bufferSize;
    sound_stream.setup(settings);
    bSoundStreaming = true;
    
    vosk.setup(ofFilePath::getAbsolutePath("vosk-model-small-en-us-0.3"), 44100, bufferSize);
    result = "";
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    if(bSoundStreaming){
        ofBackground(ofColor::blue);
    }else{
        ofBackground(ofColor::black);
    }
    
    if(vosk.isInRecognition()){
        ofPushStyle();
            ofSetColor(ofColor::green);
            ofDrawCircle(256, 256, 50);
        ofPopStyle();
    }else{
        ofPushStyle();
            ofSetColor(ofColor::red);
            ofDrawCircle(256, 256, 50);
        ofPopStyle();
    }
    ofDrawBitmapStringHighlight(result, 50, 50);
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
    audio_buf = input;
    vosk.update(&audio_buf);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 's'){
        if(bSoundStreaming){
            sound_stream.stop();
            bSoundStreaming = false;
        }else{
            sound_stream.start();
            bSoundStreaming = true;
        }
    }
    if(key == 'f'){
        if(vosk.isInRecognition()){
            vosk.stopRec();
            result = vosk.getFinalResultText();
            for(std::size_t i=0; i<result.size(); i+=30){
                result.insert(result.begin()+i, '\n');
            }
        }else{
            vosk.startRec();
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
