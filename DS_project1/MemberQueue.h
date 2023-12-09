#pragma once
#include "MemberQueueNode.h"

class MemberQueue
{
private:
	int QueueSize = 100;
	MemberQueueNode* Qhead;
	MemberQueueNode* Qtail;

public:
	MemberQueue();
	~MemberQueue();

	//functino declarations
	bool empty();
	bool full();
	void push(char name[], int age, char date[], char contract);
	MemberQueueNode* pop();
	MemberQueueNode* front();
};

