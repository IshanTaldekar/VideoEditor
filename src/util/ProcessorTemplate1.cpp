#include "ProcessorTemplate1.h"

void ProcessorTemplate1::build_output_video(const vector<FileComponents *> &input_files, FileComponents *output_file) {

    MediaProcessor::build_output_video(input_files, output_file);

}

void ProcessorTemplate1::interrupt_processing() {

    MediaProcessor::interrupt_processing();

}

FileComponents *ProcessorTemplate1::extend_background_video(FileComponents *background_file, int duration) {

    return nullptr;

}

void ProcessorTemplate1::prepare_video_decoders() {

}

void ProcessorTemplate1::prepare_video_encoder() {

}

void ProcessorTemplate1::prepare_audio_encoder() {

}

void ProcessorTemplate1::transcode_video() {

}

void ProcessorTemplate1::transcode_audio() {

}

void ProcessorTemplate1::encode_output_video() {

    MediaProcessor::encode_output_video();

}

void ProcessorTemplate1::write_output_video() {

    MediaProcessor::write_output_video();

}
void ProcessorTemplate1::prepare_audio_decoder() {

    MediaProcessor::prepare_audio_decoder();

}

void ProcessorTemplate1::encode_output_audio() {

    MediaProcessor::encode_output_audio();

}
