#include "MediaProcessor.h"

/**
 * Initializes the log file and the list of supported file extensions.
 */
MediaProcessor::MediaProcessor() {

    log_file = ofstream("./VideoEditor/build/latest.log", ofstream::out | ofstream::trunc);
    log_message("Start-up successful.");

}


/**
 * Cleanup allocated structs before exiting.
 */
MediaProcessor::~MediaProcessor() {

    avformat_close_input(&intro_file_components.format_context);
    avformat_close_input(&background_file_components.format_context);
    avformat_close_input(&outro_file_components.format_context);
    avformat_close_input(&audio_file_components.format_context);

    avformat_free_context(intro_file_components.format_context);
    avformat_free_context(background_file_components.format_context);
    avformat_free_context(outro_file_components.format_context);
    avformat_free_context(audio_file_components.format_context);

}


/**
 * opens input files and verifies that format is supported.
 *
 * @param media_file wrapper for the necessary libav structs.
 * @param validation_option specifies required streams.
 * @param status true if file format is supported and has the required streams.
 */
void MediaProcessor::open_media_and_validate_support(MediaComponents & media_file_components, int validation_option, bool & status) {

    avformat_free_context(media_file_components.format_context);

    media_file_components.format_context = nullptr;
    media_file_components.codec = nullptr;
    media_file_components.codec_parameters = nullptr;
    status = false;
    media_file_components.stream_index = -1;

    if (avformat_open_input(&media_file_components.format_context, media_file_components.url.c_str(), nullptr, nullptr) < 0) {

        log_message("ERROR: could not open file.");
        return;

    }

    if (avformat_find_stream_info(media_file_components.format_context, nullptr) < 0) {

        log_message("ERROR: did not find stream information.");
        return;

    }

    for (int i = 0; i < media_file_components.format_context->nb_streams; ++i) {

        AVCodecParameters* media_stream_codec_parameters {media_file_components.format_context->streams[i]->codecpar};
        AVCodec* media_stream_codec {avcodec_find_decoder(media_stream_codec_parameters->codec_id)};

        if (!media_stream_codec) {

            log_message("ERROR: stream codec not supported.");
            status = false;
            return;

        }

        if((validation_option == VIDEO_TYPE_MEDIA_REQUIRED && media_stream_codec_parameters->codec_type == AVMEDIA_TYPE_VIDEO)
            || (validation_option == AUDIO_TYPE_MEDIA_REQUIRED && media_stream_codec_parameters->codec_type == AVMEDIA_TYPE_AUDIO)) {

            media_file_components.stream_index = i;
            media_file_components.codec = media_stream_codec;
            media_file_components.codec_parameters = media_stream_codec_parameters;

            status = true;
            log_message("DONE: good input file format.");

            return;

        }

    }

    log_message("ERROR: bad input file format.");

}


/**
 * Loop background video to match the duration of the audio file provided.
 *
 * @return true if operation was successful.
 */
bool MediaProcessor::extend_background_video_duration() {

    AVCodecContext* codec_context {avcodec_alloc_context3(background_file_components.codec)};

    if (!codec_context) {

        log_message("ERROR: codec memory allocation failed while extending background video.");
        return false;

    }

    if (avcodec_parameters_to_context(codec_context, background_file_components.codec_parameters) < 0) {

        log_message("ERROR: background codec params could not be copied to the context.");
        return false;

    }

    if (avcodec_open2(codec_context, background_file_components.codec, nullptr) < 0) {

        log_message("ERROR: failed to open codec.");
        return false;

    }

    AVFrame* media_frame {av_frame_alloc()};

    if (!media_frame) {

        log_message("ERROR: failed to allocate memory for frame.");
        return false;

    }

    AVPacket* media_packet {av_packet_alloc()};

    if (!media_packet) {

        log_message("ERROR: failed to allocate memory for packet.");
        return false;

    }

    while (av_read_frame(background_file_components.format_context, media_packet) >= 0) {

        if (media_packet->stream_index == background_file_components.stream_index) {

            // TODO: see if there is a way to encode packets in here with diff pts values

        }

    }

    return true;

}


/**
 * Updates intro file components, if input file at url is valid.
 *
 * @param file_path the absolute path to the file.
 * @return false if file cannot be opened or is not of a supported type.
 */
bool MediaProcessor::update_intro_file_url(const string& file_path) {

    bool status {};
    intro_file_components.url = scheme_url_prefix + file_path;

    log_message("Verifying that (intro file) format is supported.");
    open_media_and_validate_support(intro_file_components, VIDEO_TYPE_MEDIA_REQUIRED, status);

    if (status) state.intro_file_available = true;
    else state.intro_file_available = false;

    return state.intro_file_available;

}


/**
 * Updates background file components, if input file at url is valid.
 *
 * @param file_path the absolute path to the file.
 * @return false if file cannot be opened or is not of a supported type.
 */
bool MediaProcessor::update_background_file_url(const string &file_path) {

    bool status {};
    background_file_components.url = scheme_url_prefix + file_path;

    log_message("Verifying that (background file) format is supported.");
    open_media_and_validate_support(background_file_components, VIDEO_TYPE_MEDIA_REQUIRED, status);

    if (status) state.background_file_available = true;
    else state.background_file_available = false;

    return state.background_file_available;

}


/**
 * Updates outro file components, if input file at url is valid.
 *
 * @param file_path the absolute path to the file.
 * @return false if file cannot be opened or is not of a supported type.
 */
bool MediaProcessor::update_outro_file_url(const string& file_path) {

    bool status {};
    outro_file_components.url = scheme_url_prefix + file_path;

    log_message("Verifying that (outro file) format is supported.");
    open_media_and_validate_support(outro_file_components, VIDEO_TYPE_MEDIA_REQUIRED, status);

    if (status) state.outro_file_available = true;
    else state.outro_file_available = false;

    return state.outro_file_available;

}


/**
 * Updates audio file components, if input file at url is valid.
 *
 * @param file_path the absolute path to the file.
 * @return false if file cannot be opened or is not of a supported type.
 */
bool MediaProcessor::update_audio_file_url(const string& file_path) {

    bool status {};
    audio_file_components.url = scheme_url_prefix + file_path;

    log_message("Verifying that (audio file) format is supported.");
    open_media_and_validate_support(audio_file_components, AUDIO_TYPE_MEDIA_REQUIRED, status);

    if (status) state.audio_file_available = true;
    else state.audio_file_available = false;

    return state.audio_file_available;

}


/**
 * Update the word list.
 *
 * @param new_list an array of (string) words.
 */
void MediaProcessor::set_word_list(vector<string>& new_list) {

    words_list = new_list;
    log_message("Word list updated.");

}


/**
 * Check that all required input files are available.
 *
 * @returns true if all four input files have been loaded.
 */
bool MediaProcessor::check_all_files_available() const {

    if (state.intro_file_available && state.outro_file_available && state.audio_file_available
        && state.background_file_available) return true;

    return false;

}


/**
 * Write a message to log file.
 *
 * @param message the (string) message to be written.
 */
void MediaProcessor::log_message(const string& message) {

    log_file << "> " << message << endl;
    log_file.flush();

}
