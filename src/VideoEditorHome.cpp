#include "VideoEditorHome.h"


/*

 TODO:

 * Add Save As option  (look into menu sample)
 * Add Save To option
 * Update RecreatePickers to match the application's styling
 * Update Event Table and Button assignments.
 * Look into static lines to highlight headers or maybe even wxPanels.

*/
BEGIN_EVENT_TABLE(VideoEditorHome, wxFrame)
EVT_MENU(MENU_Reset, VideoEditorHome::OnOptionReset)
EVT_MENU(MENU_ChangeOutputDir, VideoEditorHome::OnOptionChangeOutputDir)
EVT_MENU(MENU_About, VideoEditorHome::OnOptionAbout)
EVT_MENU(MENU_Help, VideoEditorHome::OnOptionHelp)
EVT_MENU(MENU_Exit, VideoEditorHome::OnOptionExit)
EVT_BUTTON(BUTTON_Execute, VideoEditorHome::OnExecute)
EVT_BUTTON(BUTTON_LOAD, VideoEditorHome::OnCancel)
EVT_FILEPICKER_CHANGED(PICKERPAGE_IntroFile, VideoEditorHome::OnIntroFileChange)
EVT_FILEPICKER_CHANGED(PICKERPAGE_BackgroundFile, VideoEditorHome::OnBackgroundFileChange)
EVT_FILEPICKER_CHANGED(PICKERPAGE_OutroFile, VideoEditorHome::OnOutroFileChange)
EVT_FILEPICKER_CHANGED(PICKERPAGE_AudioFile, VideoEditorHome::OnAudioFileChange)
EVT_TIMER(GAUGE_Timer, VideoEditorHome::ProgressGaugePulse)
END_EVENT_TABLE()

