//#include "provided.h" 
//#include "support.h"
//#include "ExpandableHashMap.h"
//
//#include <vector>
//#include <list>
//#include <iostream>
//
//using namespace std;
//int main() {
//    //load the map data
//    StreetMap* streetMapPtr;
//    streetMapPtr = new StreetMap();
//    streetMapPtr->load("./mapdata.txt");
//
//
//    //34.0625329 - 118.4470263
//    //    34.0712323 - 118.4505969:Chicken tenders(Sproul Landing)
//    //    34.0687443 - 118.4449195 : B - Plate salmon(Eng IV)
//    //    34.0685657 - 118.4489289 : Pabst Blue Ribbon beer(Beta Theta Pi)
//
//    GeoCoord depot("34.0625329", "-118.4470263");
//
//    vector<DeliveryRequest> deliveries;
//    GeoCoord point1("34.0685657", "-118.4489289"); //Pabst Blue
//    GeoCoord point2("34.0712323" ,"-118.4505969"); //Chicken Tenders
//    GeoCoord point3("34.0687443", "-118.4449195"); //B-Plate Salmon
//    
//    DeliveryRequest request1("Pabst Blue Ribbon beer (Beta Theta Pi)", point1);
//    DeliveryRequest request2("Chicken tenders (Sproul Landing)", point2);
//    DeliveryRequest request3("B-Plate salmon (Eng IV)", point3);
//   
//   
//    
//    
//    deliveries.push_back(request1);
//    deliveries.push_back(request2);
//    deliveries.push_back(request3);
//
//    //optimize the delivery order
//    DeliveryPlanner testPlanner(streetMapPtr);
//    vector<DeliveryCommand> resultCommands;
//    double totalDistance = 0;
//    testPlanner.generateDeliveryPlan(depot, deliveries, resultCommands, totalDistance);
//
//    cout << totalDistance << endl;
//
//
//
//
//    if (streetMapPtr != nullptr) {
//        delete streetMapPtr;
//    }
//}