#ifndef VID_PROC_H
#define VID_PROC_H

#include <string>
using std::string;

#include <fstream>
using std::ofstream;

#include <iostream>
using std::endl;

#include "ffmpeg_util.h"

class VideoProcessor {

public:

    VideoProcessor();
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

    ofstream log_file;

};



#endif  //VID_PROC_H