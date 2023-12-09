#pragma once
#include "TermsListNode.h"

class TermsLIST
{
private:
	TermsListNode* head;	//head node

public:
	TermsLIST();
	~TermsLIST();
	//get head node
	TermsListNode* getHead();

	//insert
	void insert(TermsBSTNode* NextNode);
	//print
	bool print(char contract, ofstream& flog);
	// search
	bool search_date(const char* name, const char* date);
	bool search_date_v2(TermsBSTNode* root, const char* date, const char* name);

	// delete
	bool delete_date(const char* name, const char* date);
	bool delete_date_v2(const char* date);
};
