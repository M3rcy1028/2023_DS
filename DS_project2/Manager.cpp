#include "Manager.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void Manager::run(const char* command) 
{
	fin.open(command);	//open command.txt
	flog.open("log.txt");		//open log.txt
	if(!fin)	//cannot open file
	{
		flog << "File Open Error" << endl;
		return;
	}

	string buffer;	//store line
	while (!fin.eof())
	{
		//cout << buffer << endl;
		getline(fin, buffer);	//read line

		if (buffer.find("LOAD") != string::npos)	//LOAD
		{
			if (LOAD())
			{
				printSuccessCode("LOAD");
			}
		} 
		else if (buffer.find("ADD") != string::npos)
		{
			if (!ADD(buffer.substr(buffer.find('\t') + 1)))
			{
				printErrorCode(200);
			}
		}
		else if (buffer.find("SEARCH_BP") != string::npos)
		{
			int blank = 0;
			int pos = 10;
			//first string
			blank = buffer.find('\t', pos);	//next tab
			if (buffer.size() < 11)
				printErrorCode(300);
			else if (blank == string::npos)
			{
				if (!SEARCH_BP_BOOK(buffer.substr(pos, buffer.size() - pos - 1)))
					printErrorCode(300);
			}
			else
			{
				string c_first(buffer.substr(pos, 1));
				pos += 2;
				string c_second(buffer.substr(pos, 1));
				if (!SEARCH_BP_RANGE(c_first, c_second))
					printErrorCode(300);
			}
		}
		else if (buffer.find("PRINT_BP") != string::npos)	//PRINT B+ Tree
		{
			if (!PRINT_BP())
				printErrorCode(400);
		}
		else if (buffer.find("PRINT_ST") != string::npos)	//PRINT Selection Tree
		{
			if (!PRINT_ST(atoi(buffer.substr(buffer.find('\t') + 1).c_str())))
				printErrorCode(500);
		}
		else if (buffer.find("DELETE") != string::npos)	//DELETE
		{	
			if (!DELETE())
				printErrorCode(600);
			//flog.open("log.txt", ios::app);
		}
		else if (buffer.find("EXIT") != string::npos)	//EXIT
		{
			break;	//end program
		}
		else	//error
		{
			printErrorCode(700);
		}
	}
	printSuccessCode("EXIT");
	fin.close();
	flog.close();
	return;
}

bool Manager::LOAD()
{	
	ifstream fread;
	fread.open("loan_book.txt");
	if (!fread)
	{
		printErrorCode(100);
		return 0;
	}

	string buffer;
	while(getline(fread, buffer))
	{
		int blank = 0;	//the position of tab
		int pos = 0;	//start point of next character
		//book informaion
		// string book_name;
		// int book_code;
		// string book_author;
		// int book_year;
		// int book_loan_count;

		//store name
		blank = buffer.find("\t");	//find tab
		string book_name = buffer.substr(pos, blank - pos);	//copy book name
		pos = blank + 1;	//find next character
	
		//store book code
		blank = buffer.find("\t", pos);	//find next tab
		int book_code = atoi((buffer.substr(pos, blank - pos)).c_str());
		pos = blank + 1;
		
		//store book author
		blank = buffer.find("\t", pos);	//find next tab
		string book_author(buffer.substr(pos, blank - pos));	//copy the book author
		pos = blank + 1;
		
		//store book year
		blank = buffer.find("\t", pos);	//find next tab
		int book_year = atoi((buffer.substr(pos, blank - pos)).c_str());
		pos = blank + 1;
		
		//store loan count
		int book_loan_count = atoi((buffer.substr(pos)).c_str());

		//cout << endl << ">>Stored Inf : " << book_name << " " << book_code << " " << book_author << " " << book_year << " " << book_loan_count << "/" << endl; // check

		if (bptree->searchBook(book_name))	//already stored
		{
			printErrorCode(100);
			return 0;
		}
		//creat new LoanBookData Node and add to bptree
		LoanBookData* newData = new LoanBookData();
		newData->setBookData(book_name, book_code, book_author, book_year);
		for (int i =0; i < book_loan_count; i++)
			newData->updateCount();
		bptree->Insert(newData);
	}
	fread.close();
	return true;
}

