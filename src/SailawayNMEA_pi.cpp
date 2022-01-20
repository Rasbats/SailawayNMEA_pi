/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  SailawayNMEA Plugin
 * Author:   Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2020 by Mike Rossiter                                *
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

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include "SailawayNMEA_pi.h"
#include "SailawayNMEAgui_impl.h"
#include "SailawayNMEAgui.h"

#include <wx/stdpaths.h>


class SailawayNMEA_pi;

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new SailawayNMEA_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}


//---------------------------------------------------------------------------------------------------------
//
//   SailawayNMEA Plugin Implementation
//
//---------------------------------------------------------------------------------------------------------

#define SAILAWAYNMEA_TOOL_POSITION    -1 
#include "icons.h"

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

/**
 * Load a icon, possibly using SVG
 * Parameters
 *  - api_name: Argument to GetPluginDataDir()
 *  - icon_name: Base name of icon living in data/ directory. When using
 *    SVG icon_name.svg is used, otherwise icon_name.png
 */

static wxBitmap load_plugin(const char* icon_name, const char* api_name) {
    wxBitmap bitmap; 
    wxFileName fn;
    auto path = GetPluginDataDir(api_name);
    fn.SetPath(path);
    fn.AppendDir("data");
    fn.SetName(icon_name);
#ifdef SailawayNMEA_USE_SVG
    wxLogDebug("Loading SVG icon");
    fn.SetExt("svg");
    const static int ICON_SIZE = 48;  // FIXME: Needs size from GUI 
    bitmap = GetBitmapFromSVGFile(fn.GetFullPath(), ICON_SIZE, ICON_SIZE);
#else
    wxLogDebug("Loading png icon");
    fn.SetExt("png");
    path = fn.GetFullPath();
    if (!wxImage::CanRead(path)) {
        wxLogDebug("Initiating image handlers.");
        wxInitAllImageHandlers();
    }
    wxImage panelIcon(path);
    bitmap = wxBitmap(panelIcon);
#endif
    wxLogDebug("Icon loaded, result: %s", bitmap.IsOk() ? "ok" : "fail");
    return bitmap;
}



SailawayNMEA_pi::SailawayNMEA_pi(void *ppimgr)
      :opencpn_plugin_116 (ppimgr)
{
      // Create the PlugIn icons
      initialize_images();
      m_panelBitmap = load_plugin("SailawayNMEA_panel_icon", "SailawayNMEA");	 
	  m_bShowSAILAWAYNMEA = false;
}

SailawayNMEA_pi::~SailawayNMEA_pi(void)
{
     delete _img_SAILAWAYNMEA;
     
}

BEGIN_EVENT_TABLE(DlgDef, wxWindow)
END_EVENT_TABLE()

int SailawayNMEA_pi::Init(void)
{
      AddLocaleCatalog("opencpn-SailawayNMEA_pi");

      // Set some default private member parameters
      m_route_dialog_x = 0;
      m_route_dialog_y = 0;
      ::wxDisplaySize(&m_display_width, &m_display_height);

      //    Get a pointer to the opencpn display canvas, to use as a parent for the POI Manager dialog
      m_parent_window = GetOCPNCanvasWindow();

      //    Get a pointer to the opencpn configuration object
      m_pconfig = GetOCPNConfigObject();

      //    And load the configuration items
      LoadConfig();

      //    This PlugIn needs a toolbar icon, so request its insertion
	if(m_bSAILAWAYNMEAShowIcon)
     
#ifdef SailawayNMEA_USE_SVG
	m_leftclick_tool_id = InsertPlugInToolSVG("SailawayNMEA", _svg_SAILAWAYNMEA, _svg_SAILAWAYNMEA, _svg_SAILAWAYNMEA_toggled,
		wxITEM_CHECK, _("SailawayNMEA"), "", NULL, SAILAWAYNMEA_TOOL_POSITION, 0, this);
#else
	 m_leftclick_tool_id  = InsertPlugInTool("", _img_SAILAWAYNMEA, _img_SAILAWAYNMEA, wxITEM_CHECK,
            _("SailawayNMEA"), "", NULL,
             SAILAWAYNMEA_TOOL_POSITION, 0, this);
#endif

	wxMenu dummy_menu;
	m_position_menu_id = AddCanvasContextMenuItem

	(new wxMenuItem(&dummy_menu, -1, _("Not used")), this);
	SetCanvasContextMenuItemViz(m_position_menu_id, false);

     m_pDialog = NULL;	 

      return (WANTS_OVERLAY_CALLBACK |
              WANTS_OPENGL_OVERLAY_CALLBACK |		           
              WANTS_TOOLBAR_CALLBACK    |
              INSTALLS_TOOLBAR_TOOL     |
              WANTS_CONFIG            
           );
}

