#ifndef FILETYPE_CODES
#define FILETYPE_CODES

enum {

    INPUT_FILETYPE = 0,
    OUTPUT_FILETYPE,
    INTRO_FILE,
    BACKGROUND_FILE,
    OUTRO_FILE,
    AUDIO_FILE

};

#endif  // FILETYPE_CODES


#ifndef FFMPEG_HEADERS
#define FFMPEG_HEADERS

extern "C" {

#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif

#include <libavutil/avutil.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libavdevice/avdevice.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>

}

#endif  // FFMPEG_HEADERS

#ifndef VIDEOEDITORAPP_DEPENDENCIES_H
#define VIDEOEDITORAPP_DEPENDENCIES_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>
using std::string;
using std::cout;
using std::ofstream;
using std::endl;
using std::vector;
using std::move;

#endif //VIDEOEDITORAPP_DEPENDENCIES_H
