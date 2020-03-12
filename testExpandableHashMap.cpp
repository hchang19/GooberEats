//#include "ExpandableHashMap.h"
//#include "provided.h"
//#include <iostream>
//#include <fstream>
//#include <functional>
//#include <sstream>
//#include <string>
//#include <vector>
//#include <list>
//using namespace std;
//
////used to test from string to double
//unsigned int hasher(const string& s) {
//	return std::hash<string>()(s);
//}
//
////Linker issue?
////template<typename KeyType>
////unsigned int hasher(const KeyType& s) {
////	return std::hash<KeyType>()(s);
////}
//
//
//
//int main() {
//
//	ExpandableHashMap<string, double> nameToGPA(.3);
//	cout << nameToGPA.size() << endl;
//	nameToGPA.associate("hello", 5);
//	nameToGPA.associate("hell", 4);
//	nameToGPA.associate("hel", 3);
//	nameToGPA.associate("he", 3);
//	nameToGPA.associate("h", 3);
//	nameToGPA.associate("h", 6);
//	nameToGPA.associate("i", 6);
//	nameToGPA.associate("", 6);
//	nameToGPA.associate("qq", 6);
//	nameToGPA.associate("uui", 6);
//	
//	
//
//
//}
