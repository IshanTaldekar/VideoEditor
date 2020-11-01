#include "VideoEditorHome.h"

BEGIN_EVENT_TABLE(VideoEditorHome, wxFrame)
EVT_MENU(MENU_Reset, VideoEditorHome::OnOptionReset)
EVT_MENU(MENU_ChangeOutputDir, VideoEditorHome::OnOptionChangeOutputDir)
EVT_MENU(MENU_About, VideoEditorHome::OnOptionAbout)
EVT_MENU(MENU_Help, VideoEditorHome::OnOptionHelp)
EVT_MENU(MENU_Exit, VideoEditorHome::OnOptionExit)
EVT_BUTTON(BUTTON_Execute, VideoEditorHome::OnExecute)
EVT_BUTTON(BUTTON_Cancel, VideoEditorHome::OnCancel)
EVT_FILEPICKER_CHANGED(PICKERPAGE_IntroFile, VideoEditorHome::OnIntroFileChange)
EVT_FILEPICKER_CHANGED(PICKERPAGE_BackgroundFile, VideoEditorHome::OnBackgroundFileChange)
EVT_FILEPICKER_CHANGED(PICKERPAGE_OutroFile, VideoEditorHome::OnOutroFileChange)
EVT_FILEPICKER_CHANGED(PICKERPAGE_AudioFile, VideoEditorHome::OnAudioFileChange)
END_EVENT_TABLE()

VideoEditorHome::VideoEditorHome(const wxString & title, const wxPoint & pos, const wxSize & size): wxFrame((wxFrame*) nullptr, wxID_ANY, title, pos, size) {

    CreateStatusBar(2);  // number describes how many messages can be displayed in the status bar at a time.

    HomeMenuBar = new wxMenuBar();
    wxMenu *OptionsMenu = new wxMenu();

    OptionsMenu->Append(MENU_Reset, "&Reset Selections", "Clear input choices");
    OptionsMenu->Append(MENU_ChangeOutputDir, "&Change Output Folder", "Edit where the output video will be written to");
    OptionsMenu->Append(MENU_About, "&About", "About");
    OptionsMenu->Append(MENU_Help, "&Help", "Help");
    OptionsMenu->Append(MENU_Exit, "&Quit", "Close Video Maker");
    HomeMenuBar->Append(OptionsMenu, "&Options");

    SetMenuBar(HomeMenuBar);

    CreatePickers();

    boxLeft = new wxBoxSizer(wxVERTICAL);

    IntroFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "Choose Intro.");
    IntroFileBox->Add(IntroFilePicker, wxSizerFlags().Expand().Border());

    BackgroundFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "Choose Background");
    BackgroundFileBox->Add(BackgroundFilePicker, wxSizerFlags().Expand().Border());

    OutroFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "Choose Outro.");
    OutroFileBox->Add(OutroFilePicker, wxSizerFlags().Expand().Border());

    AudioFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "Choose Audio");
    AudioFileBox->Add(AudioFilePicker, wxSizerFlags().Expand().Border());

    boxLeft->AddSpacer(50);
    boxLeft->Add(IntroFileBox, wxSizerFlags().Expand().Border());
    boxLeft->AddSpacer(25);
    boxLeft->Add(BackgroundFileBox, wxSizerFlags().Expand().Border());
    boxLeft->AddSpacer(25);
    boxLeft->Add(OutroFileBox, wxSizerFlags().Expand().Border());
    boxLeft->AddSpacer(25);
    boxLeft->Add(AudioFileBox, wxSizerFlags().Expand().Border());
    boxLeft->AddStretchSpacer();

    // ADD GAUGE
    ProgressGaugeBox = new wxBoxSizer(wxVERTICAL);
    CreateGauge();
    boxLeft->Add(ProgressGaugeBox, wxSizerFlags().Expand().Border());
    boxLeft->AddStretchSpacer();


    ExecuteButton = new wxButton(this, BUTTON_Execute, "&Run", wxDefaultPosition);
    CancelButton = new wxButton(this, BUTTON_Cancel, "&Cancel", wxDefaultPosition);

    // ExecuteButton->Enable(false);
    CancelButton->Enable(false);

    boxRight = new wxBoxSizer(wxVERTICAL);

    boxRight->AddStretchSpacer();
    boxRight->Add(ExecuteButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 30);
    boxRight->Add(CancelButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 30);
    boxRight->AddStretchSpacer();

    wxSizer *sz = new wxBoxSizer(wxHORIZONTAL);
    sz->Add(boxLeft, 1, wxGROW | wxALL, 10);
    sz->Add(boxRight, 0, wxGROW | wxALL, 10);
    SetSizer(sz);

}

