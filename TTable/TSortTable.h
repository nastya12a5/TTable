#pragma once
#include "TScanTable.h"

enum SortType { Merge, Bubble, Quick };

class TSortTable :public TScanTable
{
private:
	void BubbleSort()
	{
		if (this->empty()) return;

		for (int i = 0; i < this->DataCount; i++)
		{
			for (int j = i + 1; j < this->DataCount; j++)
			{
				if (this->pRecs[i].key > this->pRecs[j].key)
				{
					std::swap(this->pRecs[i], this->pRecs[j]);
				}
			}
		}
	}
	void QuickSort(int first, int last)
	{
		if (this->empty()) return;

		int mid = (first + last) / 2;
		TKey key = this->pRecs[mid].key;
		int leftPos = first, rightPos = last;

		while (leftPos < rightPos)
		{
			while (this->pRecs[leftPos].key < key)
			{
				leftPos++;
				this->eff++;
			}
			while (this->pRecs[rightPos].key > key)
			{
				rightPos--;
				this->eff++;
			}
			if (leftPos <= rightPos)
			{
				std::swap(this->pRecs[leftPos], this->pRecs[rightPos]);
				leftPos++;
				rightPos--;
				this->eff++;
			}
		}

		if (rightPos > first) QuickSort(first, rightPos);
		if (leftPos < last) QuickSort(leftPos, last);
	}
	void MergeSort(int left, int right)
	{
		if (left == right)
		{
			return;
		}
		else
		{
			int mid = (right + left) / 2;
			MergeSort(left, mid);
			MergeSort(mid + 1, right);
			Merge(left, mid, right);
		}
	}
	void Merge(int left, int mid, int right)
	{
		TRecord* mas2;
		mas2 = new TRecord[this->DataCount];

		int i = left, j = mid + 1, k = left;
		while (i <= mid && j <= right)
		{
			if (this->pRecs[i].key < this->pRecs[j].key)
			{
				mas2[k] = this->pRecs[i];
				k++; i++;
			}
			else
			{
				mas2[k] = this->pRecs[j];
				k++; j++;
			}
		}

		if (i > mid)
		{
			while (j <= right)
			{
				mas2[k] = this->pRecs[j];
				j++; k++;
			}
		}
		else
		{
			while (i <= mid)
			{
				mas2[k] = this->pRecs[i];
				i++; k++;
			}
		}

		for (i = left; i <= right; i++)
		{
			this->pRecs[i] = mas2[i];
		}
		delete[] mas2;
	}

public:
	TSortTable(int _size = TabMaxSize) :TScanTable(_size) { if (_size > TabMaxSize) throw "ex"; };
	void ScanToSort(TScanTable& table, SortType sortType)
	{
		for (this->Reset(), table.Reset(); !table.IsEnd(); table.GoNext(), this->GoNext())
		{
			//this->SetCurrentRecord(table.GetCurrentRecord());
			this->DataCount++;
		}
		if (sortType == SortType::Quick) this->QuickSort(0, this->DataCount - 1);
		if (sortType == SortType::Merge) this->MergeSort(0, this->DataCount - 1);
		if (sortType == SortType::Bubble) this->BubbleSort();
	}

	bool Find(TKey key)
	{
		int begin = 0, end = this->DataCount - 1, middle;
		while (begin <= end)
		{
			eff++;
			middle = (begin + end) / 2;
			if (this->pRecs[middle].key < key)
			{
				begin = middle + 1;
			}
			else if (this->pRecs[middle].key > key)
			{
				end = middle - 1;
			}
			else {
				this->CurrPos = middle; return true;
			}
		}
		this->CurrPos = begin;
		return false;
	}
	void Insert(TRecord record)
	{
		if (IsFull() || Find(record.key))
		{
			throw "full";
		}
		for (int i = this->DataCount - 1; i >= this->CurrPos; i--)
		{
			this->pRecs[i + 1] = this->pRecs[i];
			eff++;
		}

		this->pRecs[CurrPos] = record;
		eff++;
		this->DataCount++;
	}
	void Delete(TKey key)
	{
		if (!Find(key))
		{
			throw "exp";
			return;
		}
		for (int i = this->CurrPos; i < this->DataCount - 1; i++)
		{
			this->pRecs[i] = this->pRecs[i + 1];
			eff++;
		}
		this->DataCount--;
	}

	TSortTable operator=(const TSortTable& other)
	{
		if (this->TabSize != other.TabSize)
		{
			delete[] this->pRecs;
			this->TabSize = other.TabSize;
			this->pRecs = new TRecord[this->TabSize];
		}
		this->DataCount = other.DataCount;
		this->eff = other.eff;
		for (int i = 0; i < this->TabSize; i++)
		{
			this->pRecs[i] = other.pRecs[i];
		}
		this->CurrPos = other.CurrPos;
		return *this;
	}
};


 



 

 

 



 


