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

#ifndef _CALCULATORGUI_IMPL_H_
#define _CALCULATORGUI_IMPL_H_

#ifdef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "NMEASentenceGenerator.h"
#include "InstrumentsData.h"
#include "SailawayNMEAgui.h"
#include "SailawayNMEA_pi.h"
#include "NavFunc.h"
#include "tidetable.h"
#include "tinyxml.h"
#include "wx/stdpaths.h"

#include <list>
#include <vector>
#include "wx/socket.h"

#if defined (__WXMSW__)
    #include <winsock.h>
#endif

#if defined (__APPLE__) && defined (__MACH__)
    #include <sys/types.h>
    #include <sys/socket.h>
#elif defined (__POSIX__)
    #include <sys/types.h>
    #include <sys/socket.h>
#endif

#include <wx/timer.h>
#include <wx/ffile.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/url.h>
#include "jsoncpp/json/json.h"
#include "ocpn_plugin.h"
#include <wx/time.h>
#include "wx/dir.h"
#include "wx/busyinfo.h"
#include "wx/sstream.h"
#include "wx/thread.h"


#define MY_SERVER_PORT 57343

using namespace std;

enum
{
	UDP_SOCKET = 57340
};

#define REQUEST_RATE  600000
#define DEAD_RECKONING_RATE 10000
#define MS_TO_KNOTS 1.94384

struct boat
{
	double coordLat;
	double coordLon;
	int heading;
	int magHdg;
	double waterSpeed;
	double groundSpeed;
	//
	int courseOverGround;
	int magneticCourseOverGround;
	//
	double trueWindSpeed;
	int trueWindAngle;
	double ApparentWindSpeed;
	int ApparentWindAngle;

	double depth;
	double TransducerDepth;

	int boatnumber;
	wxString boatname;
	wxString username;
};


class NMEASentenceGenerator;
class InstrumentsData;
class SailawayNMEA_pi;


class Dlg : public DlgDef
{
public:
	Dlg(SailawayNMEA_pi &m_SailawayNMEA_pi, wxWindow* parent);
	~Dlg();

	
	void OnInformation(wxCommandEvent& event);

	SailawayNMEA_pi *plugin;

	wxString m_default_configuration_path;
	void AutoSizeHeader(wxListCtrl *const list_ctrl);

	wxString StandardPath();
	
	void OnLoadBoats(wxCommandEvent& event);
	void OnLoadBoatData(wxCommandEvent& event);
    void onDLEvent(OCPN_downloadEvent &ev);
	
	void OnStartServer(wxCommandEvent& event);
	void OnStopServer(wxCommandEvent& event);

	void LoadBoats();
	void LoadBoatData();
	boat FindNewBoatposition(boat drBoat);
	void GenerateDRnmeaSentence();
	//void ReLoadBoatData();
	double parseFeature(Json::Value myFeatures, string featureName);

	// for download events
	bool m_bTransferComplete = false;
	bool  m_bTransferSuccess = true;
	wxString m_totalsize = _("Unknown");
	wxString m_transferredsize = _T("0");
	bool useDR;
	
private:

	

	bool startDR;

	wxLongLong llElapsedTime = 0;
	wxLongLong m_llTimerStartTick;
	wxLongLong m_llTimerStopTick;

	wxLongLong llElapsedDownloadTime = 0;
	wxLongLong m_llTimerDownloadStartTick;
	wxLongLong m_llTimerDownloadStopTick;

	wxString key = "757a733e42e9efc9c9bd3b6e503721a4";
	wxString andusrname = "&usrname=";
	wxString usrname; //"bats";
	wxString andubtnr = "&ubtnr=";
	wxString selectedBoat;

	vector<boat>allMyBoats;
	
	void Init_Datagram_Socket();
	
	bool            m_busy;
	bool            serverRunning;
	int             m_numClients;
	wxString        m_input;
	string nmea = "";

	boat myBoat;
	boat drBoat;
	
	NMEASentenceGenerator* myGenerator;
	InstrumentsData* myData;

	void OnUDPEvent(wxSocketEvent& event);
	void OnTimerData(wxTimerEvent& event);
	void OnTimerFeed(wxTimerEvent& event);
	void NMEASend(wxString myMessage);
	
	wxIPV4address m_BroadCastAddress; // For broadcast sending
	wxIPV4address m_LocalAddress;     // For listening
	wxDatagramSocket* m_Listen_Socket;

	DECLARE_EVENT_TABLE()


	void OnClose( wxCloseEvent& event );	
    bool dbg;
};


#endif
