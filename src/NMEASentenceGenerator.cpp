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
 */#include "NMEASentenceGenerator.h"
#include "SailawayNMEAgui_impl.h"

#include <string.h>
#include <sstream>

using namespace std;

NMEASentenceGenerator::NMEASentenceGenerator()
{

};

string NMEASentenceGenerator::generate(InstrumentsData data)
{
	string nmea = "";

	//wxMessageBox(wxString::Format("%f",data.lat()));

	//data.lat(50.0);
	//data.lon(-4.0);

	//$GPGGA,124112.00,291.225264,N,4843.967704,E,1,0,0,,M,,,,*2f

	if (data.lat() != NAN && data.lon() != NAN)nmea += generatePositionSentence_GLL(data.lat(), data.lon(), "A");
	if (data.lat() != NAN && data.lon() != NAN)nmea += generatePositionSentence_GGA(data.lat(), data.lon(), "A", "4");	
	if (data.Heading() != NAN && data.waterSpd() != NAN) nmea += generateSpeedAndHeadingSentence_VHW(data.waterSpd(), data.Heading(), data.magHdg() ? data.magHdg() : 0);
    if (data.Heading() != NAN) nmea += generateTrueHeadingSentence_HDT(data.Heading() ?  data.Heading(): 0);
	
	if (data.TrueWindAngle() != NAN && data.TrueWindSpeed() != NAN) nmea += generateTrueWindSpeedAndAngleSentence_MWV(data.TrueWindAngle() ? data.TrueWindAngle() : 0, data.TrueWindSpeed() ? data.TrueWindSpeed() : 0 , "A");
	if (data.ApparentWindAngle() != NAN && data.ApparentWindSpeed() != NAN) nmea += generateApparentWindSpeedAndAngleSentence_MWV(data.ApparentWindAngle() ? data.ApparentWindAngle() : 0, data.ApparentWindSpeed() ? data.ApparentWindSpeed() : 0 , "A");
	
	if (data.Depth() != NAN && data.TransducerDepth() != NAN) nmea += generateDepthSentence_DPT(data.Depth(), data.TransducerDepth() ? data.TransducerDepth() : 0);
	if (data.Depth() != NAN) nmea += generateDepthSentence_DBT(data.Depth() ? data.Depth():0);

	if (data.CourseOverGround() != NAN && data.SpeedOverGround() != NAN) nmea += generateSpeedAndCourseOverGroundSentence_VTG(data.SpeedOverGround() ? data.SpeedOverGround() : 0, data.CourseOverGround() ? data.CourseOverGround() : 0, data.MagneticCourseOverGround());
	if (data.lat() != NAN && data.lon() != NAN && data.SpeedOverGround() != NAN && data.CourseOverGround() != NAN) nmea += generateRecommendedMinimumInformationSentence_RMC(data.lat() ? data.lat(): 0, data.lon() ? data.lon(): 0, data.SpeedOverGround() ? data.SpeedOverGround() : 0, data.CourseOverGround() ? data.CourseOverGround()  : 0, "A");

	/*
	
			
			if (data.Lat != null && data.Lon != null && data.SpeedOverGround != null && data.CourseOverGround != null) nmea += generateRecommendedMinimumInformationSentence_RMC(data.Lat ?? 0, data.Lon ?? 0, data.SpeedOverGround ?? 0, data.CourseOverGround ?? 0, data.FixQuality ?? FixQualityType.GPS);
			*/
	//wxMessageBox(nmea);
	return nmea;
}


string NMEASentenceGenerator::generatePositionSentence_GLL(double lat, double lon, string fixQuality)
{

	string _lat = ConvertDecimalDegreesToNMEAFormat(lat, Coord::lat);
	string _lon = ConvertDecimalDegreesToNMEAFormat(lon, Coord::lon);
	string valid = "A"; // Utils.isValidFix(fixQuality) ? "A" : "V"; // A is valid, V is "receiver warning"
	string time = UTCTime();
	string sentence = "GPGLL,"  + _lat + "," + _lon + "," + time + "," + valid;
	return FormatSentence(sentence);
}

