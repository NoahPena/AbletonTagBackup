
#pragma once

#include <wx/wx.h>

class MyDialog1 : public wxDialog
{
	private:

	protected:
		
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_popupBoxOKButton;
		wxButton* m_popupBoxCancelButton;

	public:
        wxStaticText* m_popupBoxTextBox;

		MyDialog1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

};