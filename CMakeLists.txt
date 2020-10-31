cmake_minimum_required(VERSION 3.16)
project(VideoEditor)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/wxWidgets)

set(SOURCE_FILES src/VideoEditorBase.cpp src/VideoEditorHome.cpp)
add_executable(VideoEditorApp ${SOURCE_FILES})
target_link_libraries(VideoEditorApp wx::net wx::core wx::base)
