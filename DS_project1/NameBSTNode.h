#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class NameBSTNode
{
private:
	//store information
	char name[30];
	int age;
	char date[9];
	char contract;
	char ex_date[8];

	NameBSTNode* left;
	NameBSTNode* right;


public:
	NameBSTNode() {}
	NameBSTNode(char name[], int age, char date[], char contract)
	{
		//store information
		strcpy(this->name, name);
		this->age = age;
		for (int i = 0; i < 8; i++)
		{
			this->date[i] = date[i] + 65;
		}
		this->contract = contract;
		CalExDate();
		//initialization
		left = nullptr;
		right = nullptr;
	}
	~NameBSTNode() 
	{
		//initialization
		left = nullptr;
		right = nullptr;
	}

	//return name
	char* GetName()
	{
		return name;
	}
	//return age
	int GetAge()
	{
		return age;
	}
	//return name
	char* GetDate()
	{
		return date;
	}
	//return expired date
	char* GetExpiredDate()
	{
		return ex_date;
	}
	//return contract
	char GetContract()
	{
		return this->contract;
	}
	//get left node
	NameBSTNode* getLeft() { return left; }
	//get right node
	NameBSTNode* getRight() { return right; }

	//set left node
	void setLeft(NameBSTNode* left) { this->left = left; }
	//set right node
	void setRight(NameBSTNode* right) { this->right = right; }

	//print its information
	void print(ofstream& flog)
	{
		flog << name << '/' << age << '/';
		for (int i = 0; i < 8; i++)
		{
			if (i == 4 || i == 6)
				flog << '-';
			flog << date[i] - 65;
		}
		flog << '/';

		//print expired date
		for (int i = 0; i < 8; i++)
		{
			if (i == 4 || i == 6)
				flog << '-';
			flog << ex_date[i] - 65;
		}
		flog << '\n';
		return;
	}

	//compute expired date
	void CalExDate()
	{
		//calculate expired date
		int a = 0, b = 0; //year, month
		switch (contract)
		{
		case 'A':
		{
			a = 0, b = 6;
			break;
		}
		case 'B':
		{
			a = 1, b = 0;
			break;
		}
		case 'C':
		{
			a = 2, b = 0;
			break;
		}
		case 'D':
		{
			a = 3, b = 0;
			break;
		}
		default:
			break;
		}
		a += month(b);
		year(a);
		ex_date[6] = date[6];
		ex_date[7] = date[7];
	}

	//compute year
	void year(int a)
	{
		//year
		int b = (date[0] - 65) * 1000 + (date[1] - 65) * 100 + (date[2] - 65) * 10 + (date[3] - 65) + a;
		ex_date[3] = (b % 10) + 65;
		ex_date[2] = ((b / 10) % 100) + 65;
		ex_date[1] = ((b / 100) % 10) + 65;
		ex_date[0] = ((b % 1000) / 10) + 65;
		return;
	}

	//compute month
	int month(int b)
	{
		int a = (date[4] - 65) + (date[5] - 65) + b;	//month
		int c = a / 12;	//compute year
		a = a % 12;	//re-compute month
		ex_date[4] = (a / 10) + 65;
		ex_date[5] = (a % 10) + 65;
		return c;
	}

};