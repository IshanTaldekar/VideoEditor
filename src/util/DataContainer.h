#include "Dependencies.h"
#include "FileComponents.h"
#include "ApplicationStatusLog.h"


#ifndef VIDEOEDITORAPP_FILEDATACONTAINER_H
#define VIDEOEDITORAPP_FILEDATACONTAINER_H

class DataContainer {

    unordered_map<int, int> file_code_maps_file_index;
    vector<FileComponents*> input_files;
    int input_files_count {};
    FileComponents* output_file {nullptr};

    const string scheme_prefix {"file.mp4"};
    string output_file_container {".mp4"};
    string output_file_url {"OutputFile"};

    string output_media_codec {"libx264"};  // H.264, MPEG-4 Part 10
    string output_codec_priv_key {"x264-params"};
    string output_codec_priv_value {"keyint=60:min-keyint=60:scenecut=0:force-cfr=0"};

    string output_muxer_opt_key {};  // set to "movflags" for frag. mp4
    string output_muxer_opt_value {};  // set to "frag_keyframe+empty_moov+default_base_moof" for frag. mp4

    int bitrate {static_cast<int>(2000000)};
    int rc_buffer_size {static_cast<int>(4 * 1000 * 1000)};
    int rc_max_rate {static_cast<int>(2.5 * 1000 * 1000)};
    int rc_min_rate {static_cast<int>(2 * 1000 * 1000)};

    ApplicationStatusLog* status_log {nullptr};

public:

    explicit DataContainer(int input_files_count, ApplicationStatusLog* curr_log);
    ~DataContainer();

    FileComponents* get_file_components(int file_code);
    const string &get_scheme_prefix() const;
    const string &get_output_file_container() const;
    const string &get_output_media_codec() const;
    const string &get_output_codec_priv_key() const;
    const string &get_output_codec_priv_value() const;
    const string &get_output_muxer_opt_key() const;
    const string &get_output_muxer_opt_value() const;
    int get_bitrate() const;
    int get_rc_buffer_size() const;
    int get_rc_max_rate() const;
    int get_rc_min_rate() const;
    bool all_files_live();
    int get_input_files_count() const;

    void set_input_file(const string & file_url, int file_code);
    void set_output_file_container(const string &);
    void set_output_media_codec(const string &);
    void set_output_codec_priv_key(const string &);
    void set_output_codec_priv_value(const string &);
    void set_output_muxer_opt_key(const string &);
    void set_output_muxer_opt_value(const string &);
    void set_bitrate(int);
    void set_rc_buffer_size(int);
    void set_rc_max_rate(int);
    void set_rc_min_rate(int);

private:
    void set_status_log(ApplicationStatusLog*);
    void set_input_files_count(int InputFilesCount);

};

#endif  // VIDEOEDITORAPP_FILEDATACONTAINER_H
