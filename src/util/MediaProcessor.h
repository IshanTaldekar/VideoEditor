#ifndef VID_PROC_H
#define VID_PROC_H

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

#include <string>
using std::string;

#include <fstream>
using std::ofstream;

#include <iostream>
using std::endl;

class MediaProcessor {

public:

    MediaProcessor();
    bool update_intro_file_url(const string& filename);
    bool update_outro_file_url(const string& filename);
    bool update_background_file_url(const string& filename);
    bool update_audio_file_url(const string& filename);

    string get_intro_file_url();
    string get_background_file_url();
    string get_outro_file_url();
    string get_audio_file_url();

    bool execute();

private:

    bool execute_flag {false};
    const string file_url_prefix {"file:"};
    string intro_file_url {};
    string background_file_url {};
    string outro_file_url {};
    string audio_file_url {};

    bool intro_file_available {false};
    bool background_file_available {false};
    bool outro_file_available {false};
    bool audio_file_available {false};

    bool validate_current_url(const char* filename);

    ofstream log_file;

};



#endif  //VID_PROC_H