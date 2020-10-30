#include "VideoEditor.h"

wxIMPLEMENT_APP(VideoEditingApplication);  // what does this do

bool VideoEditingApplication::OnInit() {

    app_frame = new VideoEditorHome();
    app_frame->Show();

    return true;

}