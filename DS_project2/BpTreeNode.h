#pragma once
#include "LoanBookData.h"
#include <map>

//base class of BpTree
class BpTreeNode
{
private:
	BpTreeNode* pParent;
	BpTreeNode* pMostLeftChild;

public:
	BpTreeNode() {
		pParent = NULL;
		pMostLeftChild = NULL;
	}
	~BpTreeNode() {

	}

	void setMostLeftChild(BpTreeNode* pN) { pMostLeftChild = pN; }
	void setParent(BpTreeNode* pN) { pParent = pN; }

	BpTreeNode* getParent() { return pParent; }
	BpTreeNode* getMostLeftChild() { return pMostLeftChild; }

	virtual void setNext(BpTreeNode* pN) {}
	virtual void setPrev(BpTreeNode* pN) {}
	virtual BpTreeNode* getNext() { return NULL; }
	virtual BpTreeNode* getPrev() { return NULL; }

	virtual void insertDataMap(string n, LoanBookData* pN) {}
	virtual void insertIndexMap(string n, BpTreeNode* pN) {}
	virtual void deleteMap(string n) {}

	virtual map<string, BpTreeNode*>* getIndexMap() { return {}; }
	virtual map<string, LoanBookData*>* getDataMap() { return {}; }

};
