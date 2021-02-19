cmake_minimum_required(VERSION 3.17)

project(VideoEditorApp)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_COMPILER_VERSION REQUIRED True)

add_subdirectory(lib/wxWidgets)

add_subdirectory(lib/FFmpeg)

set(SOURCE_FILES

        src/gui/VideoEditorBase.cpp
        src/gui/VideoEditorHome.cpp
        src/util/DataContainer.cpp
        src/util/FileComponents.cpp
        src/util/ApplicationStatusLog.cpp
        src/util/ApplicationWordListGenerator.cpp
        src/util/MediaProcessor.cpp src/util/ProcessorTemplate1.cpp

    )

add_executable(VideoEditorApp ${SOURCE_FILES})

target_link_libraries(VideoEditorApp wx::net wx::core wx::base FFMPEG)
