#pragma once
#define  H_OK 0
#define  H_INC 1
#define  H_DEC -1
#include<iostream>
#include "TTable.h"
#include <stack>
#include <corecrt_io.h>
#include <corecrt_io.h>
#include<fstream>
using namespace std;

struct TTreeNode {
	TRecord rec;
	TTreeNode* pLeft, * pRight;
	int bal ;

	TTreeNode(const TRecord& _rec)
	{
		rec = _rec;
		pLeft = nullptr;
		pRight = nullptr;
		bal = H_OK;
	}
};

class TTreeTable:public TTable
{
protected:
	TTreeNode *pRoot, *pCurr, *pPrev;
	stack <TTreeNode *> st;
	int CurrPos, level = 0;
public:
	TTreeTable()
	{
		pRoot = pCurr = pPrev = NULL;
	}
	bool Find(TKey k)
	{
	pPrev = NULL;
	pCurr = pRoot;
	while (pCurr != NULL)
	{
		eff++;
		if (pCurr->rec.key == k) break;
		else
		{
			pPrev = pCurr;
			if (pCurr->rec.key > k)
			{
				pCurr = pCurr->pLeft;
			}
			else pCurr = pCurr->pRight;
			
		}
	}
	if (pCurr != NULL) return true;
	else { pCurr = pPrev; return false; }
	}
	void Insert(TRecord _rec)
	{
		bool res = Find(_rec.key);
		if (res == true) return;
		else
		{
			DataCount++;
			TTreeNode* pNew = new TTreeNode(_rec);
		
		if (pRoot == NULL) pRoot = pNew;
		else
		{
			if (pCurr->rec.key > _rec.key)
				pCurr->pLeft = pNew;
			else pCurr->pRight = pNew;
		}
		}
	}
	void Delete(TKey k)
	{
		bool res = Find(k);
		TTreeNode* pDel;
		if (res == false) return;

		else
		
			if (pCurr->pRight == NULL)
			{
				pDel = pCurr;
				if (pPrev == NULL) pRoot = pCurr->pLeft;
				else
				{
					if (pPrev->rec.key > pCurr->rec.key)
					{
						pPrev->pLeft = pCurr->pLeft;
					}
					else
					{
						if (pPrev->rec.key < pCurr->rec.key)
						{
							pPrev->pRight = pCurr->pLeft;
						}
					}
				}

			}
			else
			
				if (pCurr->pLeft == NULL)
				{
					pDel = pCurr;
					if (pPrev == NULL) pRoot = pCurr->pRight;
					else
					{
						if (pPrev->rec.key > pCurr->rec.key)
						{
							pPrev->pLeft = pCurr->pRight;
						}
						else
						{
							if (pPrev->rec.key < pCurr->rec.key)
							{
								pPrev->pRight = pCurr->pRight;
							}
						}
					}
				}
			
			else
			{
			TTreeNode* pN = pCurr->pLeft;
			pPrev = pCurr;
			while (pN->pRight != NULL)
			{
				pPrev = pN;
				pN = pN->pRight;
				eff++;
			}
			pCurr->rec = pN->rec;
			if (pPrev->pRight == pN)
			{
				pPrev->pRight = pN->pLeft;


			}
			else
			{
				pPrev->pLeft = pN->pLeft;
			}
			pDel = pN;
			eff++;

		    }
		eff++;
		delete pDel;
		DataCount--;
		
	}
	bool IsFull()  { return false; };
	int GetKey() { return pCurr->rec.key; };
	int GetValue() { return pCurr->rec.val; };
	void SetCurrentRecord(TRecord record)
	{
		pCurr->rec.key = record.key;
		pCurr->rec.val = record.val;
	};
	void Reset()
	{
		TTreeNode* pNode = pCurr = pRoot;
		while (!st.empty()) st.pop();
		CurrPos = 0;
		while (pNode != NULL)
		{
			st.push(pNode);
			pCurr = pNode;
			pNode = pNode->pLeft;
		}
	}
	void GoNext()
	{
		if (pCurr != NULL)
		{
			TTreeNode* pNode = pCurr = pCurr->pRight;
			st.pop();
			while (pNode != NULL)
			{
				st.push(pNode);
				pCurr = pNode;
				pNode = pNode->pLeft;
			}
			if ((pCurr == NULL) && !st.empty())
			{
				pCurr = st.top();
			}
			CurrPos++;
		}
	}
	bool IsEnd() 
	{
		return CurrPos >= DataCount;
	}
	void DeleteTreeTab(TTreeNode* pNode)
	{
		if (pNode != NULL)
		{
			DeleteTreeTab(pNode->pLeft);
			DeleteTreeTab(pNode->pRight);
			delete pNode;
		}
	}
	~TTreeTable() { DeleteTreeTab(pRoot); }
	void PrintTreeTab(ostream& os, TTreeNode* pNode)
	{
		if (pNode != nullptr)
		{
			for (int i = 0; i < level; i++)
			{
				os << " ";
			}
			os << pNode->rec.key << std::endl;
			level++;
			PrintTreeTab(os, pNode->pRight);
			PrintTreeTab(os, pNode->pLeft);
			level--;

		}
	}
	
	void PrintTreeTab_f( TTreeNode* pNode,ofstream&fout)
	{
		
		if (pNode != nullptr)
		{
			for (int i = 0; i < level; i++)
			{
				fout << " ";
			}
			fout << pNode->rec.key << std::endl;
			level++;
			PrintTreeTab_f( pNode->pRight,fout);
			PrintTreeTab_f( pNode->pLeft,fout);
			level--;

		}
		
	}
	void PrintTree_f()
	{
		ofstream fout("text.txt");
		level = 0; // Сбрасываем уровень перед началом печати дерева
		PrintTreeTab_f( pRoot,fout);
		fout.close();
		// Вызываем рекурсивную функцию для печати дерева, начиная с корневого узла
	}
	/*void PrintTreeTab(ostream& os, TTreeNode* pNode)
	{
		if (pNode != nullptr)
		{
			level++; // Увеличиваем уровень перед переходом к следующему узлу
			PrintTreeTab(os, pNode->pRight); // Рекурсивный вызов для правого поддерева
			for (int i = 0; i < level; i++)
			{
				os << "\t"; // Вывод отступов в соответствии с текущим уровнем
			}
			os << pNode->rec.key << endl; // Вывод ключа узла
			PrintTreeTab(os, pNode->pLeft); // Рекурсивный вызов для левого поддерева
			level--; // Уменьшаем уровень после обработки узла и его поддеревьев
		}
	}*/
	void PrintTree(ostream& os)
	{
		level = 0; // Сбрасываем уровень перед началом печати дерева
		PrintTreeTab(os, pRoot); // Вызываем рекурсивную функцию для печати дерева, начиная с корневого узла
	}
};
	
