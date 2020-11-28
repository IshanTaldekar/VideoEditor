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

constexpr int VIDEO_TYPE_MEDIA_REQUIRED = 1;
constexpr int AUDIO_TYPE_MEDIA_REQUIRED = 2;

struct ProcessorState {

    bool intro_file_available {false};
    bool background_file_available {false};
    bool outro_file_available {false};
    bool audio_file_available {false};
    bool execute {false};

    const string scheme_url_prefix {"file:"};  // url strings in libavformat should have a scheme/protocol (i.e. file for local files), followed by a ":". followed by the url.
    string output_file_container {".mp4"};

    /* All information below referenced from: https://github.com/leandromoreira/ffmpeg-libav-tutorial */

    string output_media_codec {"libx264"};  // H.264, MPEG-4 Part 10
    string output_codec_priv_key {"x264-params"};
    string output_codec_priv_value {"keyint=60:min-keyint=60:scenecut=0:force-cfr=0"};

    string output_muxer_opt_key {};  // set to "movflags" for frag. mp4
    string output_muxer_opt_value {};  // set to "frag_keyframe+empty_moov+default_base_moof" for frag. mp4

    int bitrate = 2000000;
    int rc_buffer_size = 4 * 1000 * 1000;
    int rc_max_rate = 2.5 * 1000 * 1000;
    int rc_min_rate = 2 * 1000 * 1000;


};

struct FileComponents {

    AVFormatContext* format_context {nullptr};
    AVCodec* codec {nullptr};
    AVCodecParameters* codec_parameters {nullptr};
    AVStream* stream {nullptr};
    AVCodecContext* codec_context {nullptr};
    int stream_index {};
    string url {};
    string name {};

};

class MediaProcessor {

public:

    MediaProcessor();
    ~MediaProcessor();

    bool update_intro_file_url(const string& file_path);
    bool update_outro_file_url(const string& file_path);
    bool update_background_file_url(const string& file_path);
    bool update_audio_file_url(const string& file_path);

    bool check_all_files_available() const;
    bool execute();

private:

    FileComponents intro_file_components;
    FileComponents background_file_components;
    FileComponents outro_file_components;
    FileComponents audio_file_components;
    FileComponents output_file_components;

    vector<string> words_list;
    ProcessorState state;
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