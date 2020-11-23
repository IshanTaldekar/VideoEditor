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

/**
 * Initialize and position the buttons, file pickers and other widgets.
 *
 * @param title the current frame's title
 * @param pos the position (x and y coordinates).
 * @param size the frame size in pixel (width and height)
 */
VideoEditorHome::VideoEditorHome(const wxString & title, const wxPoint & pos, const wxSize & size): wxFrame((wxFrame*) nullptr, wxID_ANY, title, pos, size) {

    CreateStatusBar(2);  // Number describes how many messages can be displayed in the status bar at a time.

    wxMenu* OptionsMenu = new wxMenu();  // Drop-down menu list of options
    OptionsMenu->Append(MENU_Reset, "&Reset", "Clear input choices");
    OptionsMenu->Append(MENU_About, "&About", "About Video Maker");
    OptionsMenu->Append(MENU_Help, "&Help", "Help");
    OptionsMenu->Append(MENU_Exit, "&Exit", "Quit Video Maker");

    HomeMenuBar = new wxMenuBar();
    HomeMenuBar->Append(OptionsMenu, "&Options");

    SetMenuBar(HomeMenuBar);  // Associate the menu bar with the frame.

    CreatePickers();

    SetIntroFilePickerDesign();
    SetBackgroundFilePickerDesign();
    SetOutroFilePickerDesign();
    SetAudioFilePickerDesign();

    /* Details how the file pickers should be placed in relation to one another: */
    FileBrowsersBox = new wxBoxSizer(wxVERTICAL);
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

    /* Create Buttons: */
    ExecuteButton = new wxButton(this, BUTTON_Execute, "&Run", wxDefaultPosition);
    LoadButton = new wxButton(this, BUTTON_LOAD, "&Load", wxDefaultPosition);

    /* Details how the buttons should be placed in relation to one another: */
    wxBoxSizer* ButtonsBox = new wxBoxSizer(wxHORIZONTAL);
    ButtonsBox->AddStretchSpacer();
    ButtonsBox->Add(LoadButton, 2, wxALIGN_CENTER | wxALL, 0);
    ButtonsBox->AddStretchSpacer();
    ButtonsBox->Add(ExecuteButton, 2, wxALIGN_CENTER | wxALL, 0);
    ButtonsBox->AddStretchSpacer();

    ProgressGaugeBox = new wxBoxSizer(wxVERTICAL);
    CreateGauge();

    /* Details how file picker, buttons and gauge are positioned: */
    LeftBox = new wxBoxSizer(wxVERTICAL);
    LeftBox->AddStretchSpacer();
    LeftBox->Add(FileBrowsersBox, wxSizerFlags().Expand().Border());
    LeftBox->AddStretchSpacer();
    LeftBox->Add(ButtonsBox, wxSizerFlags().Expand().Border());
    LeftBox->AddStretchSpacer();
    LeftBox->Add(ProgressGaugeBox, wxSizerFlags().Expand().Border());
    LeftBox->AddStretchSpacer();

    WordListBox = new wxBoxSizer(wxHORIZONTAL);
    CreateTextBox();
    WordListBox->Add(WordList, 1, wxCENTER | wxEXPAND | wxALL | wxRESIZE_BORDER);

    /* TextBox design: */
    TextBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    TextBox->Add(new wxStaticText(this, wxID_ANY, "&        Recommended Words List"), 0, wxEXPAND , 10);
    TextBox->AddSpacer(10);
    TextBox->Add(WordListBox, 1, wxCENTER | wxEXPAND | wxALL | wxRESIZE_BORDER);

    RightBox = new wxBoxSizer(wxVERTICAL);
    RightBox->AddStretchSpacer(1);
    RightBox->Add(TextBox, 8, wxCENTER | wxEXPAND | wxALL | wxRESIZE_BORDER);
    RightBox->AddStretchSpacer(1);

    /* Final layout details */
    wxSizer* MainSizer = new wxBoxSizer(wxHORIZONTAL);
    MainSizer->Add(LeftBox, 3, wxGROW | wxALL, 10);
    MainSizer->Add(RightBox, 2, wxGROW | wxALL, 10);
    MainSizer->AddSpacer(10);

    SetSizer(MainSizer);  // Associate MainSizer with the frame

}


/**
 * Defines the behavior of the reset button from the options menu. When button is clicked, the
 * file picker selections are reset, button labels are reset, and text box is cleared.
 *
 * @param event unused command event.
 */
void VideoEditorHome::OnOptionReset(wxCommandEvent &event) {

    if (ExecuteButton->GetLabel() == "Cancel") return;  // TODO: Initiate Dialog asking user to terminate any active processes first.
    else {

        RecreatePickers();
        CreateGauge();
        RecreateTextBox();

    }

}


