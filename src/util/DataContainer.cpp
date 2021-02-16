#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-use-anyofallof"
#include "DataContainer.h"

DataContainer::DataContainer(int new_input_files_count, ApplicationStatusLog* curr_log) {

    set_input_files_count(new_input_files_count);
    set_status_log(curr_log);

    input_files.reserve(input_files_count);
    file_code_maps_file_index.reserve(input_files_count);
}

/**
 * Cleaning up dynamically allocated objects.
 */
DataContainer::~DataContainer() {

    for (auto & input_file : input_files) {

        FileComponents* temp_file {input_file};
        input_file = nullptr;

        delete temp_file;

    }

    file_code_maps_file_index.clear();
    delete output_file;

}

/**
 * Open and process input file at file path.
 *
 * @param file_url the file's path
 * @param file_code the type of file -> [INTRO_FILE, BACKGROUND_FILE, OUTRO_FILE, AUDIO_FILE, OUTPUT_FILE].
 */
void DataContainer::set_input_file(const string & file_url, int file_code) {

    if (file_code == OUTPUT_FILE) {

        if (!all_files_live()) return;

        delete output_file;
        output_file = new FileComponents(file_url, file_code, status_log, input_files);

    } else {

        auto it{file_code_maps_file_index.find(file_code)};

        FileComponents *temp_file{nullptr};

        if (it != file_code_maps_file_index.end()) {

            delete input_files.at(it->second);

        } else {

            file_code_maps_file_index.insert({file_code, static_cast<int>(input_files.size())});

        }

        input_files.push_back(new FileComponents(file_url, file_code, status_log));

    }

}

/**
 * Return the file components after processing the input file.
 *
 * @param file_code the type of file -> [INTRO_FILE, BACKGROUND_FILE, OUTRO_FILE, AUDIO_FILE, OUTPUT_FILE].
 * @return requested_component a FileComponent object (refer to FileComponent.h for more information) or nullptr if object doesn't exist.
 */
FileComponents* DataContainer::get_file_components(int file_code) {

    FileComponents* requested_component {nullptr};
    auto it {file_code_maps_file_index.find(file_code)};

    if (it != file_code_maps_file_index.end()) {

        requested_component = input_files.at(it->second);

    }

    return requested_component;

}

/**
 * Verify that all of the necessary input files have been read and processed.
 * @return true if all input FileComponent objects are available and live.
 */
bool DataContainer::all_files_live() {

    if (static_cast<int>(input_files.size()) != get_input_files_count()) return false;

    for (FileComponents* input_file: input_files) {

        if (!input_file->is_live()) return false;

    }

    return true;

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

int DataContainer::get_input_files_count() const {

    return input_files_count;

}

void DataContainer::set_input_files_count(int InputFilesCount) {

    input_files_count = InputFilesCount;

}

#pragma clang diagnostic pop