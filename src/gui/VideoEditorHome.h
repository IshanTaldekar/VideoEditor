#ifndef VIDEO_EDITOR_HOME_H
#define VIDEO_EDITOR_HOME_H

#ifndef wxUSE_FILEPICKERCTRL
#define wxUSE_FILEPICKERCTRL 1  // required by wxWidgets to use file pickers.
#endif

#include <wx/wxprec.h>

#ifndef WX_PRECOMP

    #include <wx/wx.h>
    #include <wx/app.h>
    #include <wx/log.h>
    #include <wx/radiobox.h>
    #include <wx/textctrl.h>
    #include <wx/sizer.h>
    #include <wx/stattext.h>
    #include <wx/checkbox.h>
    #include <wx/imaglist.h>
    #include <wx/filepicker.h>
    #include <wx/filedlg.h>
    #include <wx/statline.h>

#endif

// #include "../util/MediaProcessor.h"
#include "../util/Dependencies.h"
#include "../util/DataContainer.h"
#include "../util/FileComponents.h"
#include "../util/ApplicationStatusLog.h"

class VideoEditorHome : public wxFrame {

public:

    VideoEditorHome(const wxString & title, const wxPoint & pos, const wxSize & size);  // title = the frame's name, pos = where the window will show up, size = the window size.
    ~VideoEditorHome() {}

private:

    FileComponents* AppData {nullptr};
    ApplicationStatusLog* status_log;

    wxMenuBar *HomeMenuBar;  // Drop-down menu bar.
    wxGauge* ProgressGauge {nullptr};  // Progression Gauge at the bottom of the screen.
    wxButton* ExecuteButton;  // Button labelled 'Run'.
    wxButton* LoadButton;
    wxTimer* ProgressGaugeTimer {nullptr};  // Simulates gauge progress.
    wxTextCtrl* WordList;

    /* File browse/choose buttons: */
    wxFilePickerCtrl* IntroFilePicker {nullptr};
    wxFilePickerCtrl* BackgroundFilePicker {nullptr};
    wxFilePickerCtrl* OutroFilePicker {nullptr};
    wxFilePickerCtrl* AudioFilePicker {nullptr};

    /* Widget placement helpers: */
    wxBoxSizer* RightBox;
    wxBoxSizer* LeftBox;
    wxBoxSizer* IntroFileBox;
    wxBoxSizer* BackgroundFileBox;
    wxBoxSizer* OutroFileBox;
    wxBoxSizer* AudioFileBox;
    wxBoxSizer* FileBrowsersBox;
    wxBoxSizer* WordListBox;
    wxStaticBoxSizer* TextBox;
    wxSizer* ProgressGaugeBox;
    wxStaticBoxSizer* IntroPickerWrapperBox;
    wxStaticBoxSizer* BackgroundPickerWrapperBox;
    wxStaticBoxSizer* OutroPickerWrapperBox;
    wxStaticBoxSizer* AudioPickerWrapperBox;

    /* Private member function declarations: */
    void OnOptionReset(wxCommandEvent& event);
    void OnOptionAbout(wxCommandEvent& event);
    void OnOptionHelp(wxCommandEvent& event);
    void OnOptionExit(wxCommandEvent& event);
    void OnExecute(wxCommandEvent& event);
    void OnLoad(wxCommandEvent& event);
    void CreatePickers();
    void RecreatePickers();
    void OnIntroFileChange(wxFileDirPickerEvent& event);
    void OnBackgroundFileChange(wxFileDirPickerEvent& event);
    void OnOutroFileChange(wxFileDirPickerEvent& event);
    void OnAudioFileChange(wxFileDirPickerEvent& event);
    void CreateGauge();
    void GaugeTimer(wxCommandEvent& event);
    void ProgressGaugePulse(wxTimerEvent& event);
    void StartTimer();
    void StopTimer();
    void SetIntroFilePickerDesign();
    void SetBackgroundFilePickerDesign();
    void SetOutroFilePickerDesign();
    void SetAudioFilePickerDesign();
    void CreateTextBox();
    void RecreateTextBox();

    DECLARE_EVENT_TABLE()

};

enum {

    MENU_Reset = wxID_HIGHEST + 1,  // declares an id which is used to call the button (set it as highest + 1 so it doesn't have the same value as one of the default IDs).
    MENU_ChangeOutputDir,
    MENU_About,
    MENU_Help,
    MENU_Exit,
    BUTTON_Execute,
    BUTTON_LOAD,
    GAUGE_ProgressGauge,
    GAUGE_Timer,
    PICKERPAGE_IntroFile,
    PICKERPAGE_BackgroundFile,
    PICKERPAGE_OutroFile,
    PICKERPAGE_AudioFile
};

#endif  // VIDEO_EDITOR_HOME_H
