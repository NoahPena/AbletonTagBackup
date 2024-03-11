#include "PopUpBox.h"

MyDialog1::MyDialog1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_popupBoxTextBox = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_popupBoxTextBox->Wrap( -1 );
	bSizer6->Add( m_popupBoxTextBox, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	bSizer4->Add( bSizer6, 1, wxEXPAND, 5 );

	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_popupBoxOKButton = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_popupBoxOKButton );
	m_popupBoxCancelButton = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_popupBoxCancelButton );
	m_sdbSizer1->Realize();

	bSizer4->Add( m_sdbSizer1, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();
	bSizer4->Fit( this );

	this->Centre( wxBOTH );
}