#include "provided.h"
#include "ExpandableHashMap.h"
#include "support.h"
#include <list>
#include <queue>
#include <stack>
#include <set>
using namespace std;

class PointToPointRouterImpl
{
public:
    PointToPointRouterImpl(const StreetMap* sm);
    ~PointToPointRouterImpl();
    DeliveryResult generatePointToPointRoute(
        const GeoCoord& start,
        const GeoCoord& end,
        list<StreetSegment>& route,
        double& totalDistanceTravelled) const;
private:
    const StreetMap* m_streetMapPtr;
    
    
};

PointToPointRouterImpl::PointToPointRouterImpl(const StreetMap* sm)
{
    m_streetMapPtr = sm;
}

PointToPointRouterImpl::~PointToPointRouterImpl()
{
    //no need to dynamically deallocate 
}

DeliveryResult PointToPointRouterImpl::generatePointToPointRoute(
        const GeoCoord& start,
        const GeoCoord& end,
        list<StreetSegment>& route,
        double& totalDistanceTravelled) const
{

    vector<StreetSegment> tempSegs;
    list<StreetSegment> result;
    set<GeoCoord> visited;
    ExpandableHashMap<GeoCoord, CoordPacket> routeHolder;
    //open list
    priority_queue <CoordPacket, vector<CoordPacket>, CoordPacketComparator > evaluatePQ;

    //attempt to find the ending coordinates in the StreetMap
    if (!m_streetMapPtr->getSegmentsThatStartWith(end, tempSegs) || !m_streetMapPtr->getSegmentsThatStartWith(start, tempSegs)) {
        cerr << "Bad Coordinate Input!" << endl;
        return BAD_COORD;
    }
    
    tempSegs.clear();


    //cerr << "ATTEMPTING TO GO FROM (" << start.latitudeText << ", " << start.longitudeText << ") TO (" << end.latitudeText << ", " << end.longitudeText << ")" << endl;
    //Format the starting coord and push onto priority queue
    CoordPacket initial(start, start, end, 0, "");
    evaluatePQ.push(initial);
    visited.insert(initial.getCoord());


    while (!evaluatePQ.empty()) {
        //the CoordPacket that is currently being evaluated
        CoordPacket current_eval = evaluatePQ.top();
        evaluatePQ.pop();


        routeHolder.associate(current_eval.getCoord(), current_eval);
        visited.insert(current_eval.getCoord());
        //check if its the first one or not
        //cerr << endl;
        //cerr << "EVALUATING: (" << current_eval.getCoord().latitudeText << " " << current_eval.getCoord().longitudeText << ") DistanceFromOrigin: " << current_eval.getSteps() << " miles" << endl;
        //If it is at final destination
        if (current_eval.getCoord().latitude == end.latitude && current_eval.getCoord().longitude == end.longitude) {
            //cerr << "END REACHED" << endl;
            //set the segments and return delivry successful

            CoordPacket* resultIndex = routeHolder.find(end);

            if (resultIndex == nullptr) {
                cerr << "NO ROUTE CAN BE FOUND" << endl;
                return NO_ROUTE;
            }

            //FORMAT EVERYTHING IN THE CORRECT ORDER
            else {
                list<StreetSegment> resultDirections;
                stack<StreetSegment> reverseHelper;
                double totalDistance = 0;

                //push everything onto the stack since everything is currently in reversed order
                while (resultIndex->getCoord() != start) {
                    StreetSegment temp(resultIndex->getPrevCoord(), resultIndex->getCoord(), resultIndex->getStrName());
                    reverseHelper.push(temp);
                    totalDistance += distanceEarthMiles(resultIndex->getPrevCoord(), resultIndex->getCoord());
                    resultIndex = routeHolder.find(resultIndex->getPrevCoord());
                }

                //push everything off the stack and push into the list
                while (!reverseHelper.empty()) {
                    resultDirections.push_back(reverseHelper.top());
                    reverseHelper.pop();
                }

                //For Testing Purposes
                //cerr << endl;
                //cerr << "PRINTING RESULTS " << endl;
                //for (auto it = resultDirections.begin(); it != resultDirections.end(); it++) {
                // cerr << "FROM: (" << it->start.latitudeText << ", " << it->start.longitudeText << ") TO: (" << it->end.latitudeText << ", " << it->end.longitudeText << ")" << " StreetName: " << it->name << endl;
                //}

                //cerr << "Total Distance Traveled is " << totalDistance << " miles" << endl;
                route = resultDirections;
                totalDistanceTravelled = totalDistance;

            }

            return DELIVERY_SUCCESS;
        }

        
        double stepsFromOrigin = 0;
        m_streetMapPtr->getSegmentsThatStartWith(current_eval.getCoord(), tempSegs);



        //theSegment in the end
        for (int i = 0; i < tempSegs.size(); i++) {

            //check if that Coordinate has been evaluated before
            //cerr << "FOUND SEGMENT: (" << tempSegs[i].start.latitudeText << ", " << tempSegs[i].start.longitudeText << ") TO ( " << tempSegs[i].end.latitudeText << ", " << tempSegs[i].end.longitudeText << ")" << endl;
            //check if it has been explored yet


                stepsFromOrigin = current_eval.getSteps() + distanceEarthMiles(tempSegs[i].start, tempSegs[i].end);

                CoordPacket temp(tempSegs[i].start, tempSegs[i].end, end, stepsFromOrigin, tempSegs[i].name);
                

                //cerr << "ADDING TO QUEUE: (" << temp.getCoord().latitudeText << " " << temp.getCoord().longitudeText << ") Steps:" << temp.getSteps() << " Weight: " << temp.getWeight() << " StreetName: " << tempSegs[i].name << endl;
                

                CoordPacket* storedCoordPacket = routeHolder.find(tempSegs[i].end);
                if (storedCoordPacket == nullptr || visited.find(tempSegs[i].end) == visited.end()) {
                    evaluatePQ.push(temp);
                }
                
                else if (temp.getWeight() < storedCoordPacket->getWeight()) {
                    *storedCoordPacket = temp;
                    evaluatePQ.push(temp);
                } 
                
                
                
        }


      

        

    }


    cerr << "NO ROUTE FOUND" << endl;
    return NO_ROUTE; 
}

//******************** PointToPointRouter functions ***************************

// These functions simply delegate to PointToPointRouterImpl's functions.
// You probably don't want to change any of this code.

PointToPointRouter::PointToPointRouter(const StreetMap* sm)
{
    m_impl = new PointToPointRouterImpl(sm);
}

PointToPointRouter::~PointToPointRouter()
{
    delete m_impl;
}

DeliveryResult PointToPointRouter::generatePointToPointRoute(
        const GeoCoord& start,
        const GeoCoord& end,
        list<StreetSegment>& route,
        double& totalDistanceTravelled) const
{
    return m_impl->generatePointToPointRoute(start, end, route, totalDistanceTravelled);
}
