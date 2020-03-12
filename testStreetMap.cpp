//#include "provided.h"
//#include "ExpandableHashMap.h" 
//#include <iostream>
//#include <fstream>
//#include <functional>
//#include <sstream>
//#include <string>
//#include <vector>
//#include <list>
//#include <iomanip> 
//
//#include <iostream>
//#include <fstream>
//#include <sstream>
//
//using namespace std;
//
//int main() {
//
//	StreetMap testStreet;
//	testStreet.load("testMapData.txt");
//	
//
//	GeoCoord test1("100.0000000", "200.0000000");
//
//	
//
//	vector<StreetSegment> result;
//	testStreet.getSegmentsThatStartWith(test1, result);
//
//	for (int i = 0; i < result.size(); i++) {
//		vector<StreetSegment> tempResult;
//
//		cout << result[i].start.latitudeText << " " << result[i].start.longitudeText << " " << result[i].end.latitudeText << " " << result[i].end.longitudeText << endl;
//		//GeoCoord temp(result[i].end.latitudeText, result[i].end.longitudeText);
//		//
//		//testStreet.getSegmentsThatStartWith(temp, tempResult);
//		//for (int i = 0; i < tempResult.size(); i++) {
//		//	std::cout << std::fixed;
//		//	std::cout << std::setprecision(7);
//		//	cout << tempResult[i].start.latitudeText << " " << tempResult[i].start.longitude << " to " << tempResult[i].end.latitudeText << " " << tempResult[i].end.longitude << endl;
//		//}
//	}
//	return 0;
//}