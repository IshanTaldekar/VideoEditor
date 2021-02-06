#include "Dependencies.h"
#include "ApplicationStatusLog.h"

#ifndef VIDEOEDITORAPP_FILECOMPONENTS_H
#define VIDEOEDITORAPP_FILECOMPONENTS_H

class FileComponents {

    AVFormatContext* format_context {nullptr};
    AVCodec* codec {nullptr};
    AVCodecParameters* codec_parameters {nullptr};
    vector<AVStream*> file_streams {nullptr};
    AVCodecContext* codec_context {nullptr};
    vector<int> stream_index;
    string url {};
    string filename {};
    int duration {};
    bool file_live_flag {false};

public:

    FileComponents(const string & input_url, int file_code);
    ~FileComponents();

    AVFormatContext* get_format_context();
    AVCodec* get_codec();
    AVCodecParameters* get_codec_parameters();
    vector<AVStream*> get_stream();
    AVCodecContext* get_codec_context();
    vector<int> get_stream_index() const;
    string get_url();
    string get_filename();
    int get_duration() const;
    bool is_live() const;
    void set_filename(string filename);
    void set_status_log(ApplicationStatusLog* curr_log);

private:

    void set_format_context(AVFormatContext* input_context);
    void set_codec(AVCodec* input_codec);
    void set_codec_parameters(AVCodecParameters* input_parameters);
    void insert_stream(AVStream* input_stream);
    void set_codec_context(AVCodecContext* input_context);
    void insert_stream_index(int input_index);
    void set_url(string input_url);
    void set_duration(int file_duration);
    void process_file(int file_code);
    bool extract_stream_information(int file_code);

};


#endif  //VIDEOEDITORAPP_FILECOMPONENTS_H
