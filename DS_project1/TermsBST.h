#pragma once
#include "TermsBSTNode.h"

class TermsBST
{
private:
	TermsBSTNode* root;
	ifstream flog;
	int mem = 0;

public:
	TermsBST();
	~TermsBST();

	TermsBSTNode* getRoot();

	//set BST Node root
	void setRoot(TermsBSTNode* node);

	// insert node
	void insert(TermsBSTNode* NewNode);

	// print node
	void print(TermsBSTNode* temp, ofstream& flog);

	// search
	bool search_date(TermsBSTNode* cur, const char* date, const char* name);
	bool search_date_v2(TermsBSTNode* root, const char* date);

	// delete
	bool delete_date(const char* name, const char* date);
	bool delete_date_v2(const char* date);
};