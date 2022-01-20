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
//header guard at start of header file
#ifndef OBJECT_H
#define OBJECT_H

#include "InstrumentsData.h"
#include "ocpn_plugin.h"
#include <string.h>

using namespace std;

class InstrumentsData;

enum Coord {
	lat, lon
};

class NMEASentenceGenerator
{
public:
	NMEASentenceGenerator();
	InstrumentsData* data;

	string generate(InstrumentsData data);
	string generatePositionSentence_GLL(double lat, double lon, string fixQuality);
	string generatePositionSentence_GGA(double lat, double lon, string fixQuality, string satellites);
	string generateSpeedAndHeadingSentence_VHW(double speed, int trueHeading, int magneticHeading);
	string generateTrueHeadingSentence_HDT(int trueHeading);
	string generateDepthSentence_DPT(double depth, double transducerDepth);
	string generateDepthSentence_DBT(double depth);
	string generateTrueWindSpeedAndAngleSentence_MWV(int trueWindAngle, double trueWindSpeed, string fixQuality);
	string generateApparentWindSpeedAndAngleSentence_MWV(int apparentWindAngle, double apparentWindSpeed, string fixQuality);

	string generateSpeedAndCourseOverGroundSentence_VTG(double speedOverGround, int courseOverGroud, int magneticCourseOverGround);
	string generateRecommendedMinimumInformationSentence_RMC(double lat, double lon, double speedOverGround, int courseOverGroud, string fixQuality);

	string ConvertDecimalDegreesToNMEAFormat(double decimalDegrees, Coord coord);
	string CalculateCheckSum(wxString mySentence);
	string FormatSentence(string sentence);
	string UTCTime();
	string dateDDMMYY();

};
	
#endif

