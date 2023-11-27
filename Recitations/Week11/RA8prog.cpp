#include <iostream>
#include <string>
#include <vector> 
using namespace std; 
#include "val.h"
#include "val.cpp"

void ExecuteDIV(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " / " << val2 << " is " <<  val1 / val2 << endl;
}

void ExecuteEQ(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " = " << val2 << " is " <<  (val1 == val2 ) << endl;
}

void ExecuteAND(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " and " << val2 << " is " <<  (val1 && val2)<< endl;
}

void ExecuteMOD(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " mod " << val2 << " is " <<  (val1 % val2) << endl; 
}


	
int main(int argc, char *argv[])
{
	Value ErrorVal;
	double num1 = 7.25;
	Value doubleVal1(num1);
	double num2 = 3;
	Value doubleVal2(num2);
	string str1 = "CS280";
	Value StrVal1(str1); 
	string str2 = "Spring 2023";
	Value StrVal2(str2);
	
	int intval1 = 25;
	Value intVal1(intval1);
	int intval2 = 4;
	Value intVal2(intval2);
	bool logval1 = true;
	Value logVal1(logval1);
	bool logval2 = false;
	Value logVal2(logval2);
	
	vector<Value> vals( {ErrorVal, intVal1, intVal2, doubleVal1, doubleVal2, StrVal1, StrVal2, logVal1, logVal2} );
	bool divideflag = false, modflag = false, andflag = false, eqflag = false;
	
	if (argc == 1)
	{
		cerr << "No Specified arguments." << endl;
		return 0;
	}
	
	string arg( argv[1] );
	if( arg == "-divide" )
		divideflag = true;
	else if( arg == "-mod" )
		modflag = true;
	else if( arg == "-and" )
		andflag = true;		
	else if( arg == "-eq" )
		eqflag = true;
	
	else {
			cerr << "UNRECOGNIZED FLAG " << arg << endl;
			return 0;
	}
		
		
	cout << "ErrorVal=" << ErrorVal << endl; 
	//cout << "IntVal=" << IntVal << endl; 
	cout << "intVal1=" << intVal1 << endl; 
	cout << "intVal2=" << intVal2 << endl;
	cout << "doubleVal1=" << doubleVal1 << endl; 
	cout << "doubleVal2=" << doubleVal2 << endl;
	cout << "StrVal1=" << StrVal1 << endl; 
	cout << "StrVal2=" <<  StrVal2 << endl;
	cout << "logVal1=" << logVal1 << endl;
	cout << "logVal4=" << logVal2 << endl;
	
	if(divideflag)
	{
		for(int i = 0; i < vals.size(); i++ ) 
			for( int j = 0; j < vals.size(); j++ )
				if( i != j )
					ExecuteDIV( vals[i], vals[j] );
	}
	
	if(modflag)
	{
		for(int i = 0; i < vals.size(); i++ ) 
		for( int j = 0; j < vals.size(); j++ )
			if( i != j )
				ExecuteMOD( vals[i], vals[j] );
	}	
	
	if(andflag)
	{				
		for(int i = 0; i < vals.size(); i++ ) 
		for( int j = 0; j < vals.size(); j++ )
			if( i != j )
				ExecuteAND( vals[i], vals[j] );
	}
	if(eqflag)
	{
		for(int i = 0; i < vals.size(); i++ ) 
		for( int j = 0; j < vals.size(); j++ )
			if( i != j )
				ExecuteEQ( vals[i], vals[j] );
	}
	
	
	return 0;
}

