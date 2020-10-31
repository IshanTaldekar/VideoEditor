#include "VideoEditorHome.h"

BEGIN_EVENT_TABLE(VideoEditorHome, wxFrame)
EVT_MENU(MENU_Reset, VideoEditorHome::OnOptionReset)
EVT_MENU(MENU_ChangeOutputDir, VideoEditorHome::OnOptionChangeOutputDir)
EVT_MENU(MENU_About, VideoEditorHome::OnOptionAbout)
EVT_MENU(MENU_Help, VideoEditorHome::OnOptionHelp)
EVT_MENU(MENU_Exit, VideoEditorHome::OnOptionExit)
EVT_BUTTON(BUTTON_Execute, VideoEditorHome::OnExecute)
EVT_BUTTON(BUTTON_Cancel, VideoEditorHome::OnCancel)
END_EVENT_TABLE()

VideoEditorHome::VideoEditorHome(const wxString & title, const wxPoint & pos, const wxSize & size): wxFrame((wxFrame*) nullptr, wxID_ANY, title, pos, size) {

    CreateStatusBar(2);  // number describes how many messages can be displayed in the status bar at a time.

    FileMenuBar = new wxMenuBar();
    wxMenu *OptionsMenu = new wxMenu();

    OptionsMenu->Append(MENU_Reset, "&Reset Selection", "Clear input choices");
    OptionsMenu->Append(MENU_ChangeOutputDir, "&Edit Output Folder", "Change output folder");
    OptionsMenu->Append(MENU_About, "&About", "About");
    OptionsMenu->Append(MENU_Help, "&Help", "Help");
    OptionsMenu->Append(MENU_Exit, "&Quit", "Close video editor");

    FileMenuBar->Append(OptionsMenu, "&File");
    ExecuteButton = new wxButton(this, BUTTON_Execute, "&Execute", wxPoint(0, 10));
    CancelButton = new wxButton(this, BUTTON_Cancel, "&Cancel", wxPoint(100, 10));

    SetMenuBar(FileMenuBar);
    Maximize();

}

void VideoEditorHome::OnOptionReset(wxCommandEvent &event) {


}

void VideoEditorHome::OnOptionChangeOutputDir(wxCommandEvent &event) {


}

void VideoEditorHome::OnOptionAbout(wxCommandEvent &event) {


}

void VideoEditorHome::OnOptionHelp(wxCommandEvent &event) {


}

void VideoEditorHome::OnOptionExit(wxCommandEvent &event) {

    Close(true);

}

void VideoEditorHome::OnExecute(wxCommandEvent &event) {


}

void VideoEditorHome::OnCancel(wxCommandEvent &event) {


}