/**
 * Defines the behavior of the about button from the options menu. When button is clicked,
 * a pop up with information about the app and developers appears.
 *
 * @param event unused command event.
 */
void VideoEditorHome::OnOptionAbout(wxCommandEvent &event) {



}


/**
 * Defines the behavior of the help button from the options menu. When button is clicked,
 * a pop up with information on how to use the app appears.
 *
 * @param event unused command event.
 */
void VideoEditorHome::OnOptionHelp(wxCommandEvent &event) {



}

/**
 * Defines the behavior of the exit button from the options menu. When button is clicked, the
 * application terminates.
 *
 * @param event unused command event.
*/
void VideoEditorHome::OnOptionExit(wxCommandEvent &event) {

    Close(true);

}


/**
 * Defines the behavior of the run button. When button is clicked, a dialog prompts the user to
 * select an output file and location. Once the location is selected, the app will start processing
 * the inputs and compute the video output.
 *
 * @param event unused command event
 */
void VideoEditorHome::OnExecute(wxCommandEvent &event) {

    GaugeTimer(event);
    // TODO: Set words list in processor
    // TODO: Get and set output file path and name.
    // TODO: Call individual steps and log exit status.

}


/**
 * Defines the behavior of the load button. When button is clicked, a script will record and validate
 * all inputs are available and green light the use of the run button by the user.
 *
 * @param event unused command event
 */
void VideoEditorHome::OnLoad(wxCommandEvent &event) {

    // TODO: Validate input files
    // TODO: Generate and output word recommendations

}


/**
 * Initialize the different files browser/picker widgets.
 */
void VideoEditorHome::CreatePickers() {

    delete IntroFilePicker;
    delete BackgroundFilePicker;
    delete OutroFilePicker;
    delete AudioFilePicker;

    IntroFilePicker = new wxFilePickerCtrl(this, PICKERPAGE_IntroFile, wxEmptyString, "Choose Intro File",
                                           wxFileSelectorDefaultWildcardStr, wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_FILE_MUST_EXIST | wxFLP_USE_TEXTCTRL);

    BackgroundFilePicker = new wxFilePickerCtrl(this, PICKERPAGE_BackgroundFile, wxEmptyString, "Choose Background File",
                                                "*", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_FILE_MUST_EXIST | wxFLP_USE_TEXTCTRL);

    OutroFilePicker = new wxFilePickerCtrl(this, PICKERPAGE_OutroFile, wxEmptyString, "Choose Outro File",
                                                "*", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_FILE_MUST_EXIST | wxFLP_USE_TEXTCTRL);

    AudioFilePicker = new wxFilePickerCtrl(this, PICKERPAGE_AudioFile, wxEmptyString, "Choose Audio File",
                                                "*", wxDefaultPosition, wxDefaultSize, wxFLP_OPEN | wxFLP_FILE_MUST_EXIST | wxFLP_USE_TEXTCTRL);

}


/**
 * Create a text box widget to display our 'word recommendations list'.
 */
void VideoEditorHome::CreateTextBox() {

    WordList = new wxTextCtrl(this, -1, "", wxDefaultPosition, LeftBox->CalcMin(), wxTE_RICH | wxTE_MULTILINE | wxFULL_REPAINT_ON_RESIZE);
    WordList->SetBackgroundColour("#E4E0C7");
    WordList->SetForegroundColour("#3C3642");

}


/**
 * Resets and initializes a new progress-gauge widget.
 */
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


/**
 * The intro file browser/picker widget are wrapped in static BoxSizers for aesthetic reasons.
 */
void VideoEditorHome::SetIntroFilePickerDesign(){

    IntroFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    IntroFileBox->Add(new wxStaticText(this, wxID_ANY, "&        Choose Intro File "), 0, wxEXPAND, 0);
    IntroPickerWrapperBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    IntroPickerWrapperBox->Add(IntroFilePicker, 1, wxEXPAND | wxALL, 10);
    IntroFileBox->Add(IntroPickerWrapperBox, 1, wxEXPAND | wxALL, 0);

}


/**
 * The background file browser/picker widget are wrapped in static BoxSizers for aesthetic reasons.
 */
void VideoEditorHome::SetBackgroundFilePickerDesign() {

    BackgroundFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    BackgroundFileBox->Add(new wxStaticText(this, wxID_ANY, "&        Choose Background File "), 0, wxEXPAND, 0);
    BackgroundPickerWrapperBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    BackgroundPickerWrapperBox->Add(BackgroundFilePicker, 1, wxEXPAND | wxALL, 10);
    BackgroundFileBox->Add(BackgroundPickerWrapperBox, 1, wxEXPAND | wxALL, 0);

}


