cmake_minimum_required(VERSION 3.16)
project(VideoEditor)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER_VERSION REQUIRED True)

add_subdirectory(lib/FFmpeg)
add_subdirectory(lib/wxWidgets)

set(SOURCE_FILES
        src/gui/VideoEditorBase.cpp
        src/gui/VideoEditorHome.cpp
        src/processing/video_processing.cpp
        src/processing/ffmpeg_util.c
)

add_executable(VideoEditorApp ${SOURCE_FILES})

target_link_libraries(VideoEditorApp wx::net wx::core wx::base FFmpeg)