string NMEASentenceGenerator::generatePositionSentence_GGA(double lat, double lon, string fixQuality, string satellites)
{

	string _lat = ConvertDecimalDegreesToNMEAFormat(lat, Coord::lat);
	string _lon = ConvertDecimalDegreesToNMEAFormat(lon, Coord::lon);
	string time = UTCTime();
	//$GPGGA,124112.00,291.225264,N,4843.967704,E,1,0,0,,M,,,,*2f
	string sentence = "GPGGA," + time + "," + _lat + "," + _lon + "," + "1"  + ",0,0,,M,,,,"; 
	return FormatSentence(sentence);
}

string NMEASentenceGenerator::generateSpeedAndHeadingSentence_VHW(double speed, int trueHeading, int magneticHeading)
{
	string mymagneticHeading = to_string(magneticHeading);
	if (magneticHeading == 0) { mymagneticHeading = ""; }

	string _speedKnots = to_string(speed);
	string _speedKmH = to_string(speed * 1.852);
	//$IIVHW, 245.1, T, 245.1, M, 000.01, N, 000.01, K

	string sentence = "IIVHW," + to_string(trueHeading) + ",T," + mymagneticHeading + ",M," + _speedKnots + ",N," + _speedKmH + ",K";
	return FormatSentence(sentence);
}

string NMEASentenceGenerator::generateTrueHeadingSentence_HDT(int trueHeading)
{
	string sentence = "IIHDT," + to_string(trueHeading) + ",T";
	return FormatSentence(sentence);
}

string NMEASentenceGenerator::generateTrueWindSpeedAndAngleSentence_MWV(int trueWindAngle, double trueWindSpeed, string fixQuality)
{
	string valid = "A"; // A is valid, V is "receiver warning"
	string sentence = "WIMWV," + to_string(trueWindAngle) + ",T," + to_string(trueWindSpeed) + ",N," + valid;
	return FormatSentence(sentence);
}

string NMEASentenceGenerator::generateApparentWindSpeedAndAngleSentence_MWV(int apparentWindAngle, double apparentWindSpeed, string fixQuality)
{
	string valid = "A"; // A is valid, V is "receiver warning"
	string sentence = "WIMWV," + to_string(apparentWindAngle)  + ",R," + to_string(apparentWindSpeed) + ",N," + valid;
	return FormatSentence(sentence);
}

string NMEASentenceGenerator::generateDepthSentence_DPT(double depth, double transducerDepth)
{
	string sentence = "SDDPT," + to_string(depth) +  "," +  to_string(transducerDepth);
	return FormatSentence(sentence);
}


string NMEASentenceGenerator::generateDepthSentence_DBT(double depth)
{
	// $--DBT,x.x,f,x.x,M,x.x,F*hh<CR><LF>
	string sentence = "SDDBT," + to_string(depth * 3.28084) + ",f," + to_string(depth) + ",M," + to_string(depth * 0.546807) + ",F";
	return FormatSentence(sentence);
}

//$GPVTG,37.38,T,,M,0.08,N,0.1,K*56
string NMEASentenceGenerator::generateSpeedAndCourseOverGroundSentence_VTG(double speedOverGround, int courseOverGround, int magneticCourseOverGround)
{
	//if (magneticCourseOverGround == 0) magneticCourseOverGround = courseOverGround; *** only used by compasses
	string _speedKnots = to_string(speedOverGround);
	string _speedKmH = to_string(speedOverGround * 1.852);
	string sentence = "IIVTG," + to_string(courseOverGround) + ",T," +  ",M," + _speedKnots + ",N," + _speedKmH + ",K";
	return FormatSentence(sentence);
}

