#include "video_processing.h"

VideoProcessor::VideoProcessor(): log_file("./VideoEditor/build/latest.log", ofstream::out | ofstream::trunc) {

    log_file << "start up successful" << endl;
    log_file.flush();

}

bool VideoProcessor::update_intro_file_url(const string& filename) {

    log_file << "<file update event> ";

    if (validate_current_url(filename.c_str())) {

        intro_file_url = file_url_prefix + filename;

        log_file << "new intro file set: " << filename << endl;
        log_file.flush();

        intro_file_available = true;

    } else intro_file_available = false;

    return false;

}


bool VideoProcessor::update_background_file_url(const string &filename) {

    log_file << "<file update event> ";

    if (validate_current_url(filename.c_str())) {

        log_file << "new background file set: " << filename << endl;
        log_file.flush();

        background_file_url = file_url_prefix + filename;

        background_file_available = true;

    } else background_file_available = false;

    return background_file_available;

}


bool VideoProcessor::update_outro_file_url(const string& filename) {

    log_file << "<file update event> ";

    if (validate_current_url(filename.c_str())) {

        log_file << "new outro file set: " << filename << endl;
        log_file.flush();

        outro_file_url = file_url_prefix + filename;
        outro_file_available = true;


    } else outro_file_available = false;

    return outro_file_available;

}


bool VideoProcessor::update_audio_file_url(const string& filename) {

    log_file << "<file update event> ";

    if (validate_current_url(filename.c_str())) {

        log_file << "new audio file set: " << filename << endl;
        log_file.flush();

        audio_file_url = file_url_prefix + filename;

        audio_file_available = true;

    } else audio_file_available = false;

    return audio_file_available;

}


string VideoProcessor::get_intro_file_url() {

    if (!intro_file_available) return "";
    return intro_file_url;

}


string VideoProcessor::get_background_file_url() {

    if (!background_file_available) return "";
    return background_file_url;

}


string VideoProcessor::get_outro_file_url() {

    if(!outro_file_available) return "";
    return outro_file_url;
}


string VideoProcessor::get_audio_file_url() {

    if (!audio_file_available) return "";
    return audio_file_url;

}


bool VideoProcessor::execute() {

    return true;

}
