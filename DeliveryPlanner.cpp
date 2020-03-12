#include "provided.h"
#include "support.h"
#include <vector>
using namespace std;

class DeliveryPlannerImpl
{
public:
    DeliveryPlannerImpl(const StreetMap* sm);
    ~DeliveryPlannerImpl();
    DeliveryResult generateDeliveryPlan(
        const GeoCoord& depot,
        const vector<DeliveryRequest>& deliveries,
        vector<DeliveryCommand>& commands,
        double& totalDistanceTravelled) const;
private:
    const StreetMap * m_streetMapPtr;
    string angleToCompass(const double& angle) const;
    bool isDeliveryCoord(const GeoCoord& curr, const vector<DeliveryRequest>& deliveries) const;
    string turnDirection(const double& angle) const;
};

DeliveryPlannerImpl::DeliveryPlannerImpl(const StreetMap* sm)
{
    m_streetMapPtr = sm;
}

DeliveryPlannerImpl::~DeliveryPlannerImpl()
{
    //nothing is dynamically allocated
}

DeliveryResult DeliveryPlannerImpl::generateDeliveryPlan(
    const GeoCoord& depot,
    const vector<DeliveryRequest>& deliveries,
    vector<DeliveryCommand>& commands,
    double& totalDistanceTravelled) const
{

    //optimize the deliveries first
    DeliveryOptimizer optimizer(m_streetMapPtr);
    vector<DeliveryRequest> optimizedDeliveries = deliveries;
    double oldDistance, newDistance;

    optimizer.optimizeDeliveryOrder(depot, optimizedDeliveries, oldDistance, newDistance);

    if (optimizedDeliveries.size() <= 0) {
        cerr << "There are nothing Loaded " << endl;
    }

    //Add going back to the depot
    DeliveryRequest backToDepot("", depot);
    optimizedDeliveries.push_back(backToDepot);

    //Add all the segments for the entire route to a masterRoute
    PointToPointRouter router(m_streetMapPtr);
    GeoCoord start = depot;
    GeoCoord end = depot;
    double totalDistance = 0;

    list<StreetSegment> masterRoute;
    DeliveryResult dResult;
    for (int i = 0; i < optimizedDeliveries.size(); i++) {
        end = optimizedDeliveries[i].location;
        double routeDistance;
        list<StreetSegment> PtoPRoute;
        
        dResult = router.generatePointToPointRoute(start, end, PtoPRoute, routeDistance);
        totalDistance += routeDistance;
        
        //check if its a bad coord or a bad route
        if (dResult != DELIVERY_SUCCESS){
            return dResult;
        }
        else {
            //Add everything to a master route
            masterRoute.splice(masterRoute.end(), PtoPRoute);
            start = optimizedDeliveries[i].location;
        }
    }

    //remove the depot as a delivery place
    optimizedDeliveries.pop_back();

    //thigns to return
    vector<DeliveryCommand> commandResults;
    
    //data for the first segment
    auto it = masterRoute.begin();
    StreetSegment prevSegment = *it;
    string direction = angleToCompass(angleOfLine(*it));

    //Creation of a dummy command
    DeliveryCommand tempCommand;
    tempCommand.initAsProceedCommand(direction, prevSegment.name, 0);

    for (; it != masterRoute.end(); it++) {
        //cout << "FROM: (" << it->start.latitudeText << ", " << it->start.longitudeText << ") TO: (" << it->end.latitudeText << ", " << it->end.longitudeText << ")" << " StreetName: " << it->name << endl;
        //check if it is a delivery location


        //check if it is a delivery
        if (isDeliveryCoord(it->start, optimizedDeliveries)) {
            //pushback whatever the last command is
            commandResults.push_back(tempCommand);
            for (auto op = optimizedDeliveries.begin(); op != optimizedDeliveries.end();) {
                if (it->start == op->location) {
                    //cerr << "DELIVERING " << op->item << endl;
                    tempCommand.initAsDeliverCommand(op->item);
                    commandResults.push_back(tempCommand);
                    op = optimizedDeliveries.erase(op);
                }
                else {
                    op++;
                }
            }

            direction = angleToCompass(angleOfLine(*it));
            tempCommand.initAsProceedCommand(direction, it->name, distanceEarthMiles(it->start, it->end));
            
        }
        else {
            //they are on the same street
            if (prevSegment.name == it->name) {
                tempCommand.increaseDistance(distanceEarthMiles(it->start, it->end));
            }
            else {
                //check if it is a turn
                commandResults.push_back(tempCommand);
                string turn = turnDirection(angleBetween2Lines(prevSegment, *it));

                if (turn != "") {
                    //cerr << "TURNGING " << turn << " ONTO " << it->name << endl;
                    tempCommand.initAsTurnCommand(turn, it->name);
                    commandResults.push_back(tempCommand);
                }
                tempCommand.initAsProceedCommand(direction, it->name, distanceEarthMiles(it->start, it->end));

            }
        }
        
        prevSegment = *it;
        
    }

    commandResults.push_back(tempCommand);
    
    totalDistanceTravelled = totalDistance;
    commands = commandResults;
    
    //forTestingPurposes
    for (int i = 0; i < commands.size(); i++) {
        cerr << commands[i].description() << endl;
    }

    //cerr << "YOU HAVE ARRIVED AT YOUR DESTINATION AFTER TRAVELING " << totalDistanceTravelled << " MILES" << endl;
    //cerr << "PLEASE GET TF OFF MY BACK BEFORE I EAT YOU" << endl;


    return DELIVERY_SUCCESS;  // Delete this line and implement this function correctly
}


string DeliveryPlannerImpl::angleToCompass(const double& angle) const {
    if (angle >= 337.5) {
        return "east";
    }

    if (angle >= 292.5) {
        return "southeast";
    }
    if (angle >= 247.5) {
        return "east";
    }

    if (angle >= 202.5) {
        return "southwst";
    }
    if (angle >= 157.5) {
        return "west";
    }

    if (angle >= 112.5) {
        return "northwest";
    }
    if (angle >= 67.5) {
        return "north";
    }

    if (angle >= 22.5) {
        return "northeast";
    }
    if (angle >= 0) {
        return "east";
    }

    
}

bool DeliveryPlannerImpl::isDeliveryCoord(const GeoCoord& curr, const vector<DeliveryRequest>& deliveries) const {
    for (int i = 0; i < deliveries.size(); i++) {
        if (curr == deliveries[i].location) {
            return true;
        }
    }
    return false;
}

string DeliveryPlannerImpl::turnDirection(const double& angle) const {
    if (angle >= 1 && angle < 180) {
        return "left";
    }

    if (angle >= 180 && angle <= 359) {
        return "right";
    }
    return "";
}
//******************** DeliveryPlanner functions ******************************

// These functions simply delegate to DeliveryPlannerImpl's functions.
// You probably don't want to change any of this code.

DeliveryPlanner::DeliveryPlanner(const StreetMap* sm)
{
    m_impl = new DeliveryPlannerImpl(sm);
}

DeliveryPlanner::~DeliveryPlanner()
{
    delete m_impl;
}

DeliveryResult DeliveryPlanner::generateDeliveryPlan(
    const GeoCoord& depot,
    const vector<DeliveryRequest>& deliveries,
    vector<DeliveryCommand>& commands,
    double& totalDistanceTravelled) const
{
    return m_impl->generateDeliveryPlan(depot, deliveries, commands, totalDistanceTravelled);
}
