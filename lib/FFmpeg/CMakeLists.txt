cmake_minimum_required(VERSION 3.17)

project(FFMPEG)

add_library(FFMPEG INTERFACE IMPORTED GLOBAL)
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG_LIBS REQUIRED IMPORTED_TARGET
        libavdevice
        libavfilter
        libavformat
        libavcodec
        libswresample
        libswscale
        libavutil
)
target_link_libraries(FFMPEG INTERFACE PkgConfig::FFMPEG_LIBS)