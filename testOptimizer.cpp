//#include "provided.h" 
//#include "support.h"
//
//#include <iostream>
//#include <stdlib.h> 
//
//
//#include <cmath>
//
//using namespace std;
//
//int main() {
//
//	vector<DeliveryRequest> deliveries;
//	GeoCoord depot("34.0625329", "-118.4470263");
//
//	GeoCoord point1("34.0712323" ,"-118.4505969");
//	GeoCoord point2 ("34.0687443", "-118.4449195");
//	GeoCoord point3("34.0685657", "-118.4489289");
//
//	DeliveryRequest request2("Chicken tenders", point1);
//	DeliveryRequest request1("B-Plate salmon", point2);
//	DeliveryRequest request3("Pabst Blue Ribbon beer", point3);
//
//	deliveries.push_back(request2);
//	deliveries.push_back(request3);
//	deliveries.push_back(request1);
//	
//	StreetMap tempSm;
//	tempSm.load("./mapdata.txt");
//	vector<DeliveryRequest> OptimizedDeliveries;
//
//	DeliveryOptimizer testOptimizer(&tempSm);
//
//	double oldDistance, newDistance;
//
//	for (int i = 0; i < deliveries.size(); i++) {
//		cout << deliveries[i].item << endl;
//	}
//	testOptimizer.optimizeDeliveryOrder(depot, deliveries, oldDistance, newDistance);
//
//	cout << "ORIGINAL DISTANCE: " << oldDistance << " NEW DISTANCE: " << newDistance << endl;
//	cout << "NEW ORDER" << endl;
//	for (int i = 0; i < deliveries.size(); i++) {
//		cout << deliveries[i].item << endl;
//	}
//
//
//
//} 