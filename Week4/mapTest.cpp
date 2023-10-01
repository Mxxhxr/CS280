#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;


int main(int argc, char *argv[]) {

	map<string, int> myMap;
	
	myMap["maahir"] = 20;
	myMap["masoom"] = 23;
	myMap["zaid"] = 21;


	map<string, int>::iterator it;


	
	for(auto it = myMap.begin(); it != myMap.end(); it++) {
		cout << "Name: " << it->first << ": Age: " << it->second << endl;
	}

	myMap.insert(make_pair("zainab", 17));

	cout << myMap["zainab"];
}

