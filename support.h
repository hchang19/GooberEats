
#ifndef SUPPORTH
#define SUPPORTH
#include <iostream>
#include <cmath>
#include <string>

#include <utility>
#include <random>
#include "provided.h"


//const double PI = 4 * atan(1);
//const double RADIUS_EARTH = 6378.1;
//const double MILES_PER_KM = 0.62137119;
//double calculateDistance(const GeoCoord& start, const GeoCoord & final);



//the Node structure that holds the Coord and weight stored in the priority Queue in A*
class CoordPacket
{
public:
    CoordPacket(const GeoCoord& prev, const GeoCoord& current, const GeoCoord & final, const double & steps, const std::string& strName);
    GeoCoord getCoord() const;
    GeoCoord getPrevCoord() const;
    std::string getStrName() const;
    double getWeight() const; 
    double getSteps() const;
    
private:
    GeoCoord m_currentCoord;
    GeoCoord m_prevCoord;
    std::string m_streetName;
    double m_weight;
    double m_stepFromOrigin;
};


//used to maintain Priority Queue for A*
class CoordPacketComparator {

public:
    int operator() (const CoordPacket& p1, const CoordPacket& p2)
    {
        return p1.getWeight() > p2.getWeight();
    }

};

int randInt(int min, int max);


#endif