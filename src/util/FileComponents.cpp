#include "FileComponents.h"

FileComponents::FileComponents(const string & input_url, int file_code) {

    set_url(input_url);

    // set_status_log(curr_log);
    // status_log->add("File component recieved file @ (" + input_url + ")");

    process_file(file_code);

}

/**
 * Cleanup allocated structs before exiting.
 */
FileComponents::~FileComponents(){

    avformat_close_input(&format_context);
    avformat_free_context(format_context);

}

void FileComponents::process_file(int file_code) {

    avformat_free_context(format_context);

    format_context = nullptr;
    codec = nullptr;
    codec_parameters = nullptr;
    stream_index.clear();

    if (avformat_open_input(&format_context, url.c_str(), nullptr, nullptr) < 0) {

        // status_log->add("[ERROR] File component could not open file.");
        return;

    }

    if (avformat_find_stream_info(format_context, nullptr) < 0) {

        // status_log->add("[ERROR] File component did not find stream information.");
        return;

    }

    if (extract_stream_information(file_code)) {

        // status_log->add("[SUCCESS] File component processed input file.");
        file_live_flag = true;

    } else {

        // status_log->add("[ERROR] File component could not process input file.");
        file_live_flag = false;

    }

}

bool FileComponents::extract_stream_information(int file_code) {

    for (int i = 0; i < format_context->nb_streams; ++i) {

        AVCodecParameters* stream_codec_params {format_context->streams[i]->codecpar};
        AVCodec* stream_codec {avcodec_find_decoder(stream_codec_params->codec_id)};

        if (!stream_codec) {

            // status_log->add("[ERROR] Stream codec found by file component is not supported.");
            return false;

        }

        if ((file_code == AUDIO_FILE && stream_codec_params->codec_type == AVMEDIA_TYPE_AUDIO) ||
            (stream_codec_params->codec_type == AVMEDIA_TYPE_VIDEO)) {

            insert_stream_index(i);
            set_codec(stream_codec);
            set_codec_parameters(stream_codec_params);
            insert_stream(format_context->streams[i]);

            if (!(codec_context = avcodec_alloc_context3(codec))) {

                // status_log->add("[ERROR] File component failed to allocate codec context.");
                return false;

            }

            if (avcodec_open2(codec_context, codec, nullptr) < 0) {

                // status_log->add("[ERROR] File component failed to open codec.");
                return false;

            }

        }

    }

    return true;

}


AVFormatContext* FileComponents::get_format_context() {

    return format_context;

}

AVCodec* FileComponents::get_codec() {

    return codec;

}


AVCodecParameters* FileComponents::get_codec_parameters() {

    return codec_parameters;

}

vector<AVStream*> FileComponents::get_stream() {

    return file_streams;

}

AVCodecContext* FileComponents::get_codec_context() {

    return codec_context;

}

vector<int> FileComponents::get_stream_index() const {

    return stream_index;

}

string FileComponents::get_url() {

    return url;

}

string FileComponents::get_filename() {

    return filename;

}

int FileComponents::get_duration() const  {

    return duration;

}

bool FileComponents::is_live() const {

    return file_live_flag;

}

void FileComponents::set_format_context(AVFormatContext *input_context) {

    format_context = input_context;

}

void FileComponents::set_codec(AVCodec *input_codec) {

    codec = input_codec;

}

void FileComponents::set_codec_parameters(AVCodecParameters *input_parameters) {

    codec_parameters = input_parameters;

}

void FileComponents::insert_stream(AVStream *input_stream) {

    file_streams.push_back(input_stream);

}

void FileComponents::set_codec_context(AVCodecContext *input_context) {

    codec_context = input_context;

}

void FileComponents::insert_stream_index(int input_index) {

    stream_index.push_back(input_index);

}

void FileComponents::set_url(string input_url) {

    url = move(input_url);

}

void FileComponents::set_filename(string input_filename) {

    filename = move(input_filename);

}

void FileComponents::set_duration(int file_duration) {

    duration = file_duration;

}

void FileComponents::set_status_log(ApplicationStatusLog* curr_log) {

    // status_log = curr_log;

}