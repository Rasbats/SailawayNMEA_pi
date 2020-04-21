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

#include "SailawayNMEAgui_impl.h"
#include <wx/wx.h>
#include "wx/dir.h"


#include <wx/ffile.h>
#include <wx/filefn.h>
#include <wx/url.h>
#include "jsoncpp/json/json.h"
#include "wx/busyinfo.h"
#include "wx/socket.h"
#include "wx/sstream.h"
#include "wx/thread.h"
#include "wx/scopedptr.h"


class Position;
class SailawayNMEA_pi;


Dlg::Dlg(SailawayNMEA_pi &m_SailawayNMEA_pi, wxWindow* parent):	DlgDef(parent)

{	
	this->Fit();
    dbg=false; //for debug output set to true
 
	wxString blank_name = *GetpSharedDataLocation()
		+ "plugins/SailawayNMEA_pi/data/blank.ico";

	wxIcon icon(blank_name, wxBITMAP_TYPE_ICO);
	SetIcon(icon);

	wxString myOpenCPNiconsPath = StandardPath();
	wxString s = wxFileName::GetPathSeparator();	
}

Dlg::~Dlg()
{
}

void Dlg::OnInformation(wxCommandEvent& event)
{
	
	wxString infolocation = *GetpSharedDataLocation()
		+ "plugins/SailawayNMEA_pi/data/pictures/" + "SailawayNMEA.html";
	wxLaunchDefaultBrowser("file:///" + infolocation);

}

void Dlg::AutoSizeHeader(wxListCtrl *const list_ctrl)
{
	if (list_ctrl)
	{
		for (int i = 0; i < list_ctrl->GetColumnCount(); ++i)
		{
			list_ctrl->SetColumnWidth(i, wxLIST_AUTOSIZE);
			const int a_width = list_ctrl->GetColumnWidth(i);
			list_ctrl->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
			const int h_width = list_ctrl->GetColumnWidth(i);
			list_ctrl->SetColumnWidth(i, (std::max)(a_width, h_width));
		}
	}
}

void Dlg::OnClose(wxCloseEvent& event)
{
	plugin->OnSAILAWAYNMEADialogClose();
}

wxString Dlg::StandardPath()
{
	wxStandardPathsBase& std_path = wxStandardPathsBase::Get();
	wxString s = wxFileName::GetPathSeparator();

#if defined(__WXMSW__)
	wxString stdPath = std_path.GetConfigDir();
#elif defined(__WXGTK__) || defined(__WXQT__)
	wxString stdPath = std_path.GetUserDataDir();
#elif defined(__WXOSX__)
	wxString stdPath = (std_path.GetUserConfigDir() + s + "opencpn");
#endif

	stdPath += s + "plugins" + s + "SAILAWAYNMEA";
	if (!wxDirExists(stdPath)) 
		wxMkdir(stdPath);		

#ifdef __WXOSX__	
	wxString oldPath = (std_path.GetUserConfigDir());
	if (wxDirExists(oldPath) && !wxDirExists(stdPath)) {
		wxLogMessage("SailawayNMEA_pi: moving config dir %s to %s", oldPath, stdPath);
		wxRenameFile(oldPath, stdPath);
	}
#endif

	stdPath += s; // is this necessary?
	return stdPath;
}

void Dlg::OnLoadBoats(wxCommandEvent& event) {

	LoadBoats();

}