VideoEditorHome::VideoEditorHome(const wxString & title, const wxPoint & pos, const wxSize & size): wxFrame((wxFrame*) nullptr, wxID_ANY, title, pos, size) {
    /* Create GUI content */

    CreateStatusBar(2);  // Number describes how many messages can be displayed in the status bar at a time.

    wxMenu* OptionsMenu = new wxMenu();  // Drop-down menu list - Options
    OptionsMenu->Append(MENU_Reset, "&Reset", "Clear input choices");
    OptionsMenu->Append(MENU_ChangeOutputDir, "&Choose Output Directory", "Change save directory");  // make into sub-menu
    OptionsMenu->Append(MENU_About, "&About", "About Video Maker");
    OptionsMenu->Append(MENU_Help, "&Help", "Help");
    OptionsMenu->Append(MENU_Exit, "&Exit", "Quit Video Maker");

    HomeMenuBar = new wxMenuBar();
    HomeMenuBar->Append(OptionsMenu, "&Options");

    SetMenuBar(HomeMenuBar);  // Associate the menu bar with the frame

    CreatePickers();

    IntroFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    IntroFileBox->Add(new wxStaticText(this, wxID_ANY, "&    Choose Opening Video "), 0, wxEXPAND, 0);
    wxStaticBoxSizer* IntroBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    IntroBox->Add(IntroFilePicker, 1, wxEXPAND | wxALL, 10);
    IntroFileBox->Add(IntroBox, 1, wxEXPAND | wxALL, 0);

    // BackgroundFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "Choose Background");
    // BackgroundFileBox->Add(BackgroundFilePicker, 0, wxEXPAND | wxALL, 10);

    BackgroundFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    BackgroundFileBox->Add(new wxStaticText(this, wxID_ANY, "&    Choose Background Video "), 0, wxEXPAND, 0);
    wxStaticBoxSizer* BackgroundBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    BackgroundBox->Add(BackgroundFilePicker, 1, wxEXPAND | wxALL, 10);
    BackgroundFileBox->Add(BackgroundBox, 1, wxEXPAND | wxALL, 0);

    // OutroFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "Choose Outro.");
    // OutroFileBox->Add(OutroFilePicker, 0, wxEXPAND | wxALL, 10);

    OutroFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    OutroFileBox->Add(new wxStaticText(this, wxID_ANY, "&    Choose Closing Video "), 0, wxEXPAND, 0);
    wxStaticBoxSizer* OutroBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    OutroBox->Add(OutroFilePicker, 1, wxEXPAND | wxALL, 10);
    OutroFileBox->Add(OutroBox, 1, wxEXPAND | wxALL, 0);

    // AudioFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "Choose Audio");
    // AudioFileBox->Add(AudioFilePicker, 0, wxEXPAND | wxALL, 10);

    AudioFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    AudioFileBox->Add(new wxStaticText(this, wxID_ANY, "&    Choose Audio "), 0, wxEXPAND, 0);
    wxStaticBoxSizer* AudioBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    AudioBox->Add(AudioFilePicker, 1, wxEXPAND | wxALL, 10);
    AudioFileBox->Add(AudioBox, 1, wxEXPAND | wxALL, 0);

    FileBrowsersBox = new wxBoxSizer(wxVERTICAL);  // Add file browsing buttons created above
    FileBrowsersBox->AddStretchSpacer();
    FileBrowsersBox->Add(IntroFileBox, wxSizerFlags().Expand().Border());
    FileBrowsersBox->AddSpacer(10);
    FileBrowsersBox->Add(BackgroundFileBox, wxSizerFlags().Expand().Border());
    FileBrowsersBox->AddSpacer(10);
    FileBrowsersBox->Add(OutroFileBox, wxSizerFlags().Expand().Border());
    FileBrowsersBox->AddSpacer(10);
    FileBrowsersBox->Add(AudioFileBox, wxSizerFlags().Expand().Border());
    FileBrowsersBox->AddStretchSpacer();

    ProgressGaugeBox = new wxBoxSizer(wxVERTICAL);

    CreateGauge();  // Create a progression gauge widget

    ExecuteButton = new wxButton(this, BUTTON_Execute, "&Run", wxDefaultPosition);
    LoadButton = new wxButton(this, BUTTON_LOAD, "&Load", wxDefaultPosition);

    // wxStaticLine* LeftLine = new wxStaticLine(this);
    // LeftLine->Show(true);

    wxBoxSizer* ButtonsBox = new wxBoxSizer(wxHORIZONTAL);
    ButtonsBox->AddStretchSpacer();
    ButtonsBox->Add(LoadButton, 2, wxALIGN_CENTER | wxALL, 0);
    ButtonsBox->AddStretchSpacer();
    ButtonsBox->Add(ExecuteButton, 2, wxALIGN_CENTER | wxALL, 0);
    ButtonsBox->AddStretchSpacer();

    LeftBox = new wxBoxSizer(wxVERTICAL);
    LeftBox->AddStretchSpacer();
    LeftBox->Add(FileBrowsersBox, wxSizerFlags().Expand().Border());
    // LeftBox->Add(LeftLine, 0, wxEXPAND, 0);
    LeftBox->AddStretchSpacer();
    LeftBox->Add(ButtonsBox, wxSizerFlags().Expand().Border());
    LeftBox->AddStretchSpacer();
    LeftBox->Add(ProgressGaugeBox, wxSizerFlags().Expand().Border());
    LeftBox->AddStretchSpacer();

    WordList = new wxTextCtrl(this, -1, "", wxDefaultPosition, LeftBox->CalcMin(), wxTE_RICH | wxTE_MULTILINE | wxFULL_REPAINT_ON_RESIZE);
    WordList->SetBackgroundColour("#E4E0C7");
    WordList->SetForegroundColour("#3C3642");
    WordListBox = new wxBoxSizer(wxHORIZONTAL);
    WordListBox->Add(WordList, 1, wxCENTER | wxEXPAND | wxALL | wxRESIZE_BORDER);

    TextBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    TextBox->Add(new wxStaticText(this, wxID_ANY, "&    Word List"), 0, wxEXPAND , 0);
    TextBox->AddSpacer(10);
    TextBox->Add(WordListBox, 1, wxCENTER | wxEXPAND | wxALL | wxRESIZE_BORDER);

    // ExecuteButton->Enable(false);  // Cannot be used until all required files are available
    // CancelButton->Enable(false);  // Cannot be used until ExecuteButton has been clicked
    RightBox = new wxBoxSizer(wxVERTICAL);
    RightBox->AddStretchSpacer(2);
    RightBox->Add(TextBox, 8, wxCENTER | wxEXPAND | wxALL | wxRESIZE_BORDER);
    RightBox->AddStretchSpacer(2);

    // boxRight->Add(ExecuteButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 30);
    // boxRight->Add(CancelButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 30);

    wxSizer* sz = new wxBoxSizer(wxHORIZONTAL);
    sz->Add(LeftBox, 3, wxGROW | wxALL, 10);
    sz->Add(RightBox, 2, wxGROW | wxALL, 10);
    sz->AddSpacer(10);
    SetSizer(sz);

}

void VideoEditorHome::OnOptionReset(wxCommandEvent &event) {

    /* TODO: display error message if executing scripts */
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

    GaugeTimer(event);

    // TODO: Video Processing
}

void VideoEditorHome::OnCancel(wxCommandEvent &event) {

    GaugeTimer(event);
    ProgressGauge->SetValue(0);

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

    LeftBox->Layout();

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

void VideoEditorHome::GaugeTimer(wxCommandEvent& event) {

    if (event.GetId() == BUTTON_Execute) {

        SetStatusText("Processing...");
        StartTimer();

    }
    else {

        StopTimer();
        SetStatusText("");

    }

}

void VideoEditorHome::StartTimer() {

    if(ProgressGaugeTimer) return;

    static const int INTERVAL = 150;
    ProgressGaugeTimer = new wxTimer(this, GAUGE_Timer);
    ProgressGaugeTimer->Start(INTERVAL);

}

void VideoEditorHome::StopTimer() {

    if (!ProgressGaugeTimer) return;

    ProgressGaugeTimer->Stop();
    wxDELETE(ProgressGaugeTimer);

    ProgressGauge->SetValue(0);

}

void VideoEditorHome::ProgressGaugePulse(wxTimerEvent& WXUNUSED(event)) {

    ProgressGauge->Pulse();

}