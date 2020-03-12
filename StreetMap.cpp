#include "provided.h"
#include <string>
#include <vector>
#include <functional>
#include "ExpandableHashMap.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

unsigned int hasher(const GeoCoord& g)
{
    return std::hash<string>()(g.latitudeText + g.longitudeText);
}

class StreetMapImpl
{
public:
    StreetMapImpl();
    ~StreetMapImpl();
    bool load(string mapFile);
    bool getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const;
private:
    ExpandableHashMap<GeoCoord, vector<StreetSegment>> m_streetData;
};

StreetMapImpl::StreetMapImpl()
{
	//does nothing
}

StreetMapImpl::~StreetMapImpl()
{
	//does nothing
}

bool StreetMapImpl::load(string mapFile)
{

	ifstream infile(mapFile);

	if (!infile) {
		cerr << "Error: Cannot locate '" << mapFile <<"'" << endl;
		return false;
	}
	//cerr << "LOADING MAP DATA" << endl;

	string streetName;
	string line;
	while (getline(infile, line)) {
		//set line to a string stream
		istringstream iss(line);
		istringstream tempIss(line);
		//data we want to parse
		double startLat, startLong, endLat, endLong;
		string nSegments;

		//check if its the integer
		if (!(iss >> startLat >> startLong >> endLat >> endLong)) {
			char dummy;
			istringstream tempISS(line);
			if (tempISS >> nSegments >> dummy) {
				streetName = line;
			}
			continue;
		}

		//cerr << "Street Name: " << streetName << " STARTCOORD: (" << startLat << ", " << startLong << ") ENDCOORD: (" << endLat << ", " << endLong << ")" << endl;
		//create the two GeoCoord

		ostringstream startLatText, startLongText, endLatText, endLongText;

		//set precision to avoid loss of data 
		//toString truncate the last decimal point
		startLatText.precision(7);
		startLongText.precision(7);
		endLatText.precision(7);
		endLongText.precision(7);
		
		startLatText << fixed << startLat;
		startLongText << fixed << startLong;
		endLatText << fixed << endLat;
		endLongText << fixed << endLong;

		//cout << "Streetname : " << streetName << "Start Coords: " << startLatText.str() << ", " << startLongText.str() << endl;
		GeoCoord startCoord(startLatText.str(), startLongText.str());
		GeoCoord endCoord(endLatText.str(), endLongText.str());

		//create a normal oriented and reversed street coord
		StreetSegment Seg1(startCoord, endCoord, streetName);
		StreetSegment Seg2(endCoord, startCoord, streetName);
		bool isDuplicate = false;
		//check if startCoord is in hash table already
		vector<StreetSegment>* tempPtr = m_streetData.find(startCoord);
		
		//if not create vector and push it in
		if (tempPtr == nullptr) {
			vector<StreetSegment> segmentsBank1;
			segmentsBank1.push_back(Seg1);
			m_streetData.associate(startCoord, segmentsBank1);
		}
		else {

			//check if it already exist
			for (auto it = tempPtr->begin(); it != tempPtr->end(); it++) {
				if (*it == Seg1) {
					isDuplicate = true;
				}
			}
			if (!isDuplicate) {
				tempPtr->push_back(Seg1);
			}
			 
		}


		//same for reverse
		tempPtr = m_streetData.find(endCoord);
		//if it doesn't exist, simply add one
		if (tempPtr == nullptr) {
			vector<StreetSegment> segmentsBank2;
			segmentsBank2.push_back(Seg2);
			m_streetData.associate(endCoord, segmentsBank2);


		}
		//other wise just pushback onto the vector
		else {
			//check if it already exist
			for (auto it = tempPtr->begin(); it != tempPtr->end(); it++) {
				if (*it == Seg1) {
					isDuplicate = true;
				}
			}
			if (!isDuplicate) {
				tempPtr->push_back(Seg2);
			}
		}

	}

	return true; 

	
}

bool StreetMapImpl::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
	if (m_streetData.size() <= 0) {
		cerr << "THIS STREET MAP IS UNLOADED" << endl;
		return false;
	}
	const vector<StreetSegment>* tempPtr = m_streetData.find(gc);

	if (tempPtr == nullptr) {
		return false;
	}

	else {
		segs = *tempPtr;
		return true;
	}

	
}

//******************** StreetMap functions ************************************

// These functions simply delegate to StreetMapImpl's functions.
// You probably don't want to change any of this code.

StreetMap::StreetMap()
{
    m_impl = new StreetMapImpl;
}

StreetMap::~StreetMap()
{
    delete m_impl;
}

bool StreetMap::load(string mapFile)
{
    return m_impl->load(mapFile);
}

bool StreetMap::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
   return m_impl->getSegmentsThatStartWith(gc, segs);
}
