///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.0.0-0-g0efcecf)
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

///////////////////////////////////////////////////////////////////////////


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

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnDownload( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGetSavedTides( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnInformation( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLoadBoats( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStartServer( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStopServer( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTimerData( wxTimerEvent& event ) { event.Skip(); }
		virtual void OnTimerFeed( wxTimerEvent& event ) { event.Skip(); }


	public:
		wxMenuItem* m_menuItem2;
		wxTextCtrl* m_textCtrlPort;
		wxTextCtrl* m_textCtrlUser;
		wxButton* m_buttonLoadBoats;
		wxComboBox* m_comboBoxBoat;
		wxTextCtrl* m_textCtrlTransducerDepth;
		wxTextCtrl* m_text;
		wxTextCtrl* m_status;
		wxCheckBox* m_checkBoxDR;
		wxButton* m_buttonStart;
		wxButton* m_buttonStop;
		wxTimer m_timerData;
		wxTimer m_timerFeed;

		DlgDef( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("SailawayNMEA"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_NO_TASKBAR|wxRESIZE_BORDER|wxSYSTEM_MENU|wxTAB_TRAVERSAL );

		~DlgDef();

};