void Dlg::LoadBoats() {

	string name;
	wxString myname;
    boat* myNewBoat = new boat;

	wxString key = "757a733e42e9efc9c9bd3b6e503721a4";
	wxString andusrname = "&usrname=";
	wxString usrname = m_textCtrlUser->GetValue(); // "bats";
	if (usrname == "") {
		wxMessageBox("No user name entered");
		return;
	}

	myNewBoat->username = usrname;

	allMyBoats.clear();
	m_comboBoxBoat->Clear();

	wxString urlString = "https://backend.sailaway.world/cgi-bin/sailaway/TrackAllBoats.pl?key=" + key + andusrname + usrname;

	wxURI url(urlString);
	wxString tmp_file = wxFileName::CreateTempFileName(""); 
	
	m_bTransferComplete = false;
	m_bTransferSuccess = true;
	m_totalsize = _("Unknown");
	m_transferredsize = _T("0");

	long handle;
	OCPN_downloadFileBackground(url.BuildURI(), tmp_file, this, &handle);

	while (!m_bTransferComplete && m_bTransferSuccess)
	{
		wxYield();
		wxMilliSleep(30);
	}

	if (m_bTransferSuccess) {
		m_status->SetValue("Boats for this user are found");
	}
	else {
		m_status->SetValue("No user boats");
		return;
	}

	wxMilliSleep(1000);

	wxString myjson;
	wxFFile fileData;
	fileData.Open(tmp_file, wxT("r"));
	fileData.ReadAll(&myjson);

	// construct the JSON root object
	Json::Value  root;
	// construct a JSON parser
	Json::Reader reader;
	wxString error = _("SailawayNMEA ... No boats found");

	if (!reader.parse((std::string)myjson, root)) {
		wxLogMessage(error);
		return;
	}

	if (!root.isMember("boats")) {
		// Originator
		wxLogMessage(_("SailawayNMEA ... No boats features found in message"));
		return;
	}



	int i = root["boats"].size();

	for (int j = 0; j < i; j++) {

		
			Json::Value  features = root["boats"][j];

			if (!features.isMember("ubtname")) {
				// Originator
				wxLogMessage(_("No properties found in message"));
				wxMessageBox("User not found");
			}

			name = features["ubtname"].asString();
			string name = features["ubtname"].asString();
			wxString myboatname(name.c_str(), wxConvUTF8);

			myNewBoat->boatname = myboatname;

			if (!features.isMember("ubtnr")) {
				// Originator
				wxLogMessage(_("No properties found in message"));
				wxMessageBox("Not found");
			}

			name = features["ubtnr"].asString();
			wxString myboatnumber(name.c_str(), wxConvUTF8);

			int boatnum;
			boatnum = wxAtoi(myboatnumber);
			myNewBoat->boatnumber = boatnum;

			allMyBoats.push_back(*myNewBoat);
	}

		for (std::vector<boat>::iterator it = allMyBoats.begin(); it != allMyBoats.end(); it++) {

			wxString boatName = (*it).boatname;
			m_comboBoxBoat->Append(boatName);
		}
		m_comboBoxBoat->SetSelection(0);
		
		fileData.Close();
		wxRemoveFile(tmp_file);
		root.clear();
		RequestRefresh(m_parent);

}

void Dlg::OnLoadBoatData(wxCommandEvent& event) {

	LoadBoatData();
}

