///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.0.0-0-g0efcecf)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "SailawayNMEAgui.h"

///////////////////////////////////////////////////////////////////////////

DlgDef::DlgDef( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetForegroundColour( wxColour( 0, 0, 0 ) );
	this->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem( m_menu1, wxID_ANY, wxString( _("Download") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem1 );

	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem( m_menu1, wxID_ANY, wxString( _("Ports Saved") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem3 );

	m_menubar1->Append( m_menu1, _("Boats") );

	m_menu2 = new wxMenu();
	m_menuItem2 = new wxMenuItem( m_menu2, wxID_ANY, wxString( _("Guide") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem2 );

	m_menubar1->Append( m_menu2, _("Help") );

	this->SetMenuBar( m_menubar1 );

	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizerPort;
	sbSizerPort = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Port:") ), wxVERTICAL );

	m_textCtrlPort = new wxTextCtrl( sbSizerPort->GetStaticBox(), wxID_ANY, _("57343"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerPort->Add( m_textCtrlPort, 0, wxALL|wxEXPAND, 5 );


	bSizerMain->Add( sbSizerPort, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizerFolder;
	sbSizerFolder = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Boat Settings") ), wxVERTICAL );

	m_staticText2 = new wxStaticText( sbSizerFolder->GetStaticBox(), wxID_ANY, _("User name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	sbSizerFolder->Add( m_staticText2, 0, wxALL, 5 );

	m_textCtrlUser = new wxTextCtrl( sbSizerFolder->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerFolder->Add( m_textCtrlUser, 0, wxALL|wxEXPAND, 5 );

	m_buttonLoadBoats = new wxButton( sbSizerFolder->GetStaticBox(), wxID_ANY, _("Load Boats"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonLoadBoats->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	m_buttonLoadBoats->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );

	sbSizerFolder->Add( m_buttonLoadBoats, 0, wxALL|wxEXPAND, 5 );

	m_comboBoxBoat = new wxComboBox( sbSizerFolder->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	sbSizerFolder->Add( m_comboBoxBoat, 0, wxALL|wxEXPAND, 5 );

	m_staticline1 = new wxStaticLine( sbSizerFolder->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_staticline1->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	sbSizerFolder->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );

	wxStaticBoxSizer* sbSizerTransducerDepth;
	sbSizerTransducerDepth = new wxStaticBoxSizer( new wxStaticBox( sbSizerFolder->GetStaticBox(), wxID_ANY, _("Transducer Depth:") ), wxVERTICAL );

	m_textCtrlTransducerDepth = new wxTextCtrl( sbSizerTransducerDepth->GetStaticBox(), wxID_ANY, _("1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrlTransducerDepth->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	sbSizerTransducerDepth->Add( m_textCtrlTransducerDepth, 0, wxALL|wxEXPAND, 5 );


	sbSizerFolder->Add( sbSizerTransducerDepth, 1, wxEXPAND, 5 );

	m_text = new wxTextCtrl( sbSizerFolder->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_WORDWRAP|wxHSCROLL|wxVSCROLL );
	m_text->SetMinSize( wxSize( -1,120 ) );

	sbSizerFolder->Add( m_text, 0, wxALL|wxEXPAND, 5 );

	m_staticTextStatus = new wxStaticText( sbSizerFolder->GetStaticBox(), wxID_ANY, _("Status:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextStatus->Wrap( -1 );
	sbSizerFolder->Add( m_staticTextStatus, 0, wxALL, 5 );

	m_status = new wxTextCtrl( sbSizerFolder->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerFolder->Add( m_status, 0, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( sbSizerFolder->GetStaticBox(), wxID_ANY, wxEmptyString ), wxVERTICAL );

	m_checkBoxDR = new wxCheckBox( sbSizer4->GetStaticBox(), wxID_ANY, _("Use Dead Reckoning"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxDR->SetValue(true);
	sbSizer4->Add( m_checkBoxDR, 0, wxALL|wxEXPAND, 5 );


	sbSizerFolder->Add( sbSizer4, 1, wxEXPAND, 5 );


	bSizerMain->Add( sbSizerFolder, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonStart = new wxButton( this, wxID_ANY, _("Start Server"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonStart->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	m_buttonStart->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );

	bSizer7->Add( m_buttonStart, 0, wxALL, 5 );

	m_buttonStop = new wxButton( this, wxID_ANY, _("Stop Server"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonStop->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	m_buttonStop->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );

	bSizer7->Add( m_buttonStop, 0, wxALL, 5 );


	bSizerMain->Add( bSizer7, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );


	bSizerMain->Add( bSizer5, 1, wxEXPAND, 5 );


	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
	m_timerData.SetOwner( this, m_timerData.GetId() );
	m_timerFeed.SetOwner( this, m_timerFeed.GetId() );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DlgDef::OnClose ) );
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DlgDef::OnDownload ), this, m_menuItem1->GetId());
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DlgDef::OnGetSavedTides ), this, m_menuItem3->GetId());
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DlgDef::OnInformation ), this, m_menuItem2->GetId());
	m_textCtrlUser->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DlgDef::OnLoadBoats ), NULL, this );
	m_buttonLoadBoats->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgDef::OnLoadBoats ), NULL, this );
	m_textCtrlTransducerDepth->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DlgDef::OnLoadBoats ), NULL, this );
	m_buttonStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgDef::OnStartServer ), NULL, this );
	m_buttonStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgDef::OnStopServer ), NULL, this );
	this->Connect( m_timerData.GetId(), wxEVT_TIMER, wxTimerEventHandler( DlgDef::OnTimerData ) );
	this->Connect( m_timerFeed.GetId(), wxEVT_TIMER, wxTimerEventHandler( DlgDef::OnTimerFeed ) );
}

DlgDef::~DlgDef()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DlgDef::OnClose ) );
	m_textCtrlUser->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DlgDef::OnLoadBoats ), NULL, this );
	m_buttonLoadBoats->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgDef::OnLoadBoats ), NULL, this );
	m_textCtrlTransducerDepth->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( DlgDef::OnLoadBoats ), NULL, this );
	m_buttonStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgDef::OnStartServer ), NULL, this );
	m_buttonStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgDef::OnStopServer ), NULL, this );
	this->Disconnect( m_timerData.GetId(), wxEVT_TIMER, wxTimerEventHandler( DlgDef::OnTimerData ) );
	this->Disconnect( m_timerFeed.GetId(), wxEVT_TIMER, wxTimerEventHandler( DlgDef::OnTimerFeed ) );

}
