#pragma once
#include<list>
#include "THashTable.h"
#define TabMaxSize 200

using namespace std;

class TListHash :public THashTable
{
protected:
	list<TRecord>* pList;
	int MaxSize, CurrList;
	list<TRecord>::iterator pCurr;
public:
	TListHash(int size = TabMaxSize)
	{
		MaxSize = size;
		if (MaxSize > TabMaxSize) throw "big_size";
		pList = new list<TRecord>[MaxSize];
		CurrList = 0;
		
	}
	~TListHash()
	{
		
		delete[] pList;
	}
	bool IsFull()
	{
		return DataCount == MaxSize;
	}
	int GetKey() { return pCurr->key; }
	int GetValue() { return pCurr->val; }
	int GetSize() { return MaxSize; }
	bool Find(TKey Key)
	{
		CurrList = HashFunc(Key) % MaxSize;
		for (pCurr = pList[CurrList].begin(); pCurr != pList[CurrList].end(); pCurr++)
		{
			eff++;
			if (pCurr->key == Key) { return true; }
		}

		return false;
	}
	void Insert(TRecord r)
	{
		if (IsFull()) { throw "full table"; }
		bool res = Find(r.key);
		if (res == true) { return; }
		else {
			eff++;
			pList[CurrList].push_front(r);
			DataCount++;
		}
	}
	void Delete(TKey Key)
	{
		bool res = Find(Key);
		if (res == false) { throw "exp"; return; }
		else
		{
			pList[CurrList].erase(pCurr);
			DataCount--;
		}
	}
	void Reset()
	{
		CurrList = 0;
		pCurr = pList[CurrList].begin();
		while (pCurr == pList[CurrList].end())
		{
			CurrList++;
			if (CurrList < MaxSize)
			{
				pCurr = pList[CurrList].begin();
			}
			else { break; }
		}
	}
	void GoNext()
	{
		pCurr++;
		while (pCurr == pList[CurrList].end())
		{
			CurrList++;
			if (CurrList < MaxSize)
			{
				pCurr = pList[CurrList].begin();
			}
			else { break; }
		}
	}
	bool IsEnd() { return CurrList == MaxSize; }

};


