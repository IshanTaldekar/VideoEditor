#ifndef VIDEO_EDITOR_HOME_H
#define VIDEO_EDITOR_HOME_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif

class VideoEditorHome : public wxFrame {

public:

    VideoEditorHome(const wxString & title, const wxPoint & pos, const wxSize & size);  // title = the frame's name, pos = where the window will show up, size = the window size.
    ~VideoEditorHome() {}

    wxMenuBar *FileMenuBar;
    void OnOptionReset(wxCommandEvent& event);
    void OnOptionChangeOutputDir(wxCommandEvent& event);
    void OnOptionAbout(wxCommandEvent& event);
    void OnOptionHelp(wxCommandEvent& event);
    void OnOptionExit(wxCommandEvent& event);

    wxButton* ExecuteButton;
    wxButton* CancelButton;
    void OnExecute(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);

    // Add intro, bg, outro, audio file browsers

    // Add progress gauge



    DECLARE_EVENT_TABLE()

};

enum {

    MENU_Reset = wxID_HIGHEST + 1,  // declares an id which is used to call the button (set it as highest + 1 so it doesn't have the same value as one of the default IDs).
    MENU_ChangeOutputDir,
    MENU_About,
    MENU_Help,
    MENU_Exit,
    BUTTON_Execute,
    BUTTON_Cancel

};

#endif
