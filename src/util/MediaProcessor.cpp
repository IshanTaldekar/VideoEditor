#include "MediaProcessor.h"

/**
 * Initializes the log file and the list of supported file extensions.
 */
MediaProcessor::MediaProcessor() {

    supported_media_containers = vector<string>({".MOV", ".MP4", ".AVI", ".MPG", "MPEG", ".MP3",
                                                 ".WAV", ".PCM", "AIFF", ".AAC", ".OGG", ".WMA",
                                                 "FLAC", "ALAC"});

    log_file = ofstream("./VideoEditor/build/latest.log", ofstream::out | ofstream::trunc);
    log_message("Start-up successful.");

}


/**
 * Cleanup allocated structs before exiting.
 */
MediaProcessor::~MediaProcessor() {

    avformat_close_input(&intro_file_format_context);
    avformat_close_input(&background_file_format_context);
    avformat_close_input(&outro_file_format_context);
    avformat_close_input(&audio_file_format_context);

    avformat_free_context(intro_file_format_context);
    avformat_free_context(background_file_format_context);
    avformat_free_context(outro_file_format_context);
    avformat_free_context(audio_file_format_context);


}
/**
 * Populate the respective format contexts (AVFormatContext structs stores all information
 * about a file being read or written).
 * @param status true if load operations succeeded
 */
void MediaProcessor::load_media_file_information(bool& status) {

    if (!intro_file_available || !background_file_available || !outro_file_available || !audio_file_available) {
        /* stop if one or more required urls are not set */

        status = false;
        return;

    } else status = true;

    int ret {avformat_open_input(&intro_file_format_context, intro_file_url.c_str(), nullptr, nullptr)};

    if (ret < 0) {

        log_message("ERROR: intro file could not be opened.");
        status = false;
        abort();

    } else avformat_find_stream_info(intro_file_format_context, nullptr);

    ret = avformat_open_input(&background_file_format_context, background_file_url.c_str(), nullptr, nullptr);

    if (ret < 0) {

        log_message("ERROR: background file could not be opened.");

        status = false;
        abort();

    } else avformat_find_stream_info(background_file_format_context, nullptr);

    ret = avformat_open_input(&outro_file_format_context, outro_file_url.c_str(), nullptr, nullptr);

    if (ret < 0) {

        log_message("ERROR: outro file could not be opened.");

        status = false;
        abort();

    } else avformat_find_stream_info(outro_file_format_context, nullptr);

    ret = avformat_open_input(&audio_file_format_context, audio_file_url.c_str(), nullptr, nullptr);

    if (ret < 0) {

        log_message("ERROR: audio file could not be opened.");

        status = false;
        abort();

    } else avformat_find_stream_info(audio_file_format_context, nullptr);

}


/**
 * Checks that input urls are valid. avformat schemes are very powerful. They can be
 * used to expose local and remote files, audio and video devices etc. File urls
 * should not be used without running checks. For the time being, this function will only
 * look at the extension to determine whether or not the file can be handled.
 * @param filename a c-string containing the destination of the resource on the computer.
 * @returns true if the file exists and is of the appropriate file type.
 * @returns false if the file does not exist or is not supported.
 */
bool MediaProcessor::validate_file_support(const string& file_path) {

    if (file_path.length() > 4 && file_path.length() <= MAX_PATH_LENGTH) {

        string current_extension {};

        for (auto char_pt = file_path.rbegin(); char_pt != file_path.rbegin() + 4; ++char_pt) {
            /* extract extension and convert to uppercase */

            current_extension += toupper(*char_pt);

        }

        reverse(current_extension.begin(), current_extension.end());  // extension extracted right to left, is reversed.

        for (const string& container: supported_media_containers) {
            /* check if extension is a supported container type */

            if (current_extension == container) return true;

        }

    }

    log_message("WARNING: (" + file_path + ") format is not supported.");

    return false;

}


/**
 * Updates intro_file_url attribute to hold the input path, if the path points
 * to a existing and valid file.
 * @param file_path the absolute path to the file
 * @return true if intro_file_path was updated successfully.
 * @return false if file is not of a supported type.
 */
bool MediaProcessor::update_intro_file_url(const string& file_path) {

    if (validate_file_support(file_path)) {

        intro_file_url = scheme_url_prefix+ file_path;
        intro_file_available = true;

    } else intro_file_available = false;

    return intro_file_available;

}


/**
 * Updates intro_file_url attribute to hold the input path, if the path points
 * to a existing and valid file.
 * @param file_path the absolute path to the file
 * @return true if intro_file_path was updated successfully.
 * @return false if file is not of a supported type.
 */
bool MediaProcessor::update_background_file_url(const string &file_path) {

    if (validate_file_support(file_path)) {

        background_file_url = scheme_url_prefix + file_path;
        background_file_available = true;

    } else background_file_available = false;

    return background_file_available;

}


/**
 * Updates intro_file_url attribute to hold the input path, if the path points
 * to a existing and valid file.
 * @param file_path the absolute path to the file
 * @return true if intro_file_path was updated successfully.
 * @return false if file is not of a supported type.
 */
bool MediaProcessor::update_outro_file_url(const string& file_path) {

    if (validate_file_support(file_path)) {

        outro_file_url = scheme_url_prefix + file_path;
        outro_file_available = true;

    } else outro_file_available = false;

    return outro_file_available;

}


/**
 * Updates intro_file_url attribute to hold the input path, if the path points
 * to a existing and valid file.
 * @param file_path the absolute path to the file
 * @return true if intro_file_path was updated successfully.
 * @return false if file is not of a supported type.
 */
bool MediaProcessor::update_audio_file_url(const string& file_path) {

    if (validate_file_support(file_path)) {

        audio_file_url = scheme_url_prefix + file_path;
        audio_file_available = true;

    } else audio_file_available = false;

    return audio_file_available;

}


/**
 * Retrieve complete intro file url available.
 * @returns intro file path, if available. otherwise, returns 'file:'.
 */
string MediaProcessor::get_intro_file_url() {

    if (!intro_file_available) return scheme_url_prefix;
    return intro_file_url;

}


/**
 * Retrieve complete background file url available.
 * @returns background file path, if available. otherwise, returns 'file:'.
 */
string MediaProcessor::get_background_file_url() {

    if (!background_file_available) return scheme_url_prefix;
    return background_file_url;

}


/**
 * Retrieve complete outro file url available.
 * @returns outro file path, if available. otherwise, returns 'file:'.
 */
string MediaProcessor::get_outro_file_url() {

    if(!outro_file_available) return scheme_url_prefix;
    return outro_file_url;
}


/**
 * Retrieve complete audio file url available.
 * @returns audio file path, if available. otherwise, returns 'file:',
 * or an a prefix local files scheme followed by an empty url.
 */
string MediaProcessor::get_audio_file_url() {

    if (!audio_file_available) return scheme_url_prefix;
    return audio_file_url;

}


/**
 * Update the word list.
 * @param new_list an array of (string) words
 */
void MediaProcessor::set_word_list(vector<string>& new_list) {

    words_list = new_list;
    log_message("Word list updated.");

}


/**
 * Setup the files provided by the user to be processed.
 * @returns true if load was successful.
 */
bool MediaProcessor::load() {

    log_message("Started loading media files.");

    bool status {};
    load_media_file_information(status);

    if (status) log_message("Media files read.");
    else log_message("ERROR: read operation failed.");

    return status;

}


/**
 * Write a message to log file.
 * @param message the (string) message to be written
 */
void MediaProcessor::log_message(const string& message) {

    log_file << message << endl;
    log_file.flush();

}
