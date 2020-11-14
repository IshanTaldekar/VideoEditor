#include "VideoEditorHome.h"

BEGIN_EVENT_TABLE(VideoEditorHome, wxFrame)
EVT_MENU(MENU_Reset, VideoEditorHome::OnOptionReset)
EVT_MENU(MENU_About, VideoEditorHome::OnOptionAbout)
EVT_MENU(MENU_Help, VideoEditorHome::OnOptionHelp)
EVT_MENU(MENU_Exit, VideoEditorHome::OnOptionExit)
EVT_BUTTON(BUTTON_Execute, VideoEditorHome::OnExecute)
EVT_BUTTON(BUTTON_LOAD, VideoEditorHome::OnLoad)
EVT_FILEPICKER_CHANGED(PICKERPAGE_IntroFile, VideoEditorHome::OnIntroFileChange)
EVT_FILEPICKER_CHANGED(PICKERPAGE_BackgroundFile, VideoEditorHome::OnBackgroundFileChange)
EVT_FILEPICKER_CHANGED(PICKERPAGE_OutroFile, VideoEditorHome::OnOutroFileChange)
EVT_FILEPICKER_CHANGED(PICKERPAGE_AudioFile, VideoEditorHome::OnAudioFileChange)
EVT_TIMER(GAUGE_Timer, VideoEditorHome::ProgressGaugePulse)
END_EVENT_TABLE()

/*

 TODO:

 * Display dialog if Run is clicked before files are loaded
 * Explore alternatives for save as prompt
 * Display dialog loaded files of incorrect types.
 * Add a dialog that pops up when user clicks load without selecting all input files
 * OnOptionsReset: if process active - Initiate Dialog asking user to terminate any active processes first.
 * Start log file

*/

VideoEditorHome::VideoEditorHome(const wxString & title, const wxPoint & pos, const wxSize & size): wxFrame((wxFrame*) nullptr, wxID_ANY, title, pos, size) {
    /* Create GUI content */

    CreateStatusBar(2);  // Number describes how many messages can be displayed in the status bar at a time.

    wxMenu* OptionsMenu = new wxMenu();  // Drop-down menu list - Options
    OptionsMenu->Append(MENU_Reset, "&Reset", "Clear input choices");
    OptionsMenu->Append(MENU_About, "&About", "About Video Maker");
    OptionsMenu->Append(MENU_Help, "&Help", "Help");
    OptionsMenu->Append(MENU_Exit, "&Exit", "Quit Video Maker");

    HomeMenuBar = new wxMenuBar();
    HomeMenuBar->Append(OptionsMenu, "&Options");

    SetMenuBar(HomeMenuBar);  // Associate the menu bar with the frame

    CreatePickers();

    IntroFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    IntroFileBox->Add(new wxStaticText(this, wxID_ANY, "&        Choose Opening Video "), 0, wxEXPAND, 0);
    IntroPickerWrapperBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    IntroPickerWrapperBox->Add(IntroFilePicker, 1, wxEXPAND | wxALL, 10);
    IntroFileBox->Add(IntroPickerWrapperBox, 1, wxEXPAND | wxALL, 0);

    BackgroundFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    BackgroundFileBox->Add(new wxStaticText(this, wxID_ANY, "&        Choose Background Video "), 0, wxEXPAND, 0);
    BackgroundPickerWrapperBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    BackgroundPickerWrapperBox->Add(BackgroundFilePicker, 1, wxEXPAND | wxALL, 10);
    BackgroundFileBox->Add(BackgroundPickerWrapperBox, 1, wxEXPAND | wxALL, 0);

    OutroFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    OutroFileBox->Add(new wxStaticText(this, wxID_ANY, "&        Choose Closing Video "), 0, wxEXPAND, 0);
    OutroPickerWrapperBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    OutroPickerWrapperBox->Add(OutroFilePicker, 1, wxEXPAND | wxALL, 10);
    OutroFileBox->Add(OutroPickerWrapperBox, 1, wxEXPAND | wxALL, 0);

    AudioFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    AudioFileBox->Add(new wxStaticText(this, wxID_ANY, "&        Choose Audio "), 0, wxEXPAND, 0);
    AudioPickerWrapperBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    AudioPickerWrapperBox->Add(AudioFilePicker, 1, wxEXPAND | wxALL, 10);
    AudioFileBox->Add(AudioPickerWrapperBox, 1, wxEXPAND | wxALL, 0);

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
    FileBrowsersBox->AddSpacer(20);

    ExecuteButton = new wxButton(this, BUTTON_Execute, "&Run", wxDefaultPosition);
    LoadButton = new wxButton(this, BUTTON_LOAD, "&Load", wxDefaultPosition);

    // ExecuteButton->Enable(false);  // Cannot be used until all required files are loaded

    wxBoxSizer* ButtonsBox = new wxBoxSizer(wxHORIZONTAL);
    ButtonsBox->AddStretchSpacer();
    ButtonsBox->Add(LoadButton, 2, wxALIGN_CENTER | wxALL, 0);
    ButtonsBox->AddStretchSpacer();
    ButtonsBox->Add(ExecuteButton, 2, wxALIGN_CENTER | wxALL, 0);
    ButtonsBox->AddStretchSpacer();

    ProgressGaugeBox = new wxBoxSizer(wxVERTICAL);

    CreateGauge();  // Create a progression gauge widget

    LeftBox = new wxBoxSizer(wxVERTICAL);
    LeftBox->AddStretchSpacer();
    LeftBox->Add(FileBrowsersBox, wxSizerFlags().Expand().Border());
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
    TextBox->Add(new wxStaticText(this, wxID_ANY, "&        Word List"), 0, wxEXPAND , 10);
    TextBox->AddSpacer(10);
    TextBox->Add(WordListBox, 1, wxCENTER | wxEXPAND | wxALL | wxRESIZE_BORDER);

    RightBox = new wxBoxSizer(wxVERTICAL);
    RightBox->AddStretchSpacer(1);
    RightBox->Add(TextBox, 8, wxCENTER | wxEXPAND | wxALL | wxRESIZE_BORDER);
    RightBox->AddStretchSpacer(1);

    wxSizer* MainSizer = new wxBoxSizer(wxHORIZONTAL);
    MainSizer->Add(LeftBox, 3, wxGROW | wxALL, 10);
    MainSizer->Add(RightBox, 2, wxGROW | wxALL, 10);
    MainSizer->AddSpacer(10);
    SetSizer(MainSizer);

}


