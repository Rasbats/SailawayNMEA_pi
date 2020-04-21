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
#ifndef OBJECT2_H
#define OBJECT2_H

#include "SailawayNMEAgui.h"
#include "NMEASentenceGenerator.h"

class NMEASentenceGenerator;


	enum FixQualityType { NOT_AVAILABLE = 0, GPS = 1, DIFFERENTIAL_GPS = 2, PPS = 3, REAL_TIME_KINEMATIC = 4, FLOAT_RTK = 5, ESTIMATED_DEAD_RECKONING = 6, MANUAL = 7, SIMULATION_MODE = 8 };


class InstrumentsData
{
public:
	

	InstrumentsData();
	
	const double& lat() const { return _lat; }
	void lat(const double& lat) { _lat = lat; }

	const double& lon() const { return _lon; }
	void lon(const double& lon) { _lon = lon; }

	const double& waterSpd() const { return _waterSpd; }
	void waterSpd(const double& waterSpd) { _waterSpd = waterSpd; } // knots

	const int& Heading() const { return _Heading; }
	void Heading(const int& Heading) { _Heading = Heading; }

	const int& magHdg() const { return _magHdg; }
	void magHdg(const int& magHdg) { _magHdg = magHdg; }	

	const int& TrueWindAngle() const { return _TrueWindAngle; }
	void TrueWindAngle(const int& TrueWindAngle) { _TrueWindAngle = TrueWindAngle; }// 360 degrees relative to heading

	const double& TrueWindSpeed() const { return _TrueWindSpeed; }
	void TrueWindSpeed(const double& TrueWindSpeed) { _TrueWindSpeed = TrueWindSpeed; }// knots

	const int& ApparentWindAngle() const { return _ApparentWindAngle; }
	void ApparentWindAngle(const int& ApparentWindAngle) { _ApparentWindAngle = ApparentWindAngle; }// 360 degrees relative to heading

	const double& ApparentWindSpeed() const { return _ApparentWindSpeed; }
	void ApparentWindSpeed(const double& ApparentWindSpeed) { _ApparentWindSpeed = ApparentWindSpeed; }// knots
	
	const double& Depth() const { return _Depth; }
	void Depth(const double& Depth) { _Depth = Depth; }	// meters

	const double& TransducerDepth() const { return _TransducerDepth; }
	void TransducerDepth(const double& TransducerDepth) { _TransducerDepth = TransducerDepth; }	// meters
	
	const int& CourseOverGround() const { return _CourseOverGround; }
	void CourseOverGround(const int& CourseOverGround) { _CourseOverGround = CourseOverGround; }

	const int& MagneticCourseOverGround() const { return _MagneticCourseOverGround; }
	void MagneticCourseOverGround(const int& MagneticCourseOverGround) { _MagneticCourseOverGround = MagneticCourseOverGround; }

	const double& SpeedOverGround() const { return _SpeedOverGround; }
	void SpeedOverGround(const double& SpeedOverGround) { _SpeedOverGround = SpeedOverGround; } // knots

	const int& SatellitesCount() const { return _SatellitesCount; }
	void SatellitesCount(const int& SatellitesCount) { _SatellitesCount = SatellitesCount; } // when generating sentences it will be default to 4 if not set	

private:
	
	NMEASentenceGenerator* myGenerator;
	double _lat;
	double _lon;
	double _waterSpd;
	int _Heading;
	int _magHdg;
	
	int _TrueWindAngle;
	double _TrueWindSpeed;
	int _ApparentWindAngle;
	double _ApparentWindSpeed;
	double _Depth;
	double _TransducerDepth;
	int _CourseOverGround;
	int _MagneticCourseOverGround;
	double _SpeedOverGround;
	int _SatellitesCount;
    

};

#endif