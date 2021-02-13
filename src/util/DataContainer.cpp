#include "DataContainer.h"

DataContainer::DataContainer(ApplicationStatusLog* curr_log) {

    set_status_log(curr_log);

}

/**
 * Cleaning up dynamically allocated memory.
 */
DataContainer::~DataContainer() {

    delete intro_file;
    delete background_file;
    delete outro_file;
    delete audio_file;
    delete output_file;

}

/**
 * Set a file (pointed to by the file path) as one of the 5 file-types possible.
 *
 * @param file_url the file's path
 * @param file_code the type of file (INTRO_FILE, BACKGROUND_FILE, OUTRO_FILE, AUDIO_FILE, OUTPUT_FILE).
 */
void DataContainer::set_input_file(const string & file_url, int file_code) {

    switch(file_code) {

        case INTRO_FILE:
            delete intro_file;
            intro_file = new FileComponents(file_url, file_code, status_log);
            break;

        case BACKGROUND_FILE:
            delete background_file;
            background_file = new FileComponents(file_url, file_code, status_log);
            break;

        case OUTRO_FILE:
            delete outro_file;
            outro_file = new FileComponents(file_url, file_code, status_log);
            break;

        case AUDIO_FILE:
            delete audio_file;
            audio_file = new FileComponents(file_url, file_code, status_log);
            break;

        case OUTPUT_FILE:
            delete output_file;
            output_file = new FileComponents(file_url, file_code, status_log);
            break;

        default:
            status_log->add("[ERROR] Unknown file code received.");

    }

}

/**
 * Return the file components after processing the input file.
 *
 * @param file_code the type of file (INTRO_FILE, BACKGROUND_FILE, OUTRO_FILE, AUDIO_FILE, OUTPUT_FILE).
 * @return requested_component a FileComponent object (refer to FileComponent.h for more information).
 */
FileComponents* DataContainer::get_file_components(int file_code) {

    FileComponents* requested_component {nullptr};

    switch(file_code) {

        case INTRO_FILE:
            requested_component = intro_file;
            break;

        case BACKGROUND_FILE:
            requested_component = background_file;
            break;

        case OUTRO_FILE:
            requested_component = outro_file;
            break;

        case AUDIO_FILE:
            requested_component = audio_file;
            break;

        case OUTPUT_FILE:
            requested_component = output_file;
            break;

        default:
            status_log->add("[ERROR] Unknown file code requested.");

    }

    return requested_component;

}

/**
 * Verify that all of the necessary input files have been read and processed.
 * @return true if all input FileComponent objects are available and live.
 */
bool DataContainer::all_files_live() {

    if (!intro_file || !background_file || !outro_file || !audio_file) {

        return false;

    }

    return (intro_file->is_live() && background_file->is_live() && outro_file->is_live() && audio_file->is_live());

}

void DataContainer::set_status_log(ApplicationStatusLog* curr_log) {

    status_log = curr_log;

}

const string &DataContainer::get_scheme_prefix() const {

    return scheme_prefix;

}

const string &DataContainer::get_output_file_container() const {

    return output_file_container;

}

const string &DataContainer::get_output_media_codec() const {

    return output_media_codec;

}

const string &DataContainer::get_output_codec_priv_key() const {

    return output_codec_priv_key;

}

const string &DataContainer::get_output_codec_priv_value() const {

    return output_codec_priv_value;

}

const string &DataContainer::get_output_muxer_opt_key() const {

    return output_muxer_opt_key;

}

const string &DataContainer::get_output_muxer_opt_value() const {

    return output_muxer_opt_value;

}

int DataContainer::get_bitrate() const {

    return bitrate;

}

int DataContainer::get_rc_buffer_size() const {

    return rc_buffer_size;

}

int DataContainer::get_rc_max_rate() const {

    return rc_max_rate;

}

int DataContainer::get_rc_min_rate() const {

    return rc_min_rate;

}

void DataContainer::set_output_file_container(const string & new_output_container) {

    output_file_container = new_output_container;

}

void DataContainer::set_output_media_codec(const string & new_output_media_codec) {

    output_media_codec = new_output_media_codec;

}

void DataContainer::set_output_codec_priv_key(const string & new_output_codec_priv_key) {

    output_codec_priv_key = new_output_codec_priv_key;

}

void DataContainer::set_output_codec_priv_value(const string & new_output_codec_priv_value) {

    output_codec_priv_value = new_output_codec_priv_value;

}

void DataContainer::set_output_muxer_opt_key(const string & new_output_muxer_opt_key) {

    output_muxer_opt_key = new_output_muxer_opt_key;

}

void DataContainer::set_output_muxer_opt_value(const string & new_output_muxer_opt_value) {

    output_muxer_opt_value = new_output_muxer_opt_value;

}

void DataContainer::set_bitrate(int new_bitrate) {

    bitrate = new_bitrate;

}

void DataContainer::set_rc_buffer_size(int new_rc_buffer_size) {

    rc_buffer_size = new_rc_buffer_size;

}

void DataContainer::set_rc_max_rate(int new_rc_max_rate) {

    rc_max_rate = new_rc_max_rate;

}

void DataContainer::set_rc_min_rate(int new_rc_min_rate) {

    rc_min_rate = new_rc_min_rate;

}