void Dlg::LoadBoatData() {

	string name;
	wxString myname;

	usrname = m_textCtrlUser->GetValue(); 

	wxString selectedBoat = m_comboBoxBoat->GetStringSelection();

	int boatnum;
	wxString boatName;
	for (std::vector<boat>::iterator it = allMyBoats.begin(); it != allMyBoats.end(); it++) {

		boatName = (*it).boatname;
		if (boatName == selectedBoat) {
			boatnum = (*it).boatnumber;
		}
	}

	wxString ubtnr = wxString::Format(wxT("%i"), boatnum);  // "134144";
	
	if ((ubtnr == "") || (usrname == "" || m_comboBoxBoat->IsTextEmpty())) {
		wxMessageBox("No user name given or ...\n  the boat name is not selected");
		return;
	}

	wxString urlString = "https://backend.sailaway.world/cgi-bin/sailaway/TrackAllBoats.pl?key=" + key + andusrname + usrname + andubtnr + ubtnr;

	wxURI url(urlString);
	wxString tmp_file = wxFileName::CreateTempFileName("");
	
	long handle;
	OCPN_downloadFileBackground(url.BuildURI(), tmp_file, this, &handle);

	while (!m_bTransferComplete && m_bTransferSuccess)
	{
		wxYield();
		wxMilliSleep(30);
	}

	if (m_bTransferSuccess) {
		m_status->SetValue("Boat data update");
	}
	else {
		m_status->SetValue("Failure: No boat data");
		return;
	}

	wxMilliSleep(1000);
	
	wxString myjson;
	wxFFile fileData;
	fileData.Open(tmp_file, wxT("r"));
	fileData.ReadAll(&myjson);

	// construct the JSON root object
	Json::Value  root;
	// construct a JSON parser
	Json::Reader reader;
	wxString error = _("Failure: No boat data found");

	if (!reader.parse((std::string)myjson, root)) {
		wxLogMessage(error);
		return;
	}

	if (!root.isMember("boats")) {
		// Originator
		wxLogMessage(_("SailawayNMEA ... No boat features found in message"));
		return;
	}

	int i = root["boats"].size();

	for (int j = 0; j < i; j++) {

		if (j == 0) { // there should only be one boat

			Json::Value  features = root["boats"][j];

			myData = new InstrumentsData();  // need to create these objects before using them!
			myGenerator = new NMEASentenceGenerator();
			
			myData->lat(parseFeature(features, "ubtlat"));
			myData->lon(parseFeature(features, "ubtlon"));
			//
			myData->Heading(parseFeature(features, "ubtheading"));
			myData->CourseOverGround(parseFeature(features, "ubtcourseoverground"));
			//
			myData->waterSpd(parseFeature(features, "ubtspeed")*MS_TO_KNOTS);
			myData->SpeedOverGround(parseFeature(features, "ubtspeedoverground")*MS_TO_KNOTS);
			//
			myData->TrueWindSpeed(parseFeature(features, "ubttruewindspeed")*MS_TO_KNOTS);
			myData->TrueWindAngle(parseFeature(features, "ubttruewindangle"));

			int windAngle;
			if (myData->TrueWindAngle() < 0) windAngle = myData->TrueWindAngle() + 360;
			myData->TrueWindAngle(windAngle);
			//
			myData->ApparentWindSpeed(parseFeature(features, "ubtappwindspeed")*MS_TO_KNOTS);
			myData->ApparentWindAngle(parseFeature(features, "ubtappwindangle"));

			if (myData->ApparentWindAngle() < 0) windAngle = myData->ApparentWindAngle() + 360;
			myData->ApparentWindAngle(windAngle);
			//			
			myData->Depth(parseFeature(features, "depth"));
			//
			myData->magHdg(0);
			myData->MagneticCourseOverGround(0);
			//
			wxString td = m_textCtrlTransducerDepth->GetValue();
			double tdd;
			td.ToDouble(&tdd);
			myData->TransducerDepth(tdd);
			//
			//
			//
			drBoat.coordLat = myData->lat();
			drBoat.coordLon = myData->lon();
			//
			drBoat.heading = myData->Heading();
			drBoat.magHdg = myData->magHdg();
			//
			drBoat.waterSpeed = myData->waterSpd();	
			drBoat.groundSpeed = myData->SpeedOverGround();
			//		
			drBoat.courseOverGround = myData->CourseOverGround();
			drBoat.magneticCourseOverGround = myData->MagneticCourseOverGround();
			//
			drBoat.trueWindSpeed = myData->TrueWindSpeed();
			drBoat.trueWindAngle = myData->TrueWindAngle();
			drBoat.ApparentWindSpeed = myData->ApparentWindSpeed();
			drBoat.ApparentWindAngle = myData->ApparentWindAngle();
			//
			drBoat.depth = myData->Depth();
			drBoat.TransducerDepth = myData->TransducerDepth();
			//
			//
			nmea = myGenerator->generate(*myData);
			m_status->SetValue("Data download");
			m_text->SetValue(nmea);
			//wxMessageBox(nmea);
		}
	}

	fileData.Close();
	wxRemoveFile(tmp_file);
	root.clear();
	RequestRefresh(m_parent);

	}


boat Dlg::FindNewBoatposition(boat drBoat){
	boat newbtDR;
	double lat = drBoat.coordLat;
	double lon = drBoat.coordLon;
	double hdg = drBoat.heading;
	double spd = (drBoat.waterSpeed)/60/6; // to change later to allow for download interval
	double depth = drBoat.depth;

	//bool destLoxodrome(double lat1, double lon1, double brng, double dist, double* lat2, double* lon2);
	destLoxodrome(lat, lon, hdg, spd, &newbtDR.coordLat, &newbtDR.coordLon);
	
	newbtDR.heading = hdg;
	newbtDR.magHdg = drBoat.magHdg;
	newbtDR.waterSpeed = drBoat.waterSpeed;	
	newbtDR.groundSpeed = drBoat.groundSpeed;
	//
	newbtDR.depth = drBoat.depth;
	newbtDR.TransducerDepth = drBoat.TransducerDepth;
	//
	newbtDR.courseOverGround = drBoat.courseOverGround;			
	newbtDR.magneticCourseOverGround = drBoat.magneticCourseOverGround;
	//
	//
	newbtDR.trueWindSpeed = drBoat.trueWindSpeed;
	newbtDR.trueWindAngle = drBoat.trueWindAngle;
	newbtDR.ApparentWindSpeed = drBoat.ApparentWindSpeed;
	newbtDR.ApparentWindAngle = drBoat.ApparentWindAngle;
	//
	//
	//
	return newbtDR;
}

