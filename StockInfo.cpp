#include "StdAfx.h"
#include "StockInfo.h"


StockInfo::StockInfo(void)
{
}


StockInfo::~StockInfo(void)
{
}

istream& operator >>( istream& in, StockInfo& stockInfo )
{
	in >> std::hex >> stockInfo.sequence;
	in >> std::dec;
	in >> stockInfo.symbol;
	in >> stockInfo.stockPrice;
	in >> stockInfo.quantity;
	return in;
}

ostream& operator <<( ostream& os, StockInfo& stockInfo )
{
os << stockInfo.sequence << " ";
os << stockInfo.symbol << " " ;
os << stockInfo.stockPrice << " " ;
os << stockInfo.quantity << " " ;
return os;
}



//custom operator > overload for printing
	
bool operator > (const StockInfo& one, const StockInfo& two )
{
	if ( one.stockPrice == two.stockPrice )
	{
		//order by seq number
		if( one.sequence > two.sequence ) return true;
		else return false;
	}
	else return ( one.stockPrice > two.stockPrice );
}