#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using std::string;
using std::ofstream;
using std::endl;
using std::vector;


#include "DataContainer.h"


#ifndef FFMPEG_HEADERS
#define FFMPEG_HEADERS

extern "C" {

#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#include <libavutil/avutil.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libavdevice/avdevice.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>

}

#endif


#ifndef FILETYPE_CODES
#define FILETYPE_CODES

enum {

    INPUT_FILETYPE = 0,
    OUTPUT_FILETYPE,
    INTRO_FILE,
    BACKGROUND_FILE,
    OUTRO_FILE,
    AUDIO_FILE

};

#endif  // FILETYPE_CODES


#ifndef VID_PROC_H
#define VID_PROC_H

class MediaProcessor {

public:

    MediaProcessor();
    ~MediaProcessor();

    bool execute();

private:

    DataContainer* application_data {new DataContainer()};

    vector<string> words_list;
    ofstream log_file;

    void set_word_list(vector<string>& new_list);
    bool set_output_file_components();
    bool transcode_and_extend_background_video();
    bool transcode_video(FileComponents decode_file_components, AVPacket *media_packet, AVFrame *media_frame);
    bool encode_video(FileComponents decode_file_components, AVFrame *media_frame);
    bool open_media_and_validate_support(FileComponents & media_file, int validation_option);
    bool write_output_video();
    void log_message(const string& message);

};


#endif  //VID_PROC_H