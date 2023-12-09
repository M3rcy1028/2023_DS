#pragma once
#include "NameBSTNode.h"

class NameBST
{
private:
	NameBSTNode* root;
	char return_date[8];
	
public:
	NameBST();
	~NameBST();

	NameBSTNode* getRoot();

	// insert
	void insert(NameBSTNode* NewNode);
	// search
	bool search(const char* find, ofstream& flog);
	// print
	void print(NameBSTNode* temp, ofstream& flog);
	// delete
	char* delete_name(const char* name);
	bool delete_name_v2(NameBSTNode* ptr, NameBSTNode* ptr_prev, const char* date);
};
