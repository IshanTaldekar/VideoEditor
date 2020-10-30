cmake_minimum_required(VERSION 3.16)
project(VideoEditor)

set(CMAKE_CXX_STANDARD 14)

set(wxWidgets_ROOT_DIR <wx-3.1>)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

set(SOURCE_FILES src/VideoEditor.cpp)
add_executable(VideoEditorApp ${SOURCE_FILES})

target_link_libraries(VideoEditorApp ${wxWidgets_LIBRARIES})
