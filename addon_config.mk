meta:
	ADDON_NAME = ofxVosk
	ADDON_DESCRIPTION = Addon for automatic voice recognition using vosk-api with Kaldi as a backend 
	ADDON_AUTHOR = Ryo Hajika 
	ADDON_TAGS = "ASR" "voice recognition" "kaldi" "vosk" "sphinx"
	ADDON_URL = https://github.com/ryohajika/ofxVosk

common:
	# dependencies with other addons, a list of them separated by spaces 
	# or use += in several lines
	#ADDON_DEPENDENCIES = ofxOpenCv
	
	# include search paths, this will be usually parsed from the file system
	# but if the addon or addon libraries need special search paths they can be
	# specified here separated by spaces or one per line using +=
	ADDON_INCLUDES += libs/vosk-api/include
	ADDON_INCLUDES += src
	
	# any special flag that should be passed to the compiler when using this
	# addon
	# ADDON_CFLAGS += -DFST_NO_DYNAMIC_LINKING
	
	# any special flag that should be passed to the linker when using this
	# addon, also used for system libraries with -lname
	# ADDON_LDFLAGS =  -lgfortran -lpthread
	
	# linux only, any library that should be included in the project using
	# pkg-config
	# ADDON_PKG_CONFIG_LIBRARIES =
	
	# osx/iOS only, any framework that should be included in the project
	# ADDON_FRAMEWORKS =
	
	# source files, these will be usually parsed from the file system looking
	# in the src folders in libs and the root of the addon. if your addon needs
	# to include files in different places or a different set of files per platform
	# they can be specified here
	ADDON_SOURCES += src
	
	# some addons need resources to be copied to the bin/data folder of the project
	# specify here any files that need to be copied, you can use wildcards like * and ?
	# ADDON_DATA = 
	
	# when parsing the file system looking for libraries exclude this for all or
	# a specific platform
	# ADDON_LIBS_EXCLUDE =

osx:
	ADDON_FRAMEWORKS += Accelerate
	ADDON_LIBS += libs/vosk-api/lib/osx/libvosk.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-base.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-cudamatrix.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-decoder.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-feat.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-fstext.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-gmm.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-hmm.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-ivector.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-lat.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-lm.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-matrix.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-nnet3.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-online2.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-transform.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-tree.a
	ADDON_LIBS += libs/kaldi/lib/osx/kaldi-util.a
	ADDON_LIBS += libs/kaldi/lib/osx/libfst.a
	ADDON_LIBS += libs/kaldi/lib/osx/libfstngram.a
