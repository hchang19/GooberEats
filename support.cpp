#include "support.h"
#include "provided.h"
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

//IMPLEMENTED THIS THEN FOUND OUT SMALLBERG WROTE SOMETHING FOR ME ALREADY SO I AM USING THAT INSTEAD

//Instead of using Eucledian, Haversine formula is used to more accurately calculate on sphere
//returns miles between two coordinates

//double calculateDistance(const GeoCoord& start, const GeoCoord& final) {
//
//	//distance between the long and latitudes
//	double diffLat = (final.latitude - start.latitude) * PI/ 180.0;
//	double diffLong = (final.longitude - start.longitude) * PI / 180.0;
//
//	//convert to rad
//
//	double lat1 = final.latitude * PI / 180.0;
//	double lat2 = start.latitude * PI / 180.0;
//
//	//do the Haversince
//
//	double x = pow(sin(diffLat / 2), 2) + pow(sin(diffLong / 2), 2) * cos(lat1) * cos(lat2);
//
//
//	return 2.0 * RADIUS_EARTH * asin(sqrt(x)) * MILES_PER_KM;
//}

//the weight of is determined by the Haversine distance to the final
//plus the amount of steps required to get to the current node from the start
CoordPacket::CoordPacket(const GeoCoord& prev, const GeoCoord& current, const GeoCoord& final, const double & steps, const string & strName){
	m_currentCoord = current;
	m_weight = steps + distanceEarthMiles(current, final);
	m_stepFromOrigin = steps;
	m_prevCoord = prev;
	m_streetName = strName;
}


GeoCoord CoordPacket::getCoord() const{
	return m_currentCoord;
}

GeoCoord CoordPacket::getPrevCoord() const {
	return m_prevCoord;
}

string CoordPacket::getStrName() const {
	return m_streetName;
}

double CoordPacket::getWeight() const {
	return m_weight;
}

double CoordPacket::getSteps() const {
	return m_stepFromOrigin;
}


//the same random generator provided in Kontagion
int randInt(int min, int max) {
	if (max < min) {
		std::swap(min, max);
	}
	static std::random_device rd;
	static std::default_random_engine generator(rd());
	std::uniform_int_distribution<> distro(min, max);
	return distro(generator);
}