#pragma once
#include<iostream>
#define _HASHTAB_H
#include "THashTable.h"
#define TabMaxSize 200
#define TabHashStep 13
using namespace std;


class TArrayHash:public THashTable
{
protected:
	TRecord* pRecs;
	int MaxSize, Step, Curr, Free;
	TRecord Empty, Del;
public:
	TArrayHash(int size = TabMaxSize, int step = TabHashStep)
	{
		pRecs = new TRecord[size];
		MaxSize = size;
		if (MaxSize > TabMaxSize) throw "exp";
		Step = step;
		Empty.key = -1;
		for (int i = 0; i < MaxSize; ++i)
			pRecs[i] = Empty;
		Curr = 0; Free = -1;
		Del.key = -2;
	}
	~TArrayHash()
	{
		
		delete[]pRecs;
		
	}
	int GetKey() { return pRecs[Curr].key; }
	int GetValue() { return pRecs[Curr].val; }
	int GetSize() { return MaxSize; }
	void Reset()
	{
		for (Curr = 0; Curr < MaxSize; Curr++)
		{
			if(pRecs[Curr]!=Empty&&pRecs[Curr]!=Del)
			{
				break;
			}
		}
	}
	bool IsEnd() { return Curr == MaxSize; }
	void GoNext()
	{
		for (; Curr < MaxSize; Curr++)
		{
			if (pRecs[Curr] != Empty && pRecs[Curr] != Del)
			{
				break;
			}
		}
	}
	bool Find(TKey key)
	{
		Free = -1;
		Curr = HashFunc(key) % MaxSize;
		for (int t = 0; t < MaxSize; t++)
		{
			if (pRecs[Curr].key == key)
			{
				eff++;
				return true;
			}
			if (pRecs[Curr] == Empty)
			{
				eff++;
				return false;
			}
			Curr = (Curr + Step) % MaxSize;
			eff++;
		}
		return false;
	}
	bool IsFull()
	{
		return DataCount == MaxSize;
	}
	void Insert( TRecord rec)
	{
		if (IsFull()) { throw  "full table"; }
		bool isFind = Find(rec.key);
		if (isFind == true) { return; }
		else {
			if (Free != -1) { eff++; Curr = Free; }
			pRecs[Curr] = rec;
			DataCount++;
		}
	}
	void Delete(TKey Key)
	{
		if (empty()) throw "isempty";
		bool isFind = Find(Key);
		if (isFind == false) {
			//throw "exp";
		return; }
		else {
			eff++;
		pRecs[Curr] = Del;
		DataCount--;
        }
	}
};

