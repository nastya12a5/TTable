#pragma once
#include <iostream>
#include<string>
using namespace std;
typedef int TKey;
typedef int TValue;
struct TRecord {
	TKey key;
	TValue val;
	TRecord()
	{
		key = 0;
		val = 0;
	}

	TRecord(TKey key, TValue value)
	{
		this->key = key;
		this->val = value;
	}

	TRecord& operator=(const TRecord& other)
	{
		key = other.key;
		val = other.val;
		return *this;
	}

	void output()
	{
		std::cout << "( " << key << "  " << val << " )" << std::endl;
	}
	bool operator == (TRecord other)
	{
		if (this->val == other.val)
			return true;
		else
			return false;
	}
	bool operator != (const TRecord& other)
	{
		return !(*this == other);
	}

};

class TTable
{
protected:
	int DataCount;
	int eff;
public:
	TTable()
	{
		DataCount = 0;
		eff = 0;
	}
	virtual ~TTable() {}
	int getDataCount() 
	{
		return DataCount;
	}
	int getEff() 
	{
		return eff;
	}
	void ClearEff()
	{
		eff = 0;
	}
	bool empty() 
	{
		return(DataCount == 0);
	}
	virtual bool IsFull()  = 0;
	virtual bool Find(TKey key) = 0;
	virtual void Insert(TRecord rec) = 0;
	virtual void Delete(TKey key) = 0;
	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;
	virtual int GetKey() = 0;
	virtual int GetValue() = 0;
	//virtual int GetRecord() = 0;
	friend ostream& operator<<(ostream& os, TTable& t)
	{
		for (t.Reset(); !t.IsEnd(); t.GoNext())
		{
			os << "Key "<<t.GetKey() <<" " << "Val " << t.GetValue() << endl;
		}
		return os;
	}


};

int main();
