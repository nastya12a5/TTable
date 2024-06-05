#pragma once

#define _ARRAY_TABLE_H
#define TabMaxSize 25
#include "TTable.h"
#include <iostream>
#include<string>
enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };
using namespace std;

class TArrayTable:public TTable
{
protected:
	TRecord* pRecs;
	int TabSize;
	int CurrPos;
public:
    TArrayTable(int Size = TabMaxSize) { 
        pRecs = new TRecord[Size];
        
        TabSize = Size; DataCount = CurrPos = 0;
        pRecs = new TRecord[TabSize];
    }

    ~TArrayTable() {
        
        delete[] pRecs;
    }

    
     bool IsFull()  { 
        return DataCount >= TabSize;
    }

    int GetTabSize() const { return TabSize; }     

    
     int GetKey()  { return pRecs[CurrPos].key; }
    int GetValue()  { return pRecs[CurrPos].val; }
    
    

    
    virtual bool Find(TKey k) = 0;
    virtual void Insert(TRecord rec) = 0; 
    virtual void Delete(TKey k) = 0;        
    virtual void Reset()
    {
        CurrPos = 0;
        
    }
    bool IsFull() const  { return DataCount == TabSize; }
     bool IsEnd() 
    {
        return CurrPos >= DataCount;
    }
    virtual void GoNext()
    {
        CurrPos++;
        
    }
   
    virtual int SetCurrentPos(int pos)
    {
        CurrPos = ((pos > -1) && (pos < DataCount)) ? pos : 0;
        return IsEnd();
    }
    int GetCurrentPos() const { return CurrPos; }     
    

};