void Dlg::GenerateDRnmeaSentence() {
	boat calcBoat;
	calcBoat = FindNewBoatposition(drBoat);
	

	myData = new InstrumentsData();  // need to create these objects before using them!
	myGenerator = new NMEASentenceGenerator();

	myData->lat(calcBoat.coordLat);
	myData->lon(calcBoat.coordLon);
	myData->Heading(calcBoat.heading);
	myData->magHdg(calcBoat.magHdg);	
	myData->waterSpd(calcBoat.waterSpeed);
	myData->SpeedOverGround(calcBoat.groundSpeed);
	//
	myData->Depth(calcBoat.depth);
	myData->TransducerDepth(calcBoat.TransducerDepth);
	//
	myData->CourseOverGround(calcBoat.courseOverGround);
	myData->MagneticCourseOverGround(calcBoat.magneticCourseOverGround);
	//
	myData->TrueWindSpeed(calcBoat.trueWindSpeed);
	myData->TrueWindAngle(calcBoat.trueWindAngle);
	myData->ApparentWindSpeed(calcBoat.ApparentWindSpeed);
	myData->ApparentWindAngle(calcBoat.ApparentWindAngle);
	//
	//
	nmea = myGenerator->generate(*myData);
	m_text->SetValue(nmea);

	drBoat = calcBoat; //reset dr boat data
}

double Dlg::parseFeature(Json::Value myFeatures, string featureName) {

	if (!myFeatures.isMember(featureName)) {
		// Originator
		wxLogMessage(_T("Feature not found"));
		wxMessageBox(_T("Feature not found")); // for debug
		return 0;
	}

	string name = myFeatures[featureName].asString();
	wxString myname(name.c_str(), wxConvUTF8);
	double myReturnValue;
	myname.ToDouble(&myReturnValue);
	return myReturnValue;
		
}

BEGIN_EVENT_TABLE(Dlg, wxFrame)
//(*EventTable(BroadcastFrame)
//*)
EVT_SOCKET(UDP_SOCKET, Dlg::OnUDPEvent)
END_EVENT_TABLE()

void Dlg::OnStartServer(wxCommandEvent& event) {

	useDR = m_checkBoxDR->GetValue();

	LoadBoatData();

	serverRunning = true;

	Init_Datagram_Socket();
	
	m_timerFeed.Start(1000);
	m_timerData.Start(DEAD_RECKONING_RATE);

	startDR = false;
	m_llTimerStartTick = wxGetUTCTimeMillis();
	m_llTimerDownloadStartTick = wxGetUTCTimeMillis();

	NMEASend(nmea); 
	
	event.Skip();
}

void Dlg::OnStopServer(wxCommandEvent& event) {

	
	serverRunning = false;
	m_status->SetValue("server stopped");
	m_timerFeed.Stop();
	m_timerData.Stop();

	event.Skip();
}

void Dlg::OnTimerFeed(wxTimerEvent& event) {

	m_llTimerStopTick = wxGetUTCTimeMillis();
	if(!startDR){		
		llElapsedTime = m_llTimerStopTick - m_llTimerStartTick;
		if (llElapsedTime > DEAD_RECKONING_RATE) {
			startDR = true;
		}
		else {
			NMEASend(nmea);
		}
	}
	
	event.Skip();
}

void Dlg::OnTimerData(wxTimerEvent& event) {

	m_llTimerDownloadStopTick = wxGetUTCTimeMillis();
	m_llTimerStopTick = wxGetUTCTimeMillis();

	if (startDR && useDR) {		
		llElapsedDownloadTime = m_llTimerDownloadStopTick - m_llTimerDownloadStartTick;
		if (llElapsedDownloadTime > REQUEST_RATE) {
			LoadBoatData();
			NMEASend(nmea);
			startDR = false;
			m_llTimerStartTick = wxGetUTCTimeMillis();
			m_llTimerDownloadStartTick = wxGetUTCTimeMillis();
		} else {
			// send dr
			GenerateDRnmeaSentence();
			NMEASend(nmea);
			startDR = false;
			m_llTimerStartTick = wxGetUTCTimeMillis();
			m_status->SetValue("DR Update");
		}		
	}
  
	event.Skip();
}



void Dlg::NMEASend(wxString myMessage)
{
	wxString wxmessage = myMessage;
	wxCharBuffer message = wxmessage.ToUTF8();  // used to get a const char* for SendTo

	// Use same socket created for listening for sending:

	m_Listen_Socket->SendTo(m_BroadCastAddress, message.data(), strlen(message.data()));

	if (m_Listen_Socket->Error())
	{
		wxLogMessage(_T("SendTo Error: %d"), m_Listen_Socket->LastError());
	}
}

