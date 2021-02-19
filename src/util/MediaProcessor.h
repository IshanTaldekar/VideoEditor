#include "Dependencies.h"
#include "DataContainer.h"
#include "FileComponents.h"

#ifndef MEDIAPROCESSOR_H
#define MEDIAPROCESSOR_H

class MediaProcessor {

public:

    MediaProcessor() = default;

    virtual void build_output_video(const vector<FileComponents*> & input_files, FileComponents* output_file);
    virtual void interrupt_processing();

protected:

    virtual void encode_output_video();
    virtual void write_output_video();
    virtual void prepare_audio_decoder();
    virtual void encode_output_audio();


};


#endif  // MEDIAPROCESSOR_H