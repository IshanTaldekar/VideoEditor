#include "MediaProcessor.h"

#ifndef VIDEOEDITORAPP_PROCESSORTEMPLATE1_H
#define VIDEOEDITORAPP_PROCESSORTEMPLATE1_H

class ProcessorTemplate1: public MediaProcessor {

public:

    virtual void build_output_video(const vector<FileComponents*> & input_files, FileComponents* output_file);
    void interrupt_processing();

protected:

    static FileComponents* extend_background_video(FileComponents* background_file, int duration);
    void prepare_video_decoders();
    void prepare_video_encoder();
    void prepare_audio_encoder();
    void transcode_video();
    void transcode_audio();
    void encode_output_video();
    void write_output_video();
    void prepare_audio_decoder();
    void encode_output_audio();

};


#endif  // VIDEOEDITORAPP_PROCESSORTEMPLATE1_H
