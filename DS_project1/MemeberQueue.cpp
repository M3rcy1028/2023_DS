#include "MemberQueue.h"

MemberQueue::MemberQueue()
{
	QueueSize = 0;
	Qhead = nullptr;
	Qtail = nullptr;
}
MemberQueue::~MemberQueue()
{
	QueueSize = 0;
	Qhead = nullptr;
	Qtail = nullptr;
}

//whether Queue is empty
bool MemberQueue::empty()
{
	if (QueueSize == 0)
		return 1;
	return 0;
}

//whether Queue is full
bool MemberQueue::full()
{
	if (QueueSize > 100)
		return 1;
	return 0;
}

//Add nodes
void MemberQueue::push(char name[], int age, char data[], char contract)
{
	//If Queue is full
	if (full())
		exit(1);
	//create new node
	MemberQueueNode* NewNode = new MemberQueueNode(name, age, data, contract);

	//If head is empty
	if (Qhead == nullptr)
	{
		Qhead = NewNode;
		Qtail = NewNode;
	}
	else //head is not empty
	{
		MemberQueueNode* Qcur = Qhead;
		while (Qcur->NextNode() != nullptr)
			Qcur = Qcur->NextNode();	//move to next node
		Qcur->SetNextNode(NewNode);
		Qtail = NewNode;
	}
	QueueSize++; //increase the number of members
	//cout << Qtail->GetName() << endl;
	return;
}

//Pop nodes
MemberQueueNode* MemberQueue::pop()
{
	//If Queue is empty
	if (empty())
		exit(1);
	MemberQueueNode* Qpop = Qhead;	//delete node
	Qhead = Qhead->NextNode();
	QueueSize--;
	//cout << Qpop->GetName() << endl;
	return Qpop;	//return head;
}

//return front node
MemberQueueNode* MemberQueue::front()
{
	return Qhead;
}
