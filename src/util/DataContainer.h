#include "Dependencies.h"
#include "FileComponents.h"


#ifndef VIDEOEDITORAPP_FILEDATACONTAINER_H
#define VIDEOEDITORAPP_FILEDATACONTAINER_H

class DataContainer {

    FileComponents* intro_file {nullptr};
    FileComponents* background_file {nullptr};
    FileComponents* outro_file {nullptr};
    FileComponents* audio_file {nullptr};
    FileComponents* output_file {nullptr};

    const string scheme_prefix {"file.mp4"};
    string output_file_container {".mp4"};

    string output_media_codec {"libx264"};  // H.264, MPEG-4 Part 10
    string output_codec_priv_key {"x264-params"};
    string output_codec_priv_value {"keyint=60:min-keyint=60:scenecut=0:force-cfr=0"};

    string output_muxer_opt_key {};  // set to "movflags" for frag. mp4
    string output_muxer_opt_value {};  // set to "frag_keyframe+empty_moov+default_base_moof" for frag. mp4

    int bitrate {static_cast<int>(2000000)};
    int rc_buffer_size {static_cast<int>(4 * 1000 * 1000)};
    int rc_max_rate {static_cast<int>(2.5 * 1000 * 1000)};
    int rc_min_rate {static_cast<int>(2 * 1000 * 1000)};

public:

    DataContainer();
    ~DataContainer();

    FileComponents* get_file_components(int file_code);
    void get_output_file_container(string new_file_container);
    void get_output_media_codec(string new_output_codec);
    void get_codec_priv_key(string new_priv_key);
    void get_codec_priv_value(string new_priv_value);
    void get_output_muxer_opt_key(string new_output_muxer_key);
    void get_output_muxer_opt_value(string new_output_muxer_value);
    void get_bitrate(int new_bitrate);
    void get_buffer_size(int new_buffer_size);
    void get_max_rate(int new_max_rate);
    void get_min_rate(int new_min_rate);
    bool all_files_live();

    bool set_input_file(string new_file_url, int file_code);
    void set_output_file_container_postfix(string new_file_container);
    void set_output_media_codec(string new_output_codec);
    void set_codec_priv_key(string new_priv_key);
    void set_codec_priv_value(string new_priv_value);
    void set_output_muxer_opt_key(string new_output_muxer_key);
    void set_output_muxer_opt_value(string new_output_muxer_value);
    void set_bitrate(int new_bitrate);
    void set_buffer_size(int new_buffer_size);
    void set_max_rate(int new_max_rate);
    void set_min_rate(int new_min_rate);

};

#endif  // VIDEOEDITORAPP_FILEDATACONTAINER_H
