
#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/filepicker.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/frame.h>
#include <wx/wx.h>

#include "PopUpBox.h"


class MyFrame : public wxFrame
{
private:


protected:
    wxStaticText* m_operationTextBox;
    wxRadioBox* m_operationSelector;
    wxStaticText* m_userLibraryPickerTextBox;
    wxDirPickerCtrl* m_userLibraryPicker;
    wxStaticText* m_createBackupFilePickerTextBox;
    wxDirPickerCtrl* m_createBackupFileLocationPicker;
    wxStaticText* m_restoreFromBackupFilePickerTextBox;
    wxFilePickerCtrl* m_restoreFromBackupFileLocationPicker;
    wxButton* m_startButton;

    MyDialog1* m_popupBox;

    virtual void onOperationBoxClick(wxCommandEvent& event);
    virtual void onStartButtonClick(wxCommandEvent& event);

public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
};