void VideoEditorHome::OnOptionReset(wxCommandEvent &event) {

    RecreatePickers();
    CreateGauge();

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

    // Have Progress Gauge Pulse

}

void VideoEditorHome::OnCancel(wxCommandEvent &event) {

    ProgressGauge->SetValue(0);

}


void VideoEditorHome::CreateContent() {


}

void VideoEditorHome::CreatePickers() {

    delete IntroFilePicker;
    delete BackgroundFilePicker;
    delete OutroFilePicker;
    delete AudioFilePicker;

    IntroFilePicker = new wxFilePickerCtrl(this, PICKERPAGE_IntroFile, wxEmptyString, "Choose Intro File",
                                           "*", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_FILE_MUST_EXIST | wxFLP_USE_TEXTCTRL);

    BackgroundFilePicker = new wxFilePickerCtrl(this, PICKERPAGE_IntroFile, wxEmptyString, "Choose Background File",
                                                "*", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_FILE_MUST_EXIST | wxFLP_USE_TEXTCTRL);

    OutroFilePicker = new wxFilePickerCtrl(this, PICKERPAGE_IntroFile, wxEmptyString, "Choose Outro File",
                                                "*", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_FILE_MUST_EXIST | wxFLP_USE_TEXTCTRL);

    AudioFilePicker = new wxFilePickerCtrl(this, PICKERPAGE_IntroFile, wxEmptyString, "Choose Audio File",
                                                "*", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_FILE_MUST_EXIST | wxFLP_USE_TEXTCTRL);

}

void VideoEditorHome::RecreatePickers() {

    IntroFileBox->Remove(0);
    BackgroundFileBox->Remove(0);
    OutroFileBox->Remove(0);
    AudioFileBox->Remove(0);

    CreatePickers();

    IntroFileBox->Insert(0, IntroFilePicker, 0, wxEXPAND | wxALL, 6);
    BackgroundFileBox->Insert(0, BackgroundFilePicker, 0, wxEXPAND | wxALL, 6);
    OutroFileBox->Insert(0, OutroFilePicker, 0, wxEXPAND | wxALL, 6);
    AudioFileBox->Insert(0, AudioFilePicker, 0, wxEXPAND | wxALL, 6);

    boxLeft->Layout();

}

void VideoEditorHome::OnButtonSetDir(wxCommandEvent& WXUNUSED(event)) {



}

void VideoEditorHome::OnIntroFileChange(wxFileDirPickerEvent& event) {




}

void VideoEditorHome::OnOutroFileChange(wxFileDirPickerEvent &event) {


}

void VideoEditorHome::OnBackgroundFileChange(wxFileDirPickerEvent &event) {


}

void VideoEditorHome::OnAudioFileChange(wxFileDirPickerEvent &event) {



}

void VideoEditorHome::CreateGauge() {

    if (ProgressGauge) {

        ProgressGaugeBox->Detach(ProgressGauge);
        delete ProgressGauge;

    }

    ProgressGauge = new wxGauge(this, GAUGE_ProgressGauge, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL | wxGA_PROGRESS);
    ProgressGauge->SetValue(0);
    ProgressGaugeBox->Add(ProgressGauge, 0, wxEXPAND | wxALL, 6);
    ProgressGaugeBox->Layout();

}