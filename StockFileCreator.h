#pragma once
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include "StockInfo.h"

typedef pair <string, StockInfo> Symbol_StockInfo_Pair;
typedef pair <multimap<string, StockInfo >::iterator, multimap<string, StockInfo >::iterator> Symbol_StockInfo_Iterator_Pair;

class StockFileCreator
{
public:
	StockFileCreator(void);
	void SetData(multimap<string,StockInfo>&);
	void WriteStockFile(string key);
	~StockFileCreator(void);

private:
	multimap<string, StockInfo > stockMultiMapInternal;
};

