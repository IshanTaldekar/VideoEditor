#include "VideoEditorHome.h"

BEGIN_EVENT_TABLE(VideoEditorHome, wxFrame)
EVT_MENU(MENU_New, VideoEditorHome::NewFile)
EVT_MENU(MENU_Open, VideoEditorHome::OpenFile)
EVT_MENU(MENU_Close, VideoEditorHome::CloseFile)
EVT_MENU(MENU_Save, VideoEditorHome::SaveFile)
EVT_MENU(MENU_SaveAs, VideoEditorHome::SaveFileAs)
EVT_MENU(MENU_Quit, VideoEditorHome::Quit)
END_EVENT_TABLE()

VideoEditorHome::VideoEditorHome(const wxString & title, const wxPoint & pos, const wxSize & size): wxFrame((wxFrame*) nullptr, wxID_ANY, title, pos, size) {

    CreateStatusBar(2);  // number describes how many messages can be displayed in the status bar at a time.

    HomeEditBox = new wxTextCtrl(this, TEXT_Home, "Video Display", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH, wxDefaultValidator, wxTextCtrlNameStr);
    MainMenu = new wxMenuBar();
    wxMenu *FileMenu = new wxMenu();
    wxMenu *Templates = new wxMenu();


    FileMenu->Append(MENU_New, "&New", "Create new video");
    FileMenu->Append(MENU_Open, "&Open", "Open video file");
    FileMenu->Append(MENU_Save, "&Save", "Save video file");
    FileMenu->Append(MENU_SaveAs, "&Save As", "Save video file under a new file name");
    FileMenu->Append(MENU_Close, "&Close", "Close current stream");
    FileMenu->Append(MENU_Quit, "&Quit", "Quit");

    Templates->Append(MENU_Template1, "&Generate Video", "Intro + Video + Outro");
    Templates->Append(MENU_Template2, "&Stich Videos", "Video + Video + Video + ...");

    MainMenu->Append(FileMenu, "&File");
    MainMenu->Append(Templates, "&Templates");


    SetMenuBar(MainMenu);

    Maximize();
}

void VideoEditorHome::OpenFile(wxCommandEvent& WXUNUSED(event)) {

    HomeEditBox->LoadFile(wxT(".gitignore"));
}

void VideoEditorHome::NewFile(wxCommandEvent& WXUNUSED(event)) {

}


void VideoEditorHome::CloseFile(wxCommandEvent& WXUNUSED(event)) {

    HomeEditBox->Clear();

}

void VideoEditorHome::SaveFile(wxCommandEvent& WXUNUSED(event)) {

    HomeEditBox->SaveFile(wxT("base.h"));

}

void VideoEditorHome::SaveFileAs(wxCommandEvent& WXUNUSED(event)) {

}

void VideoEditorHome::Quit(wxCommandEvent& WXUNUSED(event)) {
    Close(true);
}





