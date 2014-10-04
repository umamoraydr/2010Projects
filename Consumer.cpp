// Consumer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>
#include <sstream>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include "StockInfo.h"
#include "UDPReceiver.h"
#include "StockFileCreator.h"

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")


//main program
int _tmain(int argc, _TCHAR* argv[])
{

cout << "\nCONSUMER STARTING..." << endl;
	
//CONTAINER TO STORE THE UNIQUE SYMBOLS
set<string> symbolSet;
//CONTAINER TO STORE THE SYMBOL - STOCKINFO PAIRS FROM EACH ROW
multimap<string, StockInfo > stockMultiMap;

//UDP RECEIVER
UDPReceiver udpReceiver;
//initialize the UDP Receiver
if( udpReceiver.Initialize() < 0 )
{
	cout << "\nError creating the UDPReceiver" << endl;
	return -1;
}

//INFINITE LOOP THAT EXITS ON RECEIVING A END MESSAGE
while(1)
{
	std::string line;
	udpReceiver.ReceiveUDPMessage(line);

	//CHECK IF THIS WAS THE END MESSAGE
	if( line == string(",,,"))
	{		
		cout <<"\nThe consumer has now received all the data" << endl;
		break;
	}//end if

	std::replace(line.begin(), line.end(), ',', ' '); //replace comma by space to read it,check exceptiom

	std::istringstream iss(line);
	//CREATE A STOCKINFO OBJECT FROM EACH ROW
	StockInfo stkInfo;
	if (!(iss >> stkInfo)) 
	{ 
		cout << "\nUnable to read message" << endl;
		break; 
	} // error		
    
	//INSERT SYMBOL-STOCKINFO OBJECT IN THE MULTIMAP
	stockMultiMap.insert( Symbol_StockInfo_Pair(stkInfo.GetSymbol(), stkInfo) );

	//INSERT SYMBOL IN SET
	symbolSet.insert( stkInfo.GetSymbol() );	
}//end while

//CLASS THAT CREATES FORMATTED FILE FOR EACH SYMBOL
StockFileCreator sfCreator;
sfCreator.SetData(stockMultiMap);

set<string>::iterator setIt =symbolSet.begin();

//ITERATE THROUGH ALL THE SYMBOLS IN THE SET
while( setIt != symbolSet.end() )
{	
	//WRITE A STOCK FILE FOR EACH SYMBOL
	sfCreator.WriteStockFile( (*setIt ));
	setIt++;	
}
return 0;
}
