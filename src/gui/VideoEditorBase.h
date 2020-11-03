#ifndef VIDEO_EDITOR_BASE_H
#define VIDEO_EDITOR_BASE_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif

#include "VideoEditorHome.h"

class VideoEditingApplication : public wxApp {
    /* a container for the frame VideoEditorHome - controls and handles the properties of the application and checks for events (eg. button click). */

    VideoEditorHome* main_frame {};

public:
    VideoEditingApplication() {}
    ~VideoEditingApplication() {}

    virtual bool OnInit();

};

wxDECLARE_APP(VideoEditingApplication);

#endif