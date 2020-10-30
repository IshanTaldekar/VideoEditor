#include "wx/wx.h"
#include "VideoEditorHome.h"

class VideoEditingApplication : public wxApp {

    VideoEditorHome* app_frame {};

public:
    VideoEditingApplication() {}
    ~VideoEditingApplication() {}

    virtual bool OnInit();

};

