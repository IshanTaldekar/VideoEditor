#include "FileComponents.h"

/**
 * Constructor sets target-file path. If the file is an input file type, then it processes the file's contents to build more information on
 * the file. Otherwise, it prepares an output file container.
 *
 * @param input_url the target file path
 * @param file_code the file type being input (the value can be INTRO_FILE, BACKGROUND_FILE, OUTRO_FILE, AUDIO_FILE, or OUTPUT_FILE).
 * @param curr_log the application's log data structure.
 */
FileComponents::FileComponents(const string & input_url, int file_code, ApplicationStatusLog* curr_log) {

    set_url(input_url);
    set_status_log(curr_log);

    status_log->add("File component received file @ (" + input_url + ")");

    if (file_code == OUTPUT_FILE) prepare_output_file();
    else process_file(file_code);

}

/**
 * Cleanup the allocated memory.
 */
FileComponents::~FileComponents(){

    avformat_close_input(&format_context);
    avformat_free_context(format_context);

    codec = nullptr;
    codec_context = nullptr;
    file_stream = nullptr;
    codec_context = nullptr;

}

/**
 * Populate all the necessary AV Structs for the input file.
 *
 * @param file_code the file type being input (the value can be INTRO_FILE, BACKGROUND_FILE, OUTRO_FILE, AUDIO_FILE, or OUTPUT_FILE).
 */
void FileComponents::process_file(int file_code) {

    avformat_free_context(format_context);

    format_context = nullptr;
    codec = nullptr;
    codec_parameters = nullptr;
    stream_index = -1;

    if (avformat_open_input(&format_context, url.c_str(), nullptr, nullptr) < 0) {

        status_log->add("[ERROR] File component could not open file.");
        return;

    }

    if (avformat_find_stream_info(format_context, nullptr) < 0) {

        status_log->add("[ERROR] File component did not find stream information.");
        return;

    }

    if (extract_stream_information(file_code)) {

        status_log->add("[SUCCESS] File component processed input file.");
        file_live_flag = true;

    } else {

        status_log->add("[ERROR] File component could not process input file.");
        file_live_flag = false;

    }

}


/**
 * Compute additional information about the audio or video stream.
 *
 * @param file_code file_code the file type being input (the value can be INTRO_FILE, BACKGROUND_FILE, OUTRO_FILE, AUDIO_FILE, or OUTPUT_FILE).
 * @return true if operation was successful
 */
bool FileComponents::extract_stream_information(int file_code) {

    for (int i = 0; i < format_context->nb_streams; ++i) {

        AVCodecParameters* stream_codec_params {format_context->streams[i]->codecpar};
        AVCodec* stream_codec {avcodec_find_decoder(stream_codec_params->codec_id)};

        if (!stream_codec) {

            status_log->add("[ERROR] Stream codec found by file component is not supported.");
            return false;

        }

        if ((file_code == AUDIO_FILE && stream_codec_params->codec_type == AVMEDIA_TYPE_AUDIO) ||
            (file_code != AUDIO_FILE && stream_codec_params->codec_type == AVMEDIA_TYPE_VIDEO)) {

            stream_index = i;
            set_codec(stream_codec);
            set_codec_parameters(stream_codec_params);
            file_stream = format_context->streams[i];

            break;

        }

    }

    if (!(codec_context = avcodec_alloc_context3(codec))) {

        status_log->add("[ERROR] File component failed to allocate codec context.");
        return false;

    }

    if (avcodec_parameters_to_context(codec_context, codec_parameters) < 0) {

        status_log->add("[ERROR] Failed to copy codec context.");
        return false;

    }

    if (avcodec_open2(codec_context, codec, nullptr) < 0) {

        status_log->add("[ERROR] File component failed to open codec.");
        return false;

    }

    return true;

}

/**
 * Construct an output file and populate the appropriate AV Structs.
 */
void FileComponents::prepare_output_file() {

    // TODO

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

AVStream* FileComponents::get_stream() {

    return file_stream;

}

AVCodecContext* FileComponents::get_codec_context() {

    return codec_context;

}

int FileComponents::get_stream_index() const {

    return stream_index;

}

string FileComponents::get_url() {

    return url;

}

string FileComponents::get_filename() {

    return filename;

}

long int FileComponents::get_duration()  {

    set_duration();
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

void FileComponents::set_codec_context(AVCodecContext *input_context) {

    codec_context = input_context;

}

void FileComponents::set_url(string input_url) {

    url = move(input_url);

}

void FileComponents::set_filename(string input_filename) {

    filename = move(input_filename);

}

void FileComponents::set_duration() {

    long duration_in_seconds {0};

    duration_in_seconds += (file_stream->duration * file_stream->time_base.num) / (file_stream->time_base.den);

    duration = duration_in_seconds;

}

void FileComponents::set_status_log(ApplicationStatusLog* curr_log) {

    status_log = curr_log;

}

