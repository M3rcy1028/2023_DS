#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"
#include <fstream>
#include <map>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class BpTree {
private:
	BpTreeNode* root;
	int			order;		// m children
	ofstream* fout;
public:
	BpTree(ofstream *fout, int order = 3) {
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	~BpTree()
	{
		BpTreeNode* pCur = root;
		while(pCur->getMostLeftChild())	//reach data map
			pCur = pCur->getMostLeftChild();
		while (pCur->getPrev() != NULL)
			pCur = pCur->getPrev();
		//delete data map memory
		BpTreeNode* NpCur = pCur;
		while (NpCur)
		{
			pCur = NpCur;
			NpCur = pCur->getNext();
			delete pCur;
		}
	}
	/* essential */
	bool		Insert(LoanBookData* newData);
	bool		excessDataNode(BpTreeNode* pDataNode);
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }
	BpTreeNode* searchDataNode(string name);

	void printAllDataNode();
	bool searchBook(string name);
	bool searchRange(string start, string end);

};

#endif
