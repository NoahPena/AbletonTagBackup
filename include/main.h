///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.1.0-0-g733bf3d)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyDialog1 : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText6;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;

	public:

		MyDialog1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

};

class MyFrame : public wxFrame
{
private:


protected:
    wxStaticText* m_staticText1;
    wxRadioBox* m_radioBox3;
    wxStaticText* m_staticText2;
    wxDirPickerCtrl* m_dirPicker2;
    wxStaticText* m_staticText4;
    wxDirPickerCtrl* m_dirPicker3;
    wxStaticText* m_staticText3;
    wxFilePickerCtrl* m_filePicker1;
    wxButton* m_button1;

    MyDialog1* m_dialogBox;

    virtual void onOperationBoxClick(wxCommandEvent& event);
    virtual void onStartButtonClick(wxCommandEvent& event);

public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
};

wxIMPLEMENT_APP(MyApp);

