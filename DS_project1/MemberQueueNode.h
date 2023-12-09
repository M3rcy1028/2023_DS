#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class MemberQueueNode
{
private:
	//informations
	char name[50];
	int age;
	char date[9];
	char contract; //A(6months), B(12months), C(24months), D(36months)
	MemberQueueNode* Next;

public:
	MemberQueueNode() {}
	MemberQueueNode(char name1[], int age1, char date1[], char contract1)
	{
		//store infromations
		strcpy(name, name1);
		age = age1;
		for (int i = 0; i < 8; i++)
		{
			date[i] = date1[i];
		}
		contract = contract1;
		Next = nullptr;
	}
	//return next node address
	MemberQueueNode* NextNode()
	{
		return Next;
	}

	//set next node address
	void SetNextNode(MemberQueueNode* Node)
	{
		Next = Node;
		return;
	}

	//return name
	char* GetName()
	{
		return name;
	}

	//return age
	int Getage()
	{
		return age;
	}

	//return date
	char* Getdate()
	{
		return date;
	}

	//return contract
	char Getcontract()
	{
		return contract;
	}

	~MemberQueueNode() 
	{
		Next = nullptr;
	}

};