bool Manager::ADD(string buffer)
{
	int blank = 0;	//the position of tab
	int pos = 0;	//start point of next character

	//store name
	blank = buffer.find("\t", pos);	//find tab
	if (blank == string::npos)
		return 0;
	string book_name = buffer.substr(pos, blank - pos);	//copy book name
	pos = blank + 1;	//find next character

	//store book code
	blank = buffer.find("\t", pos);	//find next tab
	if (blank == string::npos)
		return 0;
	int book_code = atoi((buffer.substr(pos, blank - pos)).c_str());
	pos = blank + 1;
	
	//store book author
	blank = buffer.find("\t", pos);	//find next tab
	if (blank == string::npos)
		return 0;
	string book_author(buffer.substr(pos, blank - pos));	//copy the book author
	pos = blank + 1;
	
	//store book year
	blank = buffer.find("\t", pos);	//find next tab
	int book_year = atoi((buffer.substr(pos, blank - pos)).c_str());
	pos = blank + 1;

	if (bptree->searchBook(book_name))	//already existed
	{
		BpTreeNode* pCur = bptree->searchDataNode(book_name);
		auto temp = pCur->getDataMap()->begin();
		if (temp->first == book_name)
			temp->second->updateCount();
		else if (pCur->getDataMap()->size() == 2)
		{
			temp++;
			if (temp->first == book_name)
				temp->second->updateCount();
			else
				return 0;	//error
		}
		else
			return 0;	//error
		flog << "========ADD========" << endl;
		flog << book_name << "/" << book_code << "/" << book_author << "/" << book_year << endl;
		flog << "===================" << endl << endl;

		//whether loan count is max
		int temp_code = temp->second->getCode();
		int temp_loan_cnt = temp->second->getLoanCount();

		if ((temp_code > 400) && (temp_loan_cnt >= 2)) //code is 500, 600, 700
		{
			stree->Insert(temp->second);
			temp->second->setDel();
		}
		else if ((temp_code > 200) && (temp_loan_cnt >= 4))	//code is 300, 400
		{
			stree->Insert(temp->second);
			temp->second->setDel();
		}
		else if ((temp_code < 300) && (temp_loan_cnt >= 3))	//code is 000, 100, 200
		{
			stree->Insert(temp->second);
			temp->second->setDel();
		}
		return 1;
	}
	//creat new LoanBookData Node and add to bptree
	LoanBookData* newData = new LoanBookData();
	newData->setBookData(book_name, book_code, book_author, book_year);
	bptree->Insert(newData);
	flog << "========ADD========" << endl;
	flog << book_name << "/" << book_code << "/" << book_author << "/" << book_year << endl;
	flog << "===================" << endl << endl;
	return true;
}

bool Manager::SEARCH_BP_BOOK(string book) 
{
	BpTreeNode* pCur = bptree->searchDataNode(book);	//get book
	LoanBookData* sData = nullptr;
	if (pCur)
	{
		auto temp = pCur->getDataMap()->begin();
		if (book.compare(temp->first) == 0)	//found node
			sData = temp->second;
		else if (pCur->getDataMap()->size() == 2)
		{
			temp++;
			if (book.compare(temp->first) == 0)
				sData = temp->second;
		}
	}
	else
	{
		return 0;
	}

	if (!sData)
		return 0;

	flog << "========SEARCH_BP========" << endl;
	string bk = to_string(sData->getCode());
	if (bk == "0")
		bk = "000";
	flog << sData->getName() << "/" << sData->getCode() << "/" << sData->getAuthor() << "/" << sData->getYear() << "/" << sData->getLoanCount() << endl;
	flog << "=========================" << endl << endl;
	return 1;
}

bool Manager::SEARCH_BP_RANGE(string s, string e) 
{
	if (!bptree->getRoot())
		return 0;
	
	if (!bptree->searchRange(s, e))	//get book
		return 0;
	
	return 1;
}

bool Manager::PRINT_BP() 
{
	if (!bptree->getRoot())
		return 0;

	flog << "========PRINT_BP========" << endl;
	bptree->printAllDataNode();
	flog << "========================" << endl << endl;
	return 1;
}

bool Manager::PRINT_ST(int BookCode) 
{
	if (BookCode % 100 != 0)
		return 0;
	if (BookCode > 700 && BookCode < 0)
		return 0;
	// if (!stree->getRoot())
	// 	return 0;
	if (stree->printBookData(BookCode))
		return 1;
	return 0;
}

bool Manager::DELETE() 
{
	if (!stree->getRoot())
		return 0;
	if (stree->Delete())
		return 1;
	return 0;
}

void Manager::printErrorCode(int n) 
{				//ERROR CODE PRINT
	flog << "========ERROR========" << endl;
	flog << n << endl;
	flog << "=====================" << endl << endl;
	return;
}

void Manager::printSuccessCode(const char* suc_cmd) 
{//SUCCESS CODE PRINT 
	flog << "========" << suc_cmd << "========" << endl;
	flog << "Success" << endl;
	flog << "====================" << endl << endl;
	return;
}

