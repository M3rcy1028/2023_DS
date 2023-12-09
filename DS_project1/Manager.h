#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Manager
{
private:
	ifstream	fcmd;
	ofstream	flog;
	MemberQueue* MQueue = new MemberQueue();
	TermsLIST* TermsList = new TermsLIST();
	NameBST* NameList = new NameBST();

public:
	Manager();
	~Manager();

	void run(const char* command);

	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	// LOAD
	void LOAD();
	// ADD
	void ADD(char[]);
	// QPOP
	void QPOP();
	// SEARCH
	void SEARCH(const char* name);
	// PRINT
	void PRINT(char ch);
	void PRINT_NAME();
	// DELETE
	void DELETE_NAME(const char* name);
	void DELETE_DATE(const char* date);
};
