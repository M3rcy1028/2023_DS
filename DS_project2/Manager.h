#pragma once
#include "SelectionTree.h"
#include "BpTree.h"

class Manager
{
private:
	//char* cmd;
	BpTree* bptree;
	SelectionTree* stree;
	//BpTree* bptree;
public:
	Manager(int bpOrder)	//constructor
	{
		//flog.open("log.txt");
		bptree = new BpTree(&flog);
		stree = new SelectionTree(&flog);
	}


	~Manager()//destructor
	{
		delete bptree;
		delete stree;
	}

	ifstream fin;
	ofstream flog;
	

	void run(const char* command);
	bool LOAD();
	bool ADD(string buffer);

	bool SEARCH_BP_BOOK(string book);
	bool SEARCH_BP_RANGE(string start, string end);

	bool PRINT_BP();
	bool PRINT_ST(int BookCode);

	bool DELETE();

	void printErrorCode(int n);
	void printSuccessCode(const char* cmd);

};

