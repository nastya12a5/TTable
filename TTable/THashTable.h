#pragma once
#include<iostream>
#define _HASHTAB_H
#include "TTable.h"
using namespace std;

class THashTable:public TTable
{
protected:
	/*virtual  int HashFunc(const TKey key)
	{
		int hashval = key;
		return hashval;
	}*/
	virtual int HashFunc(const TKey key)
	{
		
		
		
		int	hashval = key;
		return hashval;
	}
public:
	THashTable() :TTable() {}
};

