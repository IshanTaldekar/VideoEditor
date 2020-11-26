#ifndef VID_PROC_H
#define VID_PROC_H


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
constexpr int VIDEO_TYPE_MEDIA_REQUIRED = 1;
constexpr int AUDIO_TYPE_MEDIA_REQUIRED = 2;

struct ProcessorFlags {

    bool intro_file_available {false};
    bool background_file_available {false};
    bool outro_file_available {false};
    bool audio_file_available {false};

    bool execute {false};

};

struct MediaComponents {

    AVFormatContext* format_context {nullptr};
    AVCodec* codec {nullptr};
    AVCodecParameters* codec_parameters {nullptr};
    int stream_index {-1};
    string url {};

};

class MediaProcessor {

public:

    MediaProcessor();
    ~MediaProcessor();

    bool update_intro_file_url(const string& file_path);
    bool update_outro_file_url(const string& file_path);
    bool update_background_file_url(const string& file_path);
    bool update_audio_file_url(const string& file_path);

    bool check_all_files_available();

private:

    MediaComponents intro_file_components;
    MediaComponents background_file_components;
    MediaComponents outro_file_components;
    MediaComponents audio_file_components;

    vector<string> words_list;

    ofstream log_file;

    const string scheme_url_prefix {"file:"};  // url strings in libavformat should have a scheme/protocol (i.e. file for local files), followed by a ":". followed by the url.

    ProcessorFlags state;

    bool validate_file_support(const string& file_path);
    void set_word_list(vector<string>& new_list);
    void generate_background_from_video();
    void generate_background_from_image();
    void stich_videos_in_list(vector<string> file_urls);
    void open_media_and_validate_support(MediaComponents & media_file, int validation_option, bool & status);
    void integrate_audio_with_video_file(const string& audio_file_url, const string& video_file_url);
    void reset_parameters();
    void load_media_file_information(bool& status);
    void log_message(const string& message);

};


#endif  //VID_PROC_H