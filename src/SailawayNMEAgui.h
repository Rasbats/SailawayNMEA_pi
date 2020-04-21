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

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/combobox.h>
#include <wx/statline.h>
#include <wx/checkbox.h>
#include <wx/timer.h>
#include <wx/frame.h>
#include <wx/event.h>
#include "ocpn_plugin.h"

///////////////////////////////////////////////////////////////////////////////
/// Class DlgDef
///////////////////////////////////////////////////////////////////////////////
class DlgDef : public wxFrame
{
	private:

	protected:
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		wxMenu* m_menu2;
		wxStaticText* m_staticText2;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticTextStatus;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		
		virtual void OnGetSavedTides( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnInformation( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoadBoats( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoadBoatData(wxCommandEvent& event) { event.Skip(); }
		virtual void OnTestServer( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStartServer( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStopServer( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimerFeed( wxTimerEvent& event ) { event.Skip(); }
		virtual void OnTimerData(wxTimerEvent& event) { event.Skip(); }
		virtual void onDLEvent(OCPN_downloadEvent &ev) { ev.Skip(); }

	public:
		wxMenuItem* m_menuItem2;
		wxTextCtrl* m_textCtrlPort;
		wxTextCtrl* m_textCtrlUser;
		wxButton* m_buttonLoadBoats;
		wxComboBox* m_comboBoxBoat;
		wxCheckBox* m_checkBoxDR;
		wxTextCtrl* m_textCtrlTransducerDepth;
		wxTextCtrl* m_text;
		wxTextCtrl* m_status;
		wxButton* m_buttonStart;
		wxButton* m_buttonStop;
		wxTimer m_timerData;
		wxTimer m_timerFeed;

		DECLARE_EVENT_TABLE()

		DlgDef( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("SailawayNMEA"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );

		~DlgDef();

};