/// The real stuff starts

void Dlg::Init_Datagram_Socket()
{
	// wxSocketBase::Initialize() may be necessary for wxWidgets versions
	// <2.5.x, and for all versions if using secondary threads
	// See https://wiki.wxwidgets.org/WxSocket
	// See http://comp.soft-sys.wxwindows.narkive.com/vt9BEujR/wxsocketbase-initialize

	wxSocketBase::Initialize();

	m_LocalAddress.AnyAddress();            // Receive any address (0.0.0.0)
	m_LocalAddress.Service(MY_SERVER_PORT);   // port on which we listen

// Create the socket
	m_Listen_Socket = new wxDatagramSocket(m_LocalAddress, wxSOCKET_REUSEADDR);
	if (m_Listen_Socket->Error())
	{
		wxLogError(_("Could not open Datagram Socket\n\n"));
		wxMessageBox("Unable to open Datagram Socket");
		return;
	}
	else
	{
		///////////////////////////////////////////////////////////////////////////
		// To send to a broadcast address, you must enable SO_BROADCAST socket
		// option, in plain C this is:
		//      int enabled = 1;
		//      setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &enabled, sizeof(enabled));
		// where sockfd is the socket descriptor (See http://linux.die.net/man/2/setsockopt)
		// See also boxcarmiba Wed Aug 02, 2006
		// at https://forums.wxwidgets.org/viewtopic.php?t=9410
		static int enabled = 1;
		m_Listen_Socket->SetOption(SOL_SOCKET, SO_BROADCAST, &enabled, sizeof(enabled));
		///////////////////////////////////////////////////////////////////////////

		// Set types of event that you want to receive:
		m_Listen_Socket->SetNotify(wxSOCKET_INPUT_FLAG);
		// Enable the event notification:
		
		m_Listen_Socket->Notify(false); // Set false because notify would cause a problem for the data feed

		// Setup the event handler (UDP_SOCKET is our custom event ID)
		// Note: Use EVT_SOCKET(UDP_SOCKET,  BroadcastFrame::OnUDPEvent) in event table
		m_Listen_Socket->SetEventHandler(*this, UDP_SOCKET);
	}

	// Specify a broadcast IP, in this case "Limited Broadcast" on the local network:
	m_BroadCastAddress.Hostname("255.255.255.255");

	wxString port = m_textCtrlPort->GetValue();
	int portNumber = atoi(port);

	m_BroadCastAddress.Service(portNumber);

}

// Responds to an event defined by an EVT_SOCKET table entry
void Dlg::OnUDPEvent(wxSocketEvent& event)
{
#define MAX_BUF_SIZE 1024
	unsigned char buff[MAX_BUF_SIZE] = { 0 };
	wxSocketBase *sock = event.GetSocket();

	switch (event.GetSocketEvent())
	{
	case wxSOCKET_INPUT:
	{   // Using blocking I/O (m_Listen_Socket NOT created with wxSOCKET_NOWAIT)
		// - assumes that as an event occurred there must be data available
		sock->Read(&buff, MAX_BUF_SIZE);
		wxLogMessage(_("OnUDPEvent read: %hs\n"), buff);
		wxString myMess = wxString::Format("OnUDPEvent read: %hs", buff);
		break;
	}

	default:
		wxLogMessage(_("OnUDPEvent received an unexpected event\n"));
		wxMessageBox("Unexpected event");
	}   // switch
#undef MAX_BUF_SIZE
}




static wxString FormatBytes(double bytes)
{
	return wxString::Format(_T("%.1fMB"), bytes / 1024 / 1024);
}

void Dlg::onDLEvent(OCPN_downloadEvent &ev)
{
	wxString msg;
	msg.Printf(_T("onDLEvent  %d %d"), ev.getDLEventCondition(), ev.getDLEventStatus());

	switch (ev.getDLEventCondition()) {
	case OCPN_DL_EVENT_TYPE_END:
		m_bTransferComplete = true;
		m_bTransferSuccess = (ev.getDLEventStatus() == OCPN_DL_NO_ERROR) ? true : false;
		break;

	case OCPN_DL_EVENT_TYPE_PROGRESS:
		m_totalsize = FormatBytes(ev.getTotal());
		m_transferredsize = FormatBytes(ev.getTransferred());

		break;
	default:
		break;
	}
}


