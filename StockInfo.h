#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <istream>
using namespace std;

class StockInfo
{
	friend istream& operator >>( istream& in, StockInfo& stockInfo );
	friend ostream& operator <<( ostream& os, StockInfo& stockInfo );
	friend bool operator > (const StockInfo& one, const StockInfo& two );
	
public:
	StockInfo(void);
	~StockInfo(void);
	
	std::string GetSymbol() { return symbol; };
	float GetStockPrice( ) { return stockPrice; };
	int GetStockQuantity( ) { return quantity; };
	int GetSequence( ) { return sequence; };
	//bool operator >( StockInfo const& compareObj);

private:
	int sequence;//hex number
	
	std::string symbol;	//ascii text
	float  stockPrice; //decimal
	int quantity;//integer
	
};


