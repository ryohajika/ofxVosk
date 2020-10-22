#pragma once

#include "ofMain.h"
#include <atomic>
#include "vosk_api.h"

//#define DEBUG_MODE 1

class ofxVosk : public ofThread {
    public:
        ofxVosk();
        ~ofxVosk();

        bool setup(std::string full_path_to_model, float sampling_rate, unsigned buffer_size);
        bool isVoskInitialized();
        void setRealtimeResultCallback(bool value);

        void startRec();
        void stopRec();
        bool isInRecognition();
        void clearBuffer();
        void update(ofSoundBuffer * input);

        ofJson getFinalResultJson();
        std::string getFinalResultText();
        ofJson getPartialResultJson();
        std::string getPartialResultText();
        ofJson getResultJson();
        std::string getResultText();
    
        ofEvent<std::string> realtime_result_text_evt;

    private:
        void threadedFunction();
    
        VoskModel * vosk_model;
        VoskRecognizer * vosk_recognizer;
        std::string model_path;
        bool b_vosk_init;
        float vosk_smpl_rate;
    
        ofSoundBuffer * sound_buffer;
        std::vector<short> vosk_smpl_buffer;
        unsigned vosk_smpl_buffer_size;
        std::condition_variable condition;
        
        int vosk_final;
        ofJson halfway_result;
        ofJson partial_result;
        ofJson final_result;
        bool bRealtimeCbEnabled;
};