bool SailawayNMEA_pi::DeInit(void)
{
      //    Record the dialog position
      if (NULL != m_pDialog)
      {
            //Capture dialog position
            wxPoint p = m_pDialog->GetPosition();
            SetCalculatorDialogX(p.x);
            SetCalculatorDialogY(p.y);
            m_pDialog->Close();
            delete m_pDialog;
            m_pDialog = NULL;

			m_bShowSAILAWAYNMEA = false;
			SetToolbarItemState( m_leftclick_tool_id, m_bShowSAILAWAYNMEA );

      }	
    
    SaveConfig();

    RequestRefresh(m_parent_window); // refresh mainn window

    return true;
}


int SailawayNMEA_pi::GetAPIVersionMajor()
{
      return atoi(API_VERSION);
}

int SailawayNMEA_pi::GetAPIVersionMinor()
{
    std::string v(API_VERSION);
    size_t dotpos = v.find('.');
    return atoi(v.substr(dotpos + 1).c_str());
}

int SailawayNMEA_pi::GetPlugInVersionMajor()
{
      return PLUGIN_VERSION_MAJOR;
}

int SailawayNMEA_pi::GetPlugInVersionMinor()
{
      return PLUGIN_VERSION_MINOR;
}

wxBitmap *SailawayNMEA_pi::GetPlugInBitmap()
{
      return &m_panelBitmap;
}

wxString SailawayNMEA_pi::GetCommonName()
{
      return _("SailawayNMEA");
}


wxString SailawayNMEA_pi::GetShortDescription()
{
      return _("SailawayNMEA");
}

wxString SailawayNMEA_pi::GetLongDescription()
{
      return _("Creates NMEA sentences for OpenCPN from Sailaway simgame");
}

int SailawayNMEA_pi::GetToolbarToolCount(void)
{
      return 1;
}

void SailawayNMEA_pi::SetColorScheme(PI_ColorScheme cs)
{
      if (NULL == m_pDialog)
            return;

      DimeWindow(m_pDialog);
}

void SailawayNMEA_pi::OnToolbarToolCallback(int id)
{
    
	if(NULL == m_pDialog)
      {
            m_pDialog = new Dlg(*this, m_parent_window);

            m_pDialog->plugin = this;
            m_pDialog->Move(wxPoint(m_route_dialog_x, m_route_dialog_y));
			
      }

	  m_pDialog->Fit();
	  //Toggle 
	  m_bShowSAILAWAYNMEA = !m_bShowSAILAWAYNMEA;	  

      //    Toggle dialog? 
      if(m_bShowSAILAWAYNMEA) {
          m_pDialog->Show();         
      } else
          m_pDialog->Hide();
     
      // Toggle is handled by the toolbar but we must keep plugin manager b_toggle updated
      // to actual status to ensure correct status upon toolbar rebuild
      SetToolbarItemState( m_leftclick_tool_id, m_bShowSAILAWAYNMEA );

      RequestRefresh(m_parent_window); // refresh main window
}

bool SailawayNMEA_pi::LoadConfig(void)
{
      wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

      if(pConf)
      {
            pConf->SetPath ( _T( "/Settings/SailawayNMEA_pi" ) );
			 pConf->Read ( _T( "ShowSAILAWAYNMEAIcon" ), &m_bSAILAWAYNMEAShowIcon, 1 );
           
            m_route_dialog_x =  pConf->Read ( _T ( "DialogPosX" ), 20L );
            m_route_dialog_y =  pConf->Read ( _T ( "DialogPosY" ), 20L );
         
            if((m_route_dialog_x < 0) || (m_route_dialog_x > m_display_width))
                  m_route_dialog_x = 5;
            if((m_route_dialog_y < 0) || (m_route_dialog_y > m_display_height))
                  m_route_dialog_y = 5;
            return true;
      }
      else
            return false;
}

bool SailawayNMEA_pi::SaveConfig(void)
{
      wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

      if(pConf)
      {
            pConf->SetPath ( _T ( "/Settings/SailawayNMEA_pi" ) );
			pConf->Write ( _T ( "ShowSAILAWAYNMEAIcon" ), m_bSAILAWAYNMEAShowIcon );
          
            pConf->Write ( _T ( "DialogPosX" ),   m_route_dialog_x );
            pConf->Write ( _T ( "DialogPosY" ),   m_route_dialog_y );
            
            return true;
      }
      else
            return false;
}

void SailawayNMEA_pi::OnSAILAWAYNMEADialogClose()
{
    m_bShowSAILAWAYNMEA = false;
    SetToolbarItemState( m_leftclick_tool_id, m_bShowSAILAWAYNMEA );
    m_pDialog->Hide();
    SaveConfig();

    RequestRefresh(m_parent_window); // refresh main window

}

void SailawayNMEA_pi::OnClose(wxCloseEvent& event)
{
	plugin->OnSAILAWAYNMEADialogClose();
}
