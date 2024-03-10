#include "main.h"


bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello Everyone!", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

MyDialog1::MyDialog1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer6->Add( m_staticText6, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	bSizer4->Add( bSizer6, 1, wxEXPAND, 5 );

	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();

	bSizer4->Add( m_sdbSizer1, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();
	bSizer4->Fit( this );

	this->Centre( wxBOTH );
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Operation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer1->Add( m_staticText1, 0, wxALL, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wxString m_radioBox3Choices[] = { wxT("Create Backup"), wxT("Restore From Backup") };
	int m_radioBox3NChoices = sizeof( m_radioBox3Choices ) / sizeof( wxString );
	m_radioBox3 = new wxRadioBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, m_radioBox3NChoices, m_radioBox3Choices, 2, wxRA_SPECIFY_COLS );
	m_radioBox3->SetSelection( 0 );
	bSizer4->Add( m_radioBox3, 0, wxALL, 5 );


	bSizer1->Add( bSizer4, 1, wxEXPAND, 5 );

	wxGridSizer* gSizer3;
	gSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );;

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Path to User Library"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer3->Add( m_staticText2, 0, wxALL, 5 );

	m_dirPicker2 = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	gSizer3->Add( m_dirPicker2, 0, wxALL, 5 );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Where to place Backup File"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer3->Add( m_staticText4, 0, wxALL, 5 );

	m_dirPicker3 = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	gSizer3->Add( m_dirPicker3, 0, wxALL, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Path to Backup Zip File"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	m_staticText3->Hide();

	gSizer3->Add( m_staticText3, 0, wxALL, 5 );

	m_filePicker1 = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.zip"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	m_filePicker1->Hide();

	gSizer3->Add( m_filePicker1, 0, wxALL, 5 );


	bSizer1->Add( gSizer3, 1, wxEXPAND, 5 );

	wxGridSizer* gSizer4;
	gSizer4 = new wxGridSizer( 0, 1, 0, 0 );

	m_button1 = new wxButton( this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer4->Add( m_button1, 0, wxALIGN_CENTER, 5 );


	bSizer1->Add( gSizer4, 1, wxALIGN_CENTER, 1 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

    // Connect Events
    m_radioBox3->Bind(wxEVT_RADIOBOX, &MyFrame::onOperationBoxClick, this);
    m_button1->Bind(wxEVT_BUTTON, &MyFrame::onStartButtonClick, this);
	
    // Dialog Box
    m_dialogBox = new MyDialog1(this, wxID_ANY, "Hello Everyone!");
    m_dialogBox->Show(false);
}

void MyFrame::onOperationBoxClick(wxCommandEvent& event)
{
    if (m_radioBox3->GetSelection() == 0)
    {
        m_staticText4->Show(true);
        m_staticText3->Show(false);

        m_dirPicker3->Show(true);
        m_filePicker1->Show(false);
    }
    else
    {
        m_staticText4->Show(false);
        m_staticText3->Show(true);

        m_dirPicker3->Show(false);
        m_filePicker1->Show(true);
    }

    // gSizer3->Update();
    this->Layout();
    this->Refresh();
    // this->Fit();

    event.Skip();
}

void MyFrame::onStartButtonClick(wxCommandEvent& event)
{
    m_dialogBox->Show(true);
    m_dialogBox->ShowModal();

    event.Skip();
}