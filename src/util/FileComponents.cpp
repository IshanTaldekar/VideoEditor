#include "FileComponents.h"

/**
 * Constructor sets an input target-file path, and processes its contents to build more information on the file.
 *
 * @param input_url the target file path.
 * @param file_code the file type being input (the value can be INTRO_FILE, BACKGROUND_FILE, OUTRO_FILE, AUDIO_FILE, or OUTPUT_FILE).
 * @param curr_log the application's log data structure.
 */
FileComponents::FileComponents(const string & input_url, int file_code, ApplicationStatusLog* curr_log) {

    set_url(input_url);
    set_status_log(curr_log);

    status_log->add("File component received input file @ (" + input_url + ")");

    process_input_file(file_code);

}

/**
 * Constructor sets the output target-file path, and processes its contents to build more information on the file.
 *
 * @param input_url the target file path.
 * @param file_code the file type being input (the value can be INTRO_FILE, BACKGROUND_FILE, OUTRO_FILE, AUDIO_FILE, or OUTPUT_FILE).
 * @param curr_log the application's log data structure.
 * @param input_files the inputs that make up the file at the file path.
 */
FileComponents::FileComponents(const string & input_url, int file_code, ApplicationStatusLog* curr_log, const vector<FileComponents*> & input_files) {

    set_url(input_url);
    set_status_log(curr_log);

    status_log->add("File component received file @ (" + input_url + ")");

    if (file_code == OUTPUT_FILE) {

        prepare_output_file(input_files);

    } else {

        status_log->add("[ERROR] Unexpected file type.");

    }

}

/**
 * Cleanup the allocated memory.
 */
FileComponents::~FileComponents(){

    avformat_close_input(&format_context);
    avformat_free_context(format_context);

    codec = nullptr;
    codec_context = nullptr;
    file_streams.clear();
    codec_context = nullptr;

}

/**
 * Populate all the necessary AV Structs for the input file.
 *
 * @param file_code the file type being input (the value can be INTRO_FILE, BACKGROUND_FILE, OUTRO_FILE, AUDIO_FILE, or OUTPUT_FILE).
 */
void FileComponents::process_input_file(int file_code) {

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

    streams_count = format_context->nb_streams;

    streams_list = vector<int>();
    streams_list.reserve(streams_count);

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
            file_streams.push_back(format_context->streams[i]);

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
 * Construct an output file and populate the appropriate AVStructs.
 */
void FileComponents::prepare_output_file(const vector<FileComponents*> & input_files) {

    status_log->add("Preparing output file.");

    avformat_alloc_output_context2(&format_context, nullptr, nullptr, url.c_str());

    if (!format_context) {

        status_log->add("[ERROR] FileComponents object failed to create output format context.");
        return;

    }

    for (FileComponents* current_file: input_files) {

        streams_count += current_file->get_streams_count();

    }

    stream_index = -1;
    streams_list.reserve(streams_count);

    populate_stream_information(input_files.at(0), stream_index);

    for (FileComponents* current_file: input_files) {

        populate_stream_information(current_file, stream_index);

    }

    av_dump_format(format_context, 0, url.c_str(), 1);

    if (!(format_context->oformat->flags & AVFMT_NOFILE)) {

        if ((avio_open(&format_context->pb, url.c_str(), AVIO_FLAG_WRITE)) < 0) {

            status_log->add("[ERROR] FileComponents object could not open output file @(" + url + ")");
            return;

        }

    }

    AVDictionary* options {nullptr};  // needs to be populated if fragmented mp4 containers need to be supported.

    if ((avformat_write_header(format_context, &options)) < 0) {

        status_log->add("[ERROR] FileComponents object experienced an error when opening output file.");
        return;

    }

    status_log->add("[SUCCESS] Output file ready.");

}

/**
 * Go through the input file and initialize appropriate components in the output file.
 *
 * @param input_file the input file being traversed.
 * @param current_stream_index the smallest unused output stream index.
 */
void FileComponents::populate_stream_information(FileComponents* input_file, int & current_stream_index) {

    for(int i = 0; i < input_file->get_format_context()->nb_streams; ++i) {

        AVStream* new_output_stream {nullptr};
        AVStream* input_stream {input_file->get_format_context()->streams[i]};
        AVCodecParameters* input_codec_parameter {input_stream->codecpar};


        if (input_codec_parameter->codec_type != input_file->get_codec_parameters()->codec_type) {

            streams_list.at(i) = -1;
            continue;

        }

        streams_list.push_back(++current_stream_index);
        new_output_stream = avformat_new_stream(format_context, nullptr);

        if (!new_output_stream) {

            status_log->add("[ERROR] FileComponents object could not allocate output stream.");
            return;

        }

        if (avcodec_parameters_copy(new_output_stream->codecpar, input_codec_parameter) < 0) {

            status_log->add("[ERROR] FileComponents object failed to copy input codec parameters to output stream.");
            return;

        }

    }

}

/**
 * Compute the duration of the file in seconds.
 */
void FileComponents::set_duration() {

    if (stream_index < 0) return;

    long current_duration {0};

    for (int i = 0; i < format_context->nb_streams; ++i) {

        current_duration = max(current_duration, (file_streams.at(stream_index)->duration * file_streams.at(stream_index)->time_base.num) / (file_streams.at(stream_index)->time_base.den));

    }

    duration = current_duration;

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

vector<AVStream*> FileComponents::get_streams() {

    return file_streams;

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

void FileComponents::set_status_log(ApplicationStatusLog* curr_log) {

    status_log = curr_log;

}

const vector<int> &FileComponents::get_streams_list() const {

    return streams_list;

}

void FileComponents::set_streams_list(const vector<int> &StreamsList) {

    streams_list = StreamsList;

}

unsigned int FileComponents::get_streams_count() const {

    return streams_count;

}

void FileComponents::set_streams_count(unsigned int StreamsCount) {

    streams_count = StreamsCount;

}

int FileComponents::get_file_code() const {

    return file_code;

}

void FileComponents::set_file_code(int FileCode) {

    file_code = FileCode;

}
