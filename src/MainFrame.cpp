#include "MainFrame.h"

#include "CreateBackup.h"
#include "RestoreFromBackup.h"

#include <filesystem>

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size, const long style)
// MyFrame::MyFrame(const wxString& title, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
    : wxFrame(NULL, wxID_ANY, title, pos, size, style)
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_operationTextBox = new wxStaticText( this, wxID_ANY, wxT("Operation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_operationTextBox->Wrap( -1 );
	bSizer1->Add( m_operationTextBox, 0, wxALL, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wxString m_operationSelectorChoices[] = { wxT("Create Backup"), wxT("Restore From Backup") };
	int m_operationSelectorNChoices = sizeof( m_operationSelectorChoices ) / sizeof( wxString );
	m_operationSelector = new wxRadioBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, m_operationSelectorNChoices, m_operationSelectorChoices, 2, wxRA_SPECIFY_COLS );
	m_operationSelector->SetSelection( 0 );
	bSizer4->Add( m_operationSelector, 0, wxALL, 5 );


	bSizer1->Add( bSizer4, 1, wxEXPAND, 5 );

	wxGridSizer* gSizer3;
	gSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );;

	m_userLibraryPickerTextBox = new wxStaticText( this, wxID_ANY, wxT("Path to User Library"), wxDefaultPosition, wxDefaultSize, 0 );
	m_userLibraryPickerTextBox->Wrap( -1 );
	gSizer3->Add( m_userLibraryPickerTextBox, 0, wxALL, 5 );

	m_userLibraryPicker = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	gSizer3->Add( m_userLibraryPicker, 0, wxALL, 5 );

	// m_createBackupFilePickerTextBox = new wxStaticText( this, wxID_ANY, wxT("Where to place Backup File"), wxDefaultPosition, wxDefaultSize, 0 );
	// m_createBackupFilePickerTextBox->Wrap( -1 );
	// gSizer3->Add( m_createBackupFilePickerTextBox, 0, wxALL, 5 );

	// m_createBackupFileLocationPicker = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	// gSizer3->Add( m_createBackupFileLocationPicker, 0, wxALL, 5 );

	m_restoreFromBackupFilePickerTextBox = new wxStaticText( this, wxID_ANY, wxT("Path to Backup Zip File"), wxDefaultPosition, wxDefaultSize, 0 );
	m_restoreFromBackupFilePickerTextBox->Wrap( -1 );
	m_restoreFromBackupFilePickerTextBox->Hide();

	gSizer3->Add( m_restoreFromBackupFilePickerTextBox, 0, wxALL, 5 );

	m_restoreFromBackupFileLocationPicker = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.zip"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	m_restoreFromBackupFileLocationPicker->Hide();

	gSizer3->Add( m_restoreFromBackupFileLocationPicker, 0, wxALL, 5 );


	bSizer1->Add( gSizer3, 1, wxEXPAND, 5 );

	wxGridSizer* gSizer4;
	gSizer4 = new wxGridSizer( 0, 1, 0, 0 );

	m_startButton = new wxButton( this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer4->Add( m_startButton, 0, wxALIGN_CENTER, 5 );


	bSizer1->Add( gSizer4, 1, wxALIGN_CENTER, 1 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

    // Connect Events
    m_operationSelector->Bind(wxEVT_RADIOBOX, &MyFrame::onOperationBoxClick, this);
    m_startButton->Bind(wxEVT_BUTTON, &MyFrame::onStartButtonClick, this);
	
    // Dialog Box
    m_popupBox = new MyDialog1(this, wxID_ANY, "Hello Everyone!");
    m_popupBox->Show(false);
}

void MyFrame::onOperationBoxClick(wxCommandEvent& event)
{
    if (m_operationSelector->GetSelection() == 0)
    {
        // m_createBackupFilePickerTextBox->Show(true);
        m_restoreFromBackupFilePickerTextBox->Show(false);

        // m_createBackupFileLocationPicker->Show(true);
        m_restoreFromBackupFileLocationPicker->Show(false);
    }
    else
    {
        // m_createBackupFilePickerTextBox->Show(false);
        m_restoreFromBackupFilePickerTextBox->Show(true);

        // m_createBackupFileLocationPicker->Show(false);
        m_restoreFromBackupFileLocationPicker->Show(true);
    }

    // gSizer3->Update();
    this->Layout();
    this->Refresh();
    // this->Fit();

    event.Skip();
}

void MyFrame::onStartButtonClick(wxCommandEvent& event)
{
	std::filesystem::path user_library_location(std::string(m_userLibraryPicker->GetPath().mb_str()));

    std::cout << user_library_location << std::endl;

	// std::string backup_creation_path = std::string(m_createBackupFileLocationPicker->GetPath().mb_str());

	std::string backup_restore_path = std::string(m_restoreFromBackupFileLocationPicker->GetPath().mb_str());

    std::cout << backup_restore_path << std::endl;

    if (m_operationSelector->GetSelection() == 0)
    {
        if (user_library_location == "" || !std::filesystem::is_directory(user_library_location))
        {
            wxMessageBox(_("Please Enter A Valid Directory For User Library"), _("Error"), wxICON_ERROR, this);

            event.Skip();

            return;
        }

        createBackupFolderAndPopulate(user_library_location);

        wxFileDialog 
        saveFileDialog(this, _("Save ZIP file"), "", "",
                        "ZIP files (*.zip)|*.zip", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

        saveFileDialog.ShowModal();

        createBackupZipFile(std::string(saveFileDialog.GetPath().mb_str()));
    }
    else
    {
        if (user_library_location == "" || !std::filesystem::is_directory(user_library_location))
        {
            wxMessageBox(_("Please Enter A Valid Directory For User Library"), _("Error"), wxICON_ERROR, this);

            event.Skip();

            return;
        }

        if (backup_restore_path == ""   || !std::filesystem::is_regular_file(backup_restore_path))
        {
            wxMessageBox(_("Please Enter A Valid Backup File"), _("Error"), wxICON_ERROR, this);

            event.Skip();

            return;  
        }

        // TODO: Restore From Backup
    }

	// m_popupBox->m_popupBoxTextBox->SetLabel(user_library_location);

	// m_popupBox->Layout();
	// m_popupBox->Refresh();

    // m_popupBox->Show(true);
    // m_popupBox->ShowModal();



    event.Skip();
}