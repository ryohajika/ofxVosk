# [ofxVosk](https://github.com/ryohajika/ofxVosk) is an [openFrameworks](https://github.com/openframeworks/openFrameworks) addon of [vosk-api](https://github.com/alphacep/vosk-api) to use automatic speech recognition (ASR) functionality based on [Kaldi](https://github.com/kaldi-asr/kaldi) project.

Vosk is an open source speech recognition toolkit which is based on the Kaldi-ASR project. With this addon, you can add automatic speech recognition functionality to your openFrameworks app (which doesn't require an internet connection, supports various platform including RPi!)

## License
Both [Vosk](https://github.com/alphacep/vosk-api) and [Kaldi](https://github.com/kaldi-asr/kaldi) are licensed under Apache-2.0 license. Since this project including those header files from vosk-api project, this project is also licensed under Apache-2.0 license.

## Supported platform (so far)
- MacOSX 10.14 (Mojave), oF 0.11.0 (release)

## How to use this?
### OSX (example)
- You will get all the libraries and source code by cloning this repo from command line.
` git clone https://github.com/ryohajika/ofxVosk `
- Go to [VoskAPI's website](https://alphacephei.com/vosk/models) and download one of these the models available on the website  you want to use. (in the example project I used "vosk-model-small-en-us-0.3")
- Unpack the zipped model file and place it to `examples/bin/data`
- Run the project in Xcode
