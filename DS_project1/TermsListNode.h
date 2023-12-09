#pragma once
#include "TermsBST.h"

class TermsListNode
{
private:
	TermsListNode* next; //next list node address
	TermsBST* BST_tree_root;
	int cnt = 0;
	char contract;

public:
	TermsListNode() 
	{
		next = nullptr;
		BST_tree_root = nullptr;
	}
	~TermsListNode() 
	{
		next = nullptr;
		delete BST_tree_root;
	}

	TermsListNode* getNext() { return next; }

	//return contract
	char GetContract() { return contract; }

	//set contract
	void setContract(char a) { contract = a; }

	//increase total the number of nodes in BST
	void incNodeCnt()
	{
		cnt++;
		return;
	}

	//decrease total the number of nodes in BST
	void decNodeCnt()
	{
		cnt--;
		return;
	}

	//return the number of members in TermsListNode
	int getNodeCnt() { return cnt; }

	//print all nodes
	void print(ofstream& flog)
	{
		BST_tree_root->print(BST_tree_root->getRoot(), flog);
	}

	//return BST Node
	TermsBST* getBST() { return BST_tree_root; }
	void setBST(TermsBST* p) { BST_tree_root = p; }

	//set next node address
	void setNext(TermsListNode* next) { this->next = next; }
};
