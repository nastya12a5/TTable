#pragma once
#include "TTreeTable.h"
enum bal { BalOK, BalLeft, BalRight };

using namespace std;

class TBalTreeTable:public TTreeTable
{
protected:
	int InsBalTree(TTreeNode*& pNode, TRecord rec)
	{
		int res = H_OK; eff++;
		if (pNode == NULL)
		{
			pNode = new TTreeNode(rec);
			res = H_INC;
			DataCount++;
		}
		else if (pNode->rec.key > rec.key)
		{
			int tmp = InsBalTree(pNode->pLeft, rec);
			if (tmp == H_INC)
			{
				res = LeftBalanse(pNode);
			}
		}
		else if (pNode->rec.key < rec.key)
		{
			int tmp = InsBalTree(pNode->pRight, rec);
			if (tmp == H_INC)
			{
				res = RightBalanse(pNode);
			}
		}
		return res;
	}
	int LeftBalanse(TTreeNode*& pNode)
	{
		eff++;
		int res = H_OK;
		switch (pNode->bal)
		{
		case BalRight:pNode->bal = BalOK;
			res = H_OK;
			break;

		case BalOK:pNode->bal = BalLeft;
			res = H_INC; break;
		case BalLeft:TTreeNode* p1;TTreeNode* p2;
			p1 = pNode->pLeft;

			if (p1->bal == BalLeft)
			{
				pNode->pLeft = p1->pRight;
				p1->pRight = pNode;
				pNode->bal = BalOK;
				pNode = p1;
				pNode->bal = BalOK;
			}
			else
			{
				p2 = p1->pRight;
				p1->pRight = p2->pLeft;
				pNode->pLeft = p2->pRight;
				p2->pLeft = p1;
				p2->pRight = pNode;

				if (p2->bal == BalRight)
				{
					p1->bal = BalLeft;
					pNode->bal = BalOK;
				}
				else
				{
					p1->bal = BalOK;
					pNode->bal = BalRight;
				}
				pNode = p2;
				pNode->bal = BalOK;
			}
			res = H_OK;
		}
		return res;
	}
	int RightBalanse(TTreeNode*& pNode)
	{
		eff++;
		int res = H_OK;
		switch (pNode->bal)
		{
		case BalLeft:pNode->bal = BalOK;
			res = H_OK;
			break;

		case BalOK:pNode->bal = BalRight;
			res = H_INC; break;
		case BalRight:TTreeNode* p1, * p2;
			p1 = pNode->pRight;
			if (p1->bal == BalRight)
			{
				pNode->pRight = p1->pLeft;
				p1->pLeft = pNode;
				pNode->bal = BalOK;
				pNode = p1;
				pNode->bal = BalOK;
			}
			else
			{
				p2 = p1->pLeft;
				p1->pLeft = p2->pRight;
				pNode->pRight = p2->pLeft;
				p2->pRight = p1;
				p2->pLeft = pNode;

				if (p2->bal == BalRight)
				{
					p1->bal = BalLeft;
					pNode->bal = BalOK;
				}
				else
				{
					p1->bal = BalOK;
					pNode->bal = BalRight;
				}
				pNode = p2;
				pNode->bal = BalOK;
			}
			res = H_OK;
		}
		return res;
	}
	
	int DeleteRec(TTreeNode*& pNode, TKey key)
	{
		int res = H_OK; eff++;
		if (pNode == NULL) return H_OK;
		if (pNode->rec.key > key)
		{
			res = DeleteRec(pNode->pLeft, key);
			if (res != H_OK)
				res = RightBalanse(pNode);
		}
		else if (pNode->rec.key < key)
		{
			res = DeleteRec(pNode->pRight, key);
			if (res != H_OK) res = LeftBalanse(pNode);
		}
		else
		{
			DataCount--;
			if (pNode->pRight == NULL && pNode->pLeft == NULL)
			{
				delete pNode;
				pNode = NULL;
				res = H_DEC;
			}
			else if (pNode->pRight == NULL)
			{
				pNode->rec = pNode->pLeft->rec;
				delete pNode->pLeft;
				pNode->pLeft = NULL;
				pNode->bal = BalOK;
				res = H_DEC;
			}
			else if (pNode->pLeft == NULL)
			{
				pNode->rec = pNode->pRight->rec;
				delete pNode->pRight;
				pNode->pRight = NULL;
				pNode->bal = BalOK;
				res = H_DEC;
			}
			else
			{
				TTreeNode* l, * r;
				l = pNode->pLeft; r = pNode->pRight;
				TTreeNode* min = FindMin(r);
				res = RemoveMin(r);
				pNode->rec = min->rec;
				delete min;
				pNode->pLeft = l; pNode->pRight = r;
				if (res != H_OK) res = LeftBalanse(pNode);

			}
		}
		return res;
	}
	TTreeNode* FindMin(TTreeNode* r)
	{
		eff++;
		if (pRoot == NULL) return NULL;
		TTreeNode* curr = pRoot->pRight;
		while (curr->pLeft != NULL) curr = curr->pLeft;
		return curr;
	}
	int RemoveMin(TTreeNode*& pNode)
	{
		eff++;
		int res = H_OK;
		if (pNode->pLeft == NULL)
		{
			pNode = pNode->pRight;
			res = H_DEC;
		}
		else
		{
			res = RemoveMin(pNode->pLeft);
			if (res != H_OK)
				res = RightBalanse(pNode);
		}
		return res;
	}
public:
	void Insert(TRecord rec)
	{
		bool res = Find(rec.key);
		if (res == true) { return; }
		InsBalTree(pRoot, rec);
	}
	void Delete(TKey key)
	{
		if (!Find(key)) return;
		DeleteRec(pRoot, key);
	}
};

