#include <vector>
#include <string>
using std::vector;
using std::string;


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

#endif  // FFMPEG_HEADERS


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


#ifndef VIDEOEDITORAPP_FILECOMPONENTS_H
#define VIDEOEDITORAPP_FILECOMPONENTS_H


class FileComponents {

    AVFormatContext* format_context {nullptr};
    AVCodec* codec {nullptr};
    AVCodecParameters* codec_parameters {nullptr};
    AVStream* file_stream {nullptr};
    AVCodecContext* codec_context {nullptr};
    int stream_index {};
    string url {};
    string filename {};
    int duration {};
    bool file_live {false};

public:

    FileComponents(int status_code);
    ~FileComponents();

    AVFormatContext* get_format_context();
    AVCodec* get_codec();
    AVCodecParameters* get_codec_parameters();
    AVStream* get_stream();
    AVCodecContext* get_codec_context();
    int get_stream_index();
    string get_url();
    string get_filename();
    int get_duration();
    bool is_live();
    void set_output_file_information();
    void recompute();

private:

    void set_format_context(AVFormatContext* input_context);
    void set_codec(AVCodec* input_codec);
    void set_codec_parameters(AVCodecParameters* input_parameters);
    void set_stream(AVStream* input_stream);
    void set_codec_context(AVCodecContext* input_context);
    void set_stream_index(int input_index);
    void set_url(string input_url);
    void set_filename(string filename);
    void set_duration(int file_duration);
    void extract_file_information();

};


#endif  //VIDEOEDITORAPP_FILECOMPONENTS_H
