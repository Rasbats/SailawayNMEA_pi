//header guard at start of header file
#ifndef OBJECT_H
#define OBJECT_H

#include "InstrumentsData.h"


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
	string NMEASentenceGenerator::UTCTime();
	string dateDDMMYY();

};
	
#endif

