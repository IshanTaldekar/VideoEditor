#include "MediaProcessor.h"


/**
 * Initializes the log file and supported file extensions list.
 */
MediaProcessor::MediaProcessor() {

    supported_media_containers = vector<string>({".MOV", ".MP4", ".AVI", ".MPG", "MPEG", ".MP3",
                                                 ".WAV", ".PCM", "AIFF", ".AAC", ".OGG", ".WMA",
                                                 "FLAC", "ALAC"});

    log_file = ofstream("./VideoEditor/build/latest.log", ofstream::out | ofstream::trunc);
    log_file << "start up successful" << endl;
    log_file.flush();

}


/**
 * checks that input urls are valid. avformat schemes are very powerful. They can
 * be used to expose local and remote files, audio and video devices etc. File urls
 * should not be used without running checks. For the time being, this function will only
 * look at the extension to determine whether or not the file can be handled.
 *
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

        reverse(current_extension.begin(), current_extension.end());  // extension extracted right to left, must be reversed

        for (const string& container: supported_media_containers) {
            /* check if extension is a supported container type */

            if (current_extension == container) return true;

        }

    }

    return false;

}


/**
 * updates intro_file_url attribute to hold the input path, if the path
 * points to a existing and valid file.
 *
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
 * updates intro_file_url attribute to hold the input path, if the path
 * points to a existing and valid file.
 *
 * @param file_path the absolute path to the file
 * @return true if intro_file_path was updated successfully.
 * @return false if file is not of a supported type.
 */
bool MediaProcessor::update_background_file_url(const string &file_path) {

    log_file << "no validation" << endl;

    if (validate_file_support(file_path)) {

        background_file_url = scheme_url_prefix + file_path;
        background_file_available = true;

    } else background_file_available = false;

    return background_file_available;

}


/**
 * updates intro_file_url attribute to hold the input path, if the path
 * points to a existing and valid file.
 *
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
 * updates intro_file_url attribute to hold the input path, if the path
 * points to a existing and valid file.
 *
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
 * retrieve complete intro file url available.
 *
 * @returns intro file path, if available. otherwise, returns 'file:'.
 */
string MediaProcessor::get_intro_file_url() {

    if (!intro_file_available) return scheme_url_prefix;
    return intro_file_url;

}


/**
 * retrieve complete background file url available.
 *
 * @returns background file path, if available. otherwise, returns 'file:'.
 */
string MediaProcessor::get_background_file_url() {

    if (!background_file_available) return scheme_url_prefix;
    return background_file_url;

}


/**
 * retrieve complete outro file url available.
 *
 * @returns outro file path, if available. otherwise, returns 'file:'.
 */
string MediaProcessor::get_outro_file_url() {

    if(!outro_file_available) return scheme_url_prefix;
    return outro_file_url;
}


/**
 * retrieve complete audio file url available.
 *
 * @returns audio file path, if available. otherwise, returns 'file:'.
 */
string MediaProcessor::get_audio_file_url() {

    if (!audio_file_available) return scheme_url_prefix;
    return audio_file_url;

}


/**
 * Update the word list.
 *
 * @param new_list an array of (string) words
 */
void MediaProcessor::set_word_list(vector<string>& new_list) {

    words_list = new_list;

}
