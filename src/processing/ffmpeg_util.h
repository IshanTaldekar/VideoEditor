#ifndef VIDEOEDITOR_FFMPEG_UTIL_H
#define VIDEOEDITOR_FFMPEG_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <libavutil/avutil.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libavdevice/avdevice.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>

bool validate_current_url(const char* file_name);

#ifdef __cplusplus
}
#endif


#endif//VIDEOEDITOR_FFMPEG_UTIL_H
