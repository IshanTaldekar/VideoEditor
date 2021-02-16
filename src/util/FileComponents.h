#include "Dependencies.h"
#include "ApplicationStatusLog.h"

#ifndef VIDEOEDITORAPP_FILECOMPONENTS_H
#define VIDEOEDITORAPP_FILECOMPONENTS_H

class FileComponents {

    AVFormatContext* format_context {nullptr};
    AVCodec* codec {nullptr};
    AVCodecParameters* codec_parameters {nullptr};
    vector<AVStream*> file_streams;
    AVCodecContext* codec_context {nullptr};
    int stream_index {};
    vector<int> streams_list;
    unsigned int streams_count {0};
    string url {};
    string filename {};
    long int duration {-1};
    bool file_live_flag {false};
    ApplicationStatusLog* status_log {nullptr};
    int file_code {};

public:

    FileComponents(const string & input_url, int file_code, ApplicationStatusLog* curr_log);
    FileComponents(const string & input_url, int file_code, ApplicationStatusLog* curr_log, const vector<FileComponents*> & input_files);
    ~FileComponents();

    AVFormatContext* get_format_context();
    AVCodec* get_codec();
    AVCodecParameters* get_codec_parameters();
    vector<AVStream*> get_streams();
    AVCodecContext* get_codec_context();
    int get_stream_index() const;
    string get_url();
    string get_filename();
    long int get_duration();
    bool is_live() const;
    void set_filename(string filename);
    void set_status_log(ApplicationStatusLog* curr_log);
    const vector<int> &get_streams_list() const;
    void set_streams_list(const vector<int> &StreamsList);
    unsigned int get_streams_count() const;
    void set_streams_count(unsigned int StreamsCount);
    int get_file_code() const;

private:

    void set_format_context(AVFormatContext* input_context);
    void set_codec(AVCodec* input_codec);
    void set_codec_parameters(AVCodecParameters* input_parameters);
    void set_codec_context(AVCodecContext* input_context);
    void set_url(string input_url);
    void set_duration();
    void process_file(int file_code);
    bool extract_stream_information(int file_code);
    void prepare_output_file(const vector<FileComponents*> & input_files);
    void populate_output_stream_information(FileComponents* input_file, int & current_stream_index);
    void set_file_code(int FileCode);

};


#endif  //VIDEOEDITORAPP_FILECOMPONENTS_H
