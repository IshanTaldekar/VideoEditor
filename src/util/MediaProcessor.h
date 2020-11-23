#ifndef VID_PROC_H
#define VID_PROC_H


#ifndef FFMPEG_HEADERS
#define FFMPEG_HEADERS

extern "C" {

#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#include <libavutil/avutil.h>
#include <libavformat/avformat.h>  // allows for splitting of a media file into component stream and writing supplied data in a specified container format.
#include <libavfilter/avfilter.h>
#include <libavdevice/avdevice.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>

}

#endif

#include <string>
using std::string;

#include <fstream>
using std::ofstream;

#include <iostream>
using std::endl;

#include <vector>
using std::vector;

#include <algorithm>
using std::reverse;

constexpr int MAX_PATH_LENGTH = 1024;

class MediaProcessor {

public:

    MediaProcessor();
    ~MediaProcessor();

    bool update_intro_file_url(const string& file_path);
    bool update_outro_file_url(const string& file_path);
    bool update_background_file_url(const string& file_path);
    bool update_audio_file_url(const string& file_path);

    string get_intro_file_url();
    string get_background_file_url();
    string get_outro_file_url();
    string get_audio_file_url();

    bool execute();

private:

    bool execute_flag {false};
    vector<string> words_list;

    const string scheme_url_prefix {"file:"};  // url strings in libavformat should have a scheme/protocol (i.e. file for local files), followed by a ":". followed by the url.

    string intro_file_url {};
    string background_file_url {};
    string outro_file_url {};
    string audio_file_url {};

    bool intro_file_available {false};
    bool background_file_available {false};
    bool outro_file_available {false};
    bool audio_file_available {false};

    vector<string> supported_media_containers;
    ofstream log_file;

    // TODO: add INTRO, OUTRO, BG, AUDIO AVFormatContext vars if required. Init and dealloc on exit.

    bool validate_file_support(const string& file_path);
    void set_word_list(vector<string>& new_list);
    void generate_background_from_video();
    void generate_background_from_picture();
    void generate_background_from_gif();
    void stich_videos_in_list(vector<string> file_urls);
    void integrate_audio_with_video_file(const string& audio_file_url, const string& video_file_url);
    void reset_parameters();
    void log_message(const string& message);
    bool open_video_file();
    bool open_audio_file();
    bool necessary_inputs_available();

};



#endif  //VID_PROC_H