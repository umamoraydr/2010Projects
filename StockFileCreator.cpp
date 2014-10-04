#include "StdAfx.h"
#include "StockFileCreator.h"
#include <string>


StockFileCreator::StockFileCreator(void)
{
}


StockFileCreator::~StockFileCreator(void)
{
}

void StockFileCreator::SetData( multimap<string,StockInfo>& inMMap )
{
	stockMultiMapInternal = inMMap;
}

void StockFileCreator::WriteStockFile( string key )
{
	//open the file
	ofstream outFileStream(  key + ".csv" );

	Symbol_StockInfo_Iterator_Pair p;
	//get the range that matches the key
	p = stockMultiMapInternal.equal_range( key );

	std::list<StockInfo> sorterList;
	while( (p.first != p.second) && (p.first != stockMultiMapInternal.end()) )//check for end
	{		
		sorterList.push_back( (StockInfo)p.first->second );
		(p.first)++;		
    }

	cout << "\nSymbol: " << key << " Rows received: " << sorterList.size() << endl;
	
	//now sort the list
	std::greater<StockInfo> predicate;
	sorterList.sort( predicate);

	list<StockInfo>::iterator listIt = sorterList.begin();
	
	//print the list to file
	while( listIt != sorterList.end() )
	{
		outFileStream << listIt->GetStockPrice();
		outFileStream << "," ;
		outFileStream << listIt->GetStockQuantity() ;
		outFileStream << "," ;
		outFileStream << std::dec << listIt->GetSequence() << endl;
		listIt++;
	}

	//close the file
	outFileStream.close();
}
