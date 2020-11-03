#include "TextPanelSizer.h"

TextPanelSizer::TextPanelSizer(const wxString& FrameTitle): wxFrame(nullptr, -1, FrameTitle, wxPoint(-1, -1), wxSize(250, 180)) {

    TextBox = new wxTextCtrl(this, -1, "", wxPoint(-1, -1), wxSize(250, 150) , wxTE_RICH | wxTE_MULTILINE);
    Centre();

}
