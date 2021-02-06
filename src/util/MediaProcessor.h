#include "Dependencies.h"
#include "DataContainer.h"

#ifndef VID_PROC_H
#define VID_PROC_H

class MediaProcessor {

public:

    MediaProcessor();
    ~MediaProcessor();

    bool execute();

private:

    DataContainer* application_data {new DataContainer()};

    vector<string> words_list;
    ofstream log_file;

    void set_word_list(vector<string>& new_list);
    bool set_output_file_components();
    bool transcode_and_extend_background_video();
    bool transcode_video(FileComponents decode_file_components, AVPacket *media_packet, AVFrame *media_frame);
    bool encode_video(FileComponents decode_file_components, AVFrame *media_frame);
    bool open_media_and_validate_support(FileComponents & media_file, int validation_option);
    bool write_output_video();

};


#endif  //VID_PROC_H