/**
 * The outro file browser/picker widget are wrapped in static BoxSizers for aesthetic reasons.
 */
void VideoEditorHome::SetOutroFilePickerDesign(){

    OutroFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    OutroFileBox->Add(new wxStaticText(this, wxID_ANY, "&        Choose Outro File "), 0, wxEXPAND, 0);
    OutroPickerWrapperBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    OutroPickerWrapperBox->Add(OutroFilePicker, 1, wxEXPAND | wxALL, 10);
    OutroFileBox->Add(OutroPickerWrapperBox, 1, wxEXPAND | wxALL, 0);

}


/**
 * The audio file browser/picker widget are wrapped in static BoxSizers for aesthetic reasons.
 */
void VideoEditorHome::SetAudioFilePickerDesign() {

    AudioFileBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    AudioFileBox->Add(new wxStaticText(this, wxID_ANY, "&        Choose Audio File "), 0, wxEXPAND, 0);
    AudioPickerWrapperBox = new wxStaticBoxSizer(wxVERTICAL, this, "");
    AudioPickerWrapperBox->Add(AudioFilePicker, 1, wxEXPAND | wxALL, 10);
    AudioFileBox->Add(AudioPickerWrapperBox, 1, wxEXPAND | wxALL, 0);

}


/**
 * Reinitialize and update the file browser/picker widgets, wipe the old file pickers clean,
 */
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


/**
 * Updates the MediaProcessor::intro_file_url attribute. On a successful update, the function simply exits. However,
 * if the attribute update failed for some reason - a error message is displayed.
 *
 * @param event holds picker state information
 */
void VideoEditorHome::OnIntroFileChange(wxFileDirPickerEvent& event) {

    if (!(Processor->update_intro_file_url(static_cast<string>(event.GetPath())))) {

        // TODO: display unsupported file message.

    }

}


/**
 * Updates the MediaProcessor::outro_file_url attribute. On a successful update, the function simply exits. However,
 * if the attribute update failed for some reason - a error message is displayed.
 *
 * @param event holds picker state information
 */
void VideoEditorHome::OnOutroFileChange(wxFileDirPickerEvent &event) {

    if (!(Processor->update_outro_file_url(static_cast<string>(event.GetPath())))) {

        // TODO: display unsupported file message.

    }

}


/**
 * Updates the MediaProcessor::background_file_url attribute. On a successful update, the function simply exits. However,
 * if the attribute update failed for some reason - a error message is displayed.
 *
 * @param event holds picker state information
 */
void VideoEditorHome::OnBackgroundFileChange(wxFileDirPickerEvent &event) {

    if (!(Processor->update_background_file_url(static_cast<string>(event.GetPath())))) {

        // TODO: display unsupported file message.

    }

}


/**
 * Updates the MediaProcessor::audio_file_url attribute. On a successful update, the function simply exits. However,
 * if the attribute update failed for some reason - a error message is displayed.
 *
 * @param event holds picker state information
 */
void VideoEditorHome::OnAudioFileChange(wxFileDirPickerEvent &event) {

    if (!(Processor->update_audio_file_url(static_cast<string>(event.GetPath())))) {

        // TODO: display unsupported file message.

    }
}


/**
 * When media files are being processed, this function helps keep the progress-gauge pulsing
 * - indicating to user that the application is busy. Otherwise, it will reset the progress-gauge.
 *
 * @param event holds run/cancel button attributes
 */
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


/**
 * If a timer is not active already, create one and make it tick.
 */
void VideoEditorHome::StartTimer() {

    if(ProgressGaugeTimer) return;

    static const int INTERVAL = 150;
    ProgressGaugeTimer = new wxTimer(this, GAUGE_Timer);
    ProgressGaugeTimer->Start(INTERVAL);

}


/**
 * If a timer is active, kill it.
 */
void VideoEditorHome::StopTimer() {

    if (!ProgressGaugeTimer) return;

    ProgressGaugeTimer->Stop();
    wxDELETE(ProgressGaugeTimer);

    ProgressGauge->SetValue(0);

}


/**
 * Use the wxGauge::Pulse() call to introduce movement (activity indication) within the progress-gauge widget.
 */
void VideoEditorHome::ProgressGaugePulse(wxTimerEvent& WXUNUSED(event)) {

    ProgressGauge->Pulse();

}


/**
 * Clear the current 'word recommendation list' text box widget, and create a fresh one to replace it.
 */
void VideoEditorHome::RecreateTextBox() {

    WordListBox->Remove(0);
    delete WordList;

    CreateTextBox();
    WordListBox->Add(WordList, 1, wxCENTER | wxEXPAND | wxALL | wxRESIZE_BORDER);
    RightBox->Layout();

}