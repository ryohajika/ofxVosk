#include "ofxVosk.h"

ofxVosk::ofxVosk(){
    b_vosk_init = false;
    vosk_smpl_rate = -1.0;
    model_path = "";
    vosk_model = nullptr;
    vosk_recognizer = nullptr;
    sound_buffer = nullptr;
    bRealtimeCbEnabled = false;
}
ofxVosk::~ofxVosk(){
    std::unique_lock<std::mutex> lock(mutex);
    stopThread();
    condition.notify_one();
    waitForThread(false);
    
    if(b_vosk_init){
        vosk_recognizer_free(vosk_recognizer);
        vosk_model_free(vosk_model);
        vosk_model = nullptr;
        vosk_recognizer = nullptr;
        sound_buffer = nullptr;
        vosk_smpl_buffer.clear();
    }
    ofLogNotice("ofxVosk::~ofxVosk", "Vosk clean up done!");
}

bool ofxVosk::setup(std::string full_path_to_model, float sampling_rate, unsigned buffer_size){
    model_path = full_path_to_model;
    vosk_smpl_rate = sampling_rate;
    vosk_smpl_buffer_size = buffer_size;
    
    if(vosk_smpl_rate < 0.0){
        ofLogError("ofxVosk::setup", "Sampling rate is under 0Hz");
        return false;
    }
    vosk_model = vosk_model_new(full_path_to_model.c_str());
    if(vosk_model == nullptr){
        ofLogError("ofxVosk::setup", "Vosk Model init failed!");
        return false;
    }
    vosk_recognizer = vosk_recognizer_new(vosk_model, vosk_smpl_rate);
    if(vosk_recognizer == nullptr){
        ofLogError("ofxVosk::setup", "Vosk Recognizer init failed!");
        return false;
    }
    ofLogNotice("ofxVosk::setup", "Vosk init finished!");
    b_vosk_init = true;
    this->setThreadName("ofxVoskThread");
    vosk_smpl_buffer.resize(vosk_smpl_buffer_size);
    
    return true;
}
bool ofxVosk::isVoskInitialized(){
    return b_vosk_init;
}
void ofxVosk::setRealtimeResultCallback(bool value){
    bRealtimeCbEnabled = value;
}

void ofxVosk::startRec(){
    halfway_result = "";
    partial_result = "";
    final_result = "";
    startThread();
}
void ofxVosk::stopRec(){
    std::unique_lock<std::mutex> lock(mutex);
    stopThread();
    condition.notify_one();
    
    std::string str(vosk_recognizer_final_result(vosk_recognizer));
    final_result = operator""_json(str.c_str(), str.size());
#ifdef DEBUG_MODE
    cout << str << endl;
#endif
}
bool ofxVosk::isInRecognition(){
    return isThreadRunning();
}
void ofxVosk::update(ofSoundBuffer * input){
    std::unique_lock<std::mutex> lock(mutex);
    sound_buffer = input;
    condition.notify_one();
}
void ofxVosk::threadedFunction(){
    while(isThreadRunning()){
        std::unique_lock<std::mutex> lock(mutex);
        for(std::size_t i=0; i<vosk_smpl_buffer_size; i++){
            vosk_smpl_buffer[i] = sound_buffer->getBuffer()[i] * float(std::numeric_limits<short>::max());
        }
        vosk_final = vosk_recognizer_accept_waveform_s(vosk_recognizer,
                                                       vosk_smpl_buffer.data(),
                                                       vosk_smpl_buffer_size);
        if(vosk_final){
            std::string str(vosk_recognizer_result(vosk_recognizer));
            halfway_result = operator""_json(str.c_str(), str.size());
#ifdef DEBUG_MODE
            cout << vosk_smpl_buffer_size << ", " << str << endl;
#endif
        }else{
            std::string str(vosk_recognizer_partial_result(vosk_recognizer));
            partial_result = operator""_json(str.c_str(), str.size());
            if(bRealtimeCbEnabled){
                std::string msg = this->getPartialResultText();
                ofNotifyEvent(realtime_result_text_evt, msg);
            }
#ifdef DEBUG_MODE
            cout << vosk_smpl_buffer.size() << ", " << str << endl;
#endif
        }
        condition.wait(lock);
    }
}

ofJson ofxVosk::getFinalResultJson(){
    return final_result;
}
std::string ofxVosk::getFinalResultText(){
    return final_result.empty() ? "" : final_result["text"];
}
ofJson ofxVosk::getPartialResultJson(){
    return partial_result;
}
std::string ofxVosk::getPartialResultText(){
    return partial_result.empty() ? "" : partial_result["partial"];
}
ofJson ofxVosk::getResultJson(){
    return halfway_result;
}
std::string ofxVosk::getResultText(){
    return halfway_result.empty() ? "" : halfway_result["text"];
}
