#include "provided.h"
#include "support.h"
#include <algorithm>
#include <vector>
using namespace std;

class DeliveryOptimizerImpl
{
public:
    DeliveryOptimizerImpl(const StreetMap* sm);
    ~DeliveryOptimizerImpl();
    void optimizeDeliveryOrder(
        const GeoCoord& depot,
        vector<DeliveryRequest>& deliveries,
        double& oldCrowDistance,
        double& newCrowDistance) const;
private:
    const StreetMap* m_streetMapPtr;
    double calculateCrowDistance(const GeoCoord& depot, vector<DeliveryRequest>& deliveries) const;

};

DeliveryOptimizerImpl::DeliveryOptimizerImpl(const StreetMap* sm)
{
    m_streetMapPtr = sm;
}

DeliveryOptimizerImpl::~DeliveryOptimizerImpl()
{
    //not dynamically allocating anything
}

void DeliveryOptimizerImpl::optimizeDeliveryOrder(
    const GeoCoord& depot,
    vector<DeliveryRequest>& deliveries,
    double& oldCrowDistance,
    double& newCrowDistance) const
{

    if (deliveries.size() <= 0) {
        cerr << "NO DELIVERIES INPUTTED" << endl;
        return;
    }
   

    //calculate the old crow distance
    
    oldCrowDistance = calculateCrowDistance(depot, deliveries);
   

    //Do Simulating Annealing
    vector<DeliveryRequest> bestDeliveries = deliveries;
    PointToPointRouter router(m_streetMapPtr);
    //used to hold the deliveries being passed into
    double temperature = 0.70;

	while (temperature > .01) {

		vector<DeliveryRequest> modifiedDeliveries = deliveries ;

		//current cost
		double oldCost = calculateCrowDistance(depot, modifiedDeliveries);

		//calculate random indexes to swap
		int index1 = randInt(0, modifiedDeliveries.size() - 1);
		int index2 = randInt(0, modifiedDeliveries.size() - 1);
        int index3 = randInt(0, modifiedDeliveries.size() - 1);
		//switch first two random deliveries
		DeliveryRequest temp = modifiedDeliveries[index1];
		modifiedDeliveries[index1] = modifiedDeliveries[index2];
        modifiedDeliveries[index2] = modifiedDeliveries[index3];
        modifiedDeliveries[index3] = temp;

        
		//new cost after achange
		double newCost = calculateCrowDistance(depot, modifiedDeliveries);

		//cost difference
		double costDiff = newCost - oldCost;
		cerr << "New Distance: " << newCost << " Old Distance: " << oldCost << " Cost Difference: " << costDiff << endl;
		double prob = min(1.0, exp(-(costDiff) / temperature));
		double acceptProb = randInt(0, 100) / 100.0;
		//if it is less cost, keep the change
		if (costDiff < 0 || acceptProb > prob) {
			deliveries = modifiedDeliveries;

			//compare with the best delivery
			
            double bestCost = calculateCrowDistance(depot, bestDeliveries);

			if (newCost < bestCost) {
				//cerr << "New Distance: " << newCost << " Best Distance: " << bestCost << endl;
				bestDeliveries = modifiedDeliveries;
			}
            
		}

        temperature = .9 * temperature;
        
        
	}


    newCrowDistance = calculateCrowDistance(depot, bestDeliveries);
    deliveries = bestDeliveries;


}

double DeliveryOptimizerImpl::calculateCrowDistance(const GeoCoord& depot, vector<DeliveryRequest>& deliveries) const {
    GeoCoord start = depot;
    
    DeliveryRequest goingToDepot("", depot);
    deliveries.push_back(goingToDepot);
    double totalDistance = 0;
    PointToPointRouter router(m_streetMapPtr);
    list<StreetSegment> trashSegs;
    //calculate the old crow distance
    for (int i = 0; i < deliveries.size(); i++) {
        //double tempDistant;
        //router.generatePointToPointRoute(start, deliveries[i].location, trashSegs, tempDistant);
        //totalDistance += tempDistant;

        totalDistance += distanceEarthMiles(start, deliveries[i].location);
        start = deliveries[i].location;
    }
    deliveries.pop_back();


    return totalDistance;

}

//******************** DeliveryOptimizer functions ****************************

// These functions simply delegate to DeliveryOptimizerImpl's functions.
// You probably don't want to change any of this code.

DeliveryOptimizer::DeliveryOptimizer(const StreetMap* sm)
{
    m_impl = new DeliveryOptimizerImpl(sm);
}

DeliveryOptimizer::~DeliveryOptimizer()
{
    delete m_impl;
}

void DeliveryOptimizer::optimizeDeliveryOrder(
        const GeoCoord& depot,
        vector<DeliveryRequest>& deliveries,
        double& oldCrowDistance,
        double& newCrowDistance) const
{
    return m_impl->optimizeDeliveryOrder(depot, deliveries, oldCrowDistance, newCrowDistance);
}
