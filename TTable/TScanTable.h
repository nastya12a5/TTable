#pragma once
#ifndef _SCANTAB_H
#define _SCANTAB_H

#include "TArrayTable.h"

class  TScanTable : public TArrayTable {
public:
    TScanTable(int Size = TabMaxSize) : TArrayTable(Size) {};
   
    virtual bool Find(TKey k)
    {
        int i;
        for ( i = 0; i < DataCount; ++i)
        {
            eff++;
            if (pRecs[i].key == k) break;
        }
            CurrPos = i;
        
        if (i < DataCount)
        {
            return true;
        }
        return false;
    }
    virtual void Insert(TRecord rec)
    {
            if (IsFull())
                throw "insert in full table";
            pRecs[this->DataCount] =rec;
            DataCount++;
            eff++;
            
    }
   virtual void Delete(TKey k)
   {
       if (!Find(k)) throw "no el";
       pRecs[CurrPos] = pRecs[DataCount - 1];
       DataCount--;
       eff++;
      
    }
};

#endif


