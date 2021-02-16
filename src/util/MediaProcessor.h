#include "Dependencies.h"
#include "DataContainer.h"
#include "FileComponents.h"

#ifndef MEDIAPROCESSOR_H
#define MEDIAPROCESSOR_H

class MediaProcessor {

public:

    MediaProcessor() = default;

    FileComponents* extend_background_video(FileComponents* background_file, int duration);
    void build_output_video(const vector<FileComponents*> & input_files, FileComponents* output_file);


};


#endif  // MEDIAPROCESSOR_H