void VideoEditorHome::OnOptionReset(wxCommandEvent &event) {

    if (ExecuteButton->GetLabel() == "Cancel") return;  // Initiate Dialog asking user to terminate any active processes first.

    RecreatePickers();
    CreateGauge();
    RecreateTextBox();

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
    // Read from TextCtrl
    // Set Word List
    // Call VideoProcessor

}


void VideoEditorHome::OnLoad(wxCommandEvent &event) {

    // Validate input files
    // Call random word generator
    // Write to TextCtrl


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

    IntroPickerWrapperBox->Remove(0);
    BackgroundPickerWrapperBox->Remove(0);
    OutroPickerWrapperBox->Remove(0);
    AudioPickerWrapperBox->Remove(0);

    CreatePickers();

    IntroPickerWrapperBox->Insert(0, IntroFilePicker, 1, wxEXPAND | wxALL, 10);
    BackgroundPickerWrapperBox->Insert(0, BackgroundFilePicker, 0, wxEXPAND | wxALL, 10);
    OutroPickerWrapperBox->Insert(0, OutroFilePicker, 1, wxEXPAND | wxALL, 10);
    AudioPickerWrapperBox->Insert(0, AudioFilePicker, 1, wxEXPAND | wxALL, 10);

    LeftBox->Layout();

}


void VideoEditorHome::OnIntroFileChange(wxFileDirPickerEvent& event) {

    Processor->update_intro_file_url(static_cast<string>(event.GetPath()));

}


void VideoEditorHome::OnOutroFileChange(wxFileDirPickerEvent &event) {

    Processor->update_outro_file_url(static_cast<string>(event.GetPath()));

}


void VideoEditorHome::OnBackgroundFileChange(wxFileDirPickerEvent &event) {

    Processor->update_background_file_url(static_cast<string>(event.GetPath()));

}


void VideoEditorHome::OnAudioFileChange(wxFileDirPickerEvent &event) {

    Processor->update_audio_file_url(static_cast<string>(event.GetPath()));

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

    if (!ProgressGaugeTimer) {

        ExecuteButton->SetLabel("Cancel");
        SetStatusText("Processing...");
        StartTimer();

    }
    else {

        StopTimer();
        ExecuteButton->SetLabel("Run");
        ProgressGauge->SetValue(0);
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


void VideoEditorHome::RecreateTextBox() {

    WordListBox->Remove(0);
    delete WordList;

    WordList = new wxTextCtrl(this, -1, "", wxDefaultPosition, LeftBox->CalcMin(), wxTE_RICH | wxTE_MULTILINE | wxFULL_REPAINT_ON_RESIZE);
    WordList->SetBackgroundColour("#E4E0C7");
    WordList->SetForegroundColour("#3C3642");
    WordListBox->Add(WordList, 1, wxCENTER | wxEXPAND | wxALL | wxRESIZE_BORDER);

    RightBox->Layout();

}