//#include "provided.h" 
//#include "support.h"
//#include "ExpandableHashMap.h"
//
//#include <string>
//#include <vector>
//#include <list>
//#include <iostream>
//#include <queue>
//#include <map>
//#include <stack>
//
//#include <fstream>
//#include <sstream>
//using namespace std;
//
//
////34.0625329 - 118.4470263
////34.0685657 - 118.4489289 : Pabst Blue Ribbon beer(Beta Theta Pi)
////34.0712323 - 118.4505969:Chicken tenders(Sproul Landing)
////34.0687443 - 118.4449195 : B - Plate salmon(Eng IV)
//
//
//
//int main() {
//
//    GeoCoord depot("34.0625329", "-118.4470263");
//
//    vector<DeliveryRequest> deliveries;
//    GeoCoord point1("34.0685657", "-118.4489289"); //Pabst Blue
//    GeoCoord point2("34.0712323", "-118.4505969"); //Chicken Tenders
//    GeoCoord point3("34.0687443", "-118.4449195"); //B-Plate Salmon
//    GeoCoord point4("34.0669763", "-118.4451404");
//    GeoCoord point5("34.0668846", "-118.4450991");
//    GeoCoord point6("34.0668977", "-118.4452290");
//    
//    DeliveryRequest request3("Pabst Blue Ribbon beer (Beta Theta Pi)", point1);
//    DeliveryRequest request1("Chicken tenders (Sproul Landing)", point2);
//    DeliveryRequest request2("B-Plate salmon (Eng IV)", point3);
//
//
//
//    StreetMap testmap;
//    testmap.load("./mapdata.txt");
//
//    PointToPointRouter testRouter(&testmap);
//
//    list<StreetSegment> result;
//    double finalDistance = 0;
//    double distance;
//
//    testRouter.generatePointToPointRoute(depot, point1, result, distance);
//    finalDistance += distance;
//    cerr << "DELIVERING PABST BLUE " << distance << endl;
//
//    testRouter.generatePointToPointRoute(point1, point2, result, distance);
//    finalDistance += distance;
//    cerr << "DELIVERING Chicken Tenders " << distance << endl;
//
//    testRouter.generatePointToPointRoute(point2, point3, result, distance);
//    finalDistance += distance;
//    cerr << "DELIVERING BPlate " << distance << endl;
//
//    testRouter.generatePointToPointRoute(point3, depot, result, distance);
//    finalDistance += distance;
//    cerr << "WALKING BACK TO DEPOT :" << distance << endl;
//
//    cerr << "Final Distance :" << finalDistance << endl;
//    //testRouter.generatePointToPointRoute(point3, point4, result, distance);
//    //cerr << "Salmon to divergence point " << distance << endl;
//
//    //testRouter.generatePointToPointRoute(point4, point5, result, distance);
//    //cerr << "Divergence Point Effecient: " << distance <<  endl;
//    //cerr << "Crow Distasnce Between Two Points" << distanceEarthMiles(point4, point5) << endl;
//    //cerr << "Heuristic Distance: " << distanceEarthMiles(point5, depot) << endl;
//    //testRouter.generatePointToPointRoute(point4, point6, result, distance);
//    //cerr << "Divergence Point Non-Effecient: " << distance << endl;
//    //cerr << "Crow Distasnce Between Two Points" << distanceEarthMiles(point4, point6) << endl;
//    //cerr << "Heuristic Distance: " << distanceEarthMiles(point6, depot) << endl;
//
//    return 0;
//
//
//}
