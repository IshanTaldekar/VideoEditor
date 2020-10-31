#ifndef VIDEO_EDITOR_HOME_H
#define VIDEO_EDITOR_HOME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif


class VideoEditorHome : public wxFrame {

public:
    VideoEditorHome(const wxString & title, const wxPoint & pos, const wxSize & size);  // title = the frame's name, pos = where the window will show up, size = the window size.
    wxTextCtrl *HomeEditBox;
    wxMenuBar *MainMenu;
    wxButton* Exit;

    void Quit(wxCommandEvent& event);
    void NewFile(wxCommandEvent& event);
    void OpenFile(wxCommandEvent& event);
    void SaveFile(wxCommandEvent& event);
    void SaveFileAs(wxCommandEvent& event);
    void CloseFile(wxCommandEvent& event);

    ~VideoEditorHome() {}

    DECLARE_EVENT_TABLE()

};

enum {

    TEXT_Home = wxID_HIGHEST + 1,  // declares an id which is used to call the button (set it as highest + 1 so it doesn't have the same value as one of the default IDs).
    MENU_New,
    MENU_Open,
    MENU_Close,
    MENU_Save,
    MENU_SaveAs,
    MENU_Quit,
    MENU_Template1,
    MENU_Template2

};

#endif
