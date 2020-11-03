#ifndef TEXT_PANEL_SIZER_H
#define TEXT_PANEL_SIZER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class TextPanelSizer: public wxFrame {

public:
    TextPanelSizer(const wxString& FrameTitle = "TextPanelSizer Frame");
    wxTextCtrl* TextBox;

};

#endif