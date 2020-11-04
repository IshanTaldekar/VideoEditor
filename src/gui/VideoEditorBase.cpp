#include "VideoEditorBase.h"

wxIMPLEMENT_APP(VideoEditingApplication);  // tells wxWidgets to create an instance of the application.

bool VideoEditingApplication::OnInit() {

    main_frame = new VideoEditorHome(_("Video Editor"), wxDefaultPosition, wxSize(750, 825));
    main_frame->Show(true);
    SetTopWindow(main_frame);  // set as main window.

    return true;

}