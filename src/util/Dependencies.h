#ifndef FILETYPE_CODES
#define FILETYPE_CODES

enum {

    INPUT_FILETYPE = 0,
    OUTPUT_FILETYPE,
    INTRO_FILE,
    BACKGROUND_FILE,
    OUTRO_FILE,
    AUDIO_FILE,
    OUTPUT_FILE

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
#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include <random>
#include <unistd.h>
#include <algorithm>
#include <functional>
using std::pair;
using std::string;
using std::getline;
using std::cout;
using std::ofstream;
using std::ifstream;
using std::endl;
using std::vector;
using std::move;
using std::unordered_map;
using std::unordered_set;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::chrono::system_clock;
using std::to_string;
using std::back_inserter;

#endif //VIDEOEDITORAPP_DEPENDENCIES_H
