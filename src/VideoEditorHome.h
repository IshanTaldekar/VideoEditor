#ifndef VIDEO_EDITOR_HOME_H
#define VIDEO_EDITOR_HOME_H

#ifndef wxUSE_FILEPICKERCTRL
#define wxUSE_FILEPICKERCTRL 1
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/app.h>
    #include <wx/log.h>
    #include <wx/radiobox.h>
    #include <wx/textctrl.h>
#endif

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/imaglist.h>
#include <wx/filepicker.h>
#include <wx/filedlg.h>

class VideoEditorHome : public wxFrame {

public:


    VideoEditorHome(const wxString & title, const wxPoint & pos, const wxSize & size);  // title = the frame's name, pos = where the window will show up, size = the window size.
    ~VideoEditorHome() {}

private:

    wxMenuBar *HomeMenuBar;

    wxGauge* ProgressGauge {nullptr};

    wxButton* ExecuteButton;
    wxButton* CancelButton;

    /* File browse/choose buttons */
    wxFilePickerCtrl* IntroFilePicker {nullptr};
    wxFilePickerCtrl* BackgroundFilePicker {nullptr};
    wxFilePickerCtrl* OutroFilePicker {nullptr};
    wxFilePickerCtrl* AudioFilePicker {nullptr};

    /* Widget placement */
    wxSizer* boxRight;
    wxBoxSizer* boxLeft;
    wxBoxSizer* IntroFileBox;
    wxBoxSizer* BackgroundFileBox;
    wxBoxSizer* OutroFileBox;
    wxBoxSizer* AudioFileBox;
    wxSizer* ProgressGaugeBox;

    bool processing_flag {false};  // REMOVE

    void OnOptionReset(wxCommandEvent& event);
    void OnOptionChangeOutputDir(wxCommandEvent& event);
    void OnOptionAbout(wxCommandEvent& event);
    void OnOptionHelp(wxCommandEvent& event);
    void OnOptionExit(wxCommandEvent& event);
    void OnExecute(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    void CreateContent();
    void CreatePickers();
    void RecreatePickers();
    void UpdateFilePickerMode();
    void OnIntroFileChange(wxFileDirPickerEvent& event);
    void OnBackgroundFileChange(wxFileDirPickerEvent& event);
    void OnOutroFileChange(wxFileDirPickerEvent& event);
    void OnAudioFileChange(wxFileDirPickerEvent& event);
    void OnCheckBox(wxCommandEvent& event);
    void OnButtonReset(wxCommandEvent& event);
    void OnButtonSetDir(wxCommandEvent& event);
    void CreateGauge();

    DECLARE_EVENT_TABLE()

};

enum {

    MENU_Reset = wxID_HIGHEST + 1,  // declares an id which is used to call the button (set it as highest + 1 so it doesn't have the same value as one of the default IDs).
    MENU_ChangeOutputDir,
    MENU_About,
    MENU_Help,
    MENU_Exit,
    BUTTON_Execute,
    BUTTON_Cancel,
    GAUGE_ProgressGauge,
    PICKERPAGE_IntroFile,
    PICKERPAGE_BackgroundFile,
    PICKERPAGE_OutroFile,
    PICKERPAGE_AudioFile

};

enum {

    FILE_Open = 0,
    FILE_Save,

};

#endif
