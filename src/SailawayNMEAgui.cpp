/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  SailawayNMEA Plugin
 * Author:   Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2020 by Mike Rossiter                                   *
 *   $EMAIL$                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */
///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
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

	m_textCtrlUser = new wxTextCtrl( sbSizerFolder->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	sbSizerFolder->Add( m_textCtrlUser, 0, wxALL|wxEXPAND, 5 );

	m_buttonLoadBoats = new wxButton( sbSizerFolder->GetStaticBox(), wxID_ANY, _("Load Boats"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerFolder->Add( m_buttonLoadBoats, 0, wxALL|wxEXPAND, 5 );

	m_comboBoxBoat = new wxComboBox( sbSizerFolder->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	sbSizerFolder->Add( m_comboBoxBoat, 0, wxALL|wxEXPAND, 5 );

	m_staticline1 = new wxStaticLine(sbSizerFolder->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	sbSizerFolder->Add(m_staticline1, 0, wxEXPAND | wxALL, 5);

	wxStaticBoxSizer* sbSizerTransducerDepth;
	sbSizerTransducerDepth = new wxStaticBoxSizer(new wxStaticBox(sbSizerFolder->GetStaticBox(), wxID_ANY, _("Transducer Depth:")), wxVERTICAL);

	m_textCtrlTransducerDepth = new wxTextCtrl(sbSizerTransducerDepth->GetStaticBox(), wxID_ANY, _("1.0"), wxDefaultPosition, wxDefaultSize, 0);
	sbSizerTransducerDepth->Add(m_textCtrlTransducerDepth, 0, wxALL | wxEXPAND, 5);

	sbSizerFolder->Add(sbSizerTransducerDepth, 1, wxEXPAND, 5);

	m_text = new wxTextCtrl( sbSizerFolder->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_WORDWRAP|wxTE_MULTILINE |wxVSCROLL );
	m_text->SetMinSize( wxSize( -1,120 ) );

	sbSizerFolder->Add( m_text, 0, wxALL|wxEXPAND, 5 );

	m_staticTextStatus = new wxStaticText( sbSizerFolder->GetStaticBox(), wxID_ANY, _("Status:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextStatus->Wrap( -1 );
	sbSizerFolder->Add( m_staticTextStatus, 0, wxALL, 5 );

	m_status = new wxTextCtrl( sbSizerFolder->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizerFolder->Add( m_status, 0, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer(new wxStaticBox(sbSizerFolder->GetStaticBox(), wxID_ANY, wxEmptyString), wxVERTICAL);

	m_checkBoxDR = new wxCheckBox(sbSizer4->GetStaticBox(), wxID_ANY, _("Use Dead Reckoning"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkBoxDR->SetValue(true);
	sbSizer4->Add(m_checkBoxDR, 0, wxALL | wxEXPAND, 5);


	sbSizerFolder->Add(sbSizer4, 1, wxEXPAND, 5);

	bSizerMain->Add( sbSizerFolder, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonStart = new wxButton( this, wxID_ANY, _("Start Server"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_buttonStart, 0, wxALL, 5 );

	m_buttonStop = new wxButton( this, wxID_ANY, _("Stop Server"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_buttonStop, 0, wxALL, 5 );


	bSizerMain->Add( bSizer7, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );


	bSizerMain->Add( bSizer5, 1, wxEXPAND, 5 );


	this->SetSizer( bSizerMain );
	this->Layout();
	bSizerMain->Fit( this );
	m_timerData.SetOwner(this, 1002);
	m_timerFeed.SetOwner(this, 1001);

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DlgDef::OnClose ) );
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DlgDef::OnLoadBoatData ), this, m_menuItem1->GetId());
	m_menu2->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( DlgDef::OnInformation ), this, m_menuItem2->GetId());
	m_textCtrlUser->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(DlgDef::OnLoadBoats), NULL, this);
	m_buttonLoadBoats->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgDef::OnLoadBoats ), NULL, this );
	m_buttonStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgDef::OnStartServer ), NULL, this );
	m_buttonStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgDef::OnStopServer ), NULL, this );
	this->Connect(wxID_ANY, wxEVT_TIMER, wxTimerEventHandler(DlgDef::OnTimerData));
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( DlgDef::OnTimerFeed ) );

	Connect(wxEVT_DOWNLOAD_EVENT, (wxObjectEventFunction)(wxEventFunction)&DlgDef::onDLEvent);
}

DlgDef::~DlgDef()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DlgDef::OnClose ) );
	m_textCtrlUser->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(DlgDef::OnLoadBoats), NULL, this);
	m_buttonLoadBoats->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgDef::OnLoadBoats ), NULL, this );
	m_buttonStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgDef::OnStartServer ), NULL, this );
	m_buttonStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DlgDef::OnStopServer ), NULL, this );
	this->Disconnect(wxID_ANY, wxEVT_TIMER, wxTimerEventHandler(DlgDef::OnTimerData));
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( DlgDef::OnTimerFeed ) );

	Disconnect(wxEVT_DOWNLOAD_EVENT, (wxObjectEventFunction)(wxEventFunction)&DlgDef::onDLEvent);

}