string NMEASentenceGenerator::generateRecommendedMinimumInformationSentence_RMC(double lat, double lon, double speedOverGround, int courseOverGround, string fixQuality)
{
	string _lat = ConvertDecimalDegreesToNMEAFormat(lat, Coord::lat);
	string _lon = ConvertDecimalDegreesToNMEAFormat(lon, Coord::lon);
	string valid = "A"; // : "V";  // A is valid, V is "receiver warning"
	string _sogKnots = to_string(speedOverGround);
	string time = UTCTime();
	string date = dateDDMMYY();
	string sentence = "GPRMC," + time + "," + valid + "," + _lat + "," + _lon + "," + _sogKnots + "," + to_string(courseOverGround) + "," + date +  ",,";
	return FormatSentence(sentence);
}


string NMEASentenceGenerator::ConvertDecimalDegreesToNMEAFormat(double decimalDegrees, Coord coord)
{
	string cardinal = "";

	switch (coord)
	{
	case Coord::lat:
		cardinal = decimalDegrees >= 0 ? "N" : "S";
		break;
	case Coord::lon:
		cardinal = decimalDegrees >= 0 ? "E" : "W";
		break;
	}

	wxString mMinLL;
	wxString mDegLL;
	wxString doublezero = _T("00");
	wxString singlezero = _T("0");

	decimalDegrees = abs(decimalDegrees);

	

	double sec = decimalDegrees * 3600;

	double floorSec = sec / 3600;
	int deg = static_cast<int>(floorSec);


    
	sec -= deg * 3600;
	double min = sec / 60;

	wxString wxDeg(wxString::Format("%i", deg));

	int myLL = wxDeg.length();

	switch (myLL) {
		case(1): {
			if (coord == Coord::lat) {
				mDegLL = singlezero + wxDeg;
			}
			else if (coord == Coord::lon) {
				mDegLL = doublezero + wxDeg;
			}
			break;
		}
		case(2): {	
			if (coord == Coord::lon) {
				mDegLL = singlezero + wxDeg;
			} else 	mDegLL = wxDeg;
			break;
		}
		case(3): {
			mDegLL = wxDeg;
			break;
		}
	}
	
	wxString wxMin(wxString::Format("%5.3f", min));

	int myMinLength = wxMin.length();

	switch (myMinLength) {
		
		case(5): {
			mMinLL = singlezero + wxMin;
			break;
		}

		case(6): {
			mMinLL = wxMin;
			break;
		}
	}
	//wxMessageBox(mMinLL);

	return mDegLL.ToStdString() + mMinLL.ToStdString() + "," + cardinal; //     ("00.0###", CultureInfo.InvariantCulture) ;
}



string NMEASentenceGenerator::CalculateCheckSum(wxString mySentence) {
	int i;
	unsigned char XOR;

	wxString s(mySentence);
	wxCharBuffer buffer = s.ToUTF8();
	char *Buff = buffer.data();	// data() returns const char *
	unsigned long iLen = strlen(Buff);
	for (XOR = 0, i = 0; i < iLen; i++)
		XOR ^= (unsigned char)Buff[i];
	stringstream tmpss;
	tmpss << hex << (int)XOR << endl;
	wxString mystr = tmpss.str();
	return (string)mystr;
}

string NMEASentenceGenerator::FormatSentence(string sentence)
{
	return "$" + sentence + "*" + CalculateCheckSum(sentence);
}

string NMEASentenceGenerator::UTCTime()
{
	wxDateTime myDT = wxDateTime::Now();
	wxString sHours, sMinutes, sSecs;
	sHours = myDT.Format(_T("%H"));
	sMinutes = myDT.Format(_T("%M"));
	sSecs = myDT.Format(_T("%S"));
	wxString dtss = sHours + sMinutes + sSecs;
	//wxMessageBox(dtss);
	return dtss.ToStdString();
}

string NMEASentenceGenerator::dateDDMMYY()
{
	wxDateTime myDT = wxDateTime::Now();
	wxString sDay, sMonth, sYear;
	sDay = myDT.Format(_T("%d"));
	sMonth = myDT.Format(_T("%m"));
	sYear = myDT.Format(_T("%y"));
	wxString datestring = sDay + sMonth + sYear;
	return datestring.ToStdString();
}