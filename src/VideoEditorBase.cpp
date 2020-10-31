#include "VideoEditorBase.h"


wxIMPLEMENT_APP(VideoEditingApplication);  // tells wxWidgets to create an instance of the application.

bool VideoEditingApplication::OnInit() {

    main_frame = new VideoEditorHome(_("Home"), wxDefaultPosition, wxSize(300, 200));
    main_frame->Show(true);
    SetTopWindow(main_frame);  // set as main window.

    return true;

}