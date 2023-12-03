#include <iostream>
#include <fstream>
#include <sstream>       
#include <cstdlib>  // exit prototype
#include <ctype.h>
#include <string>


using namespace std;
double FindMaxRec(const double arr[], int maxInd, int low, int high) {
    if (low == high) {
        return arr[low];
    } else {
        int mid = (low + high) / 2;
        double leftMax = FindMaxRec(arr, maxInd, low, mid);
        double rightMax = FindMaxRec(arr, maxInd, mid + 1, high);

        if (leftMax < rightMax) {
            return leftMax;
        }
        else {
            return rightMax;
        }
    }
}






int main(int argc, char *argv [])
{
	
	double myArray[20];
	int low, high, maxInd;
	double maxVal;
	ifstream file;
	int ind=0, len = 20;
    string str = "", word, filename;
    
    if (argc == 1)
	{
		cerr << "NO SPECIFIED INPUT FILE NAME." << endl;
		return 0;
	}
	else 
	{
		file.open(argv[1]);
		if( file.is_open() == false ) {
			cerr << "CANNOT OPEN THE FILE " << argv[1] << endl;
			return 0;
		}
	}	
	
	getline(file, str);
    while ( !file.eof()) 
	{
		str = str + "\n";   
		istringstream mystring(str);
		mystring >> myArray[ind];
		ind++;
		while(mystring.good() && ind < len)
		{
			mystring >> myArray[ind];
			ind++;
		}
		getline(file, str);
	}
		
	low = 1; high = ind - 1; //actual lenght of the array
	maxInd = 0;
	maxVal = FindMaxRec(myArray, low, high, maxInd);
		
	cout << "The maximum value is " << maxVal << endl;
		
	return 0;
}

