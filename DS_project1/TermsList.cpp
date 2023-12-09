#include "TermsList.h"

TermsLIST::TermsLIST() : head(nullptr)
{
	
}
TermsLIST::~TermsLIST()
{
	TermsListNode* cur = head;
	while(head)
	{
		cur = head->getNext();
		delete head;
		head = cur;
	} //delete memory
}

//get head node
TermsListNode* TermsLIST::getHead()
{
	return head;
}

// insert TermsBSTNode to TermsList
void TermsLIST::insert(TermsBSTNode* NewNode)
{
	char ch = NewNode->GetContract(); //get contract
	if (head) //if head exists
	{
		TermsListNode* cur = head, *prev = nullptr;
		while (cur)
		{
			if (cur->GetContract() != ch) //compare contract
			{
				prev = cur; //store current node
				cur = cur->getNext(); //move to next node
			}
			else
				break;
		}//while
		if (!cur) //not found
		{ 
			TermsListNode* NewListNode = new TermsListNode(); //create new list node
			prev->setNext(NewListNode); //set linked list
			NewListNode->setContract(ch); //set contract
			NewListNode->incNodeCnt(); //increase the number of members
			TermsBST* temp = new TermsBST(); //create new BST node
			NewListNode->setBST(temp); //set BST root
			NewListNode->getBST()->setRoot(NewNode); //set NewNode
		}
		else //found
		{
			cur->getBST()->insert(NewNode);
			cur->incNodeCnt();
		}
	}
	else { //no head
		head = new TermsListNode();
		
		TermsBST* p = new TermsBST();
		head->setBST(p);
		head->getBST()->setRoot(NewNode);
		head->setContract(ch);
		head->incNodeCnt();
	}
	return;
}

//print all nodes
bool TermsLIST::print(char contract, ofstream& flog)
{
	TermsListNode* cur = head;
	bool flag = 0;
	while (cur != nullptr)
	{
		if (cur->GetContract() == contract)
		{
			flag = 1;
			flog << "===== PRINT =====" << endl;
			flog << "Terms_BST " << contract << endl;
			cur->print(flog);
			flog << "=================" << endl << endl;
			break;
		}
		cur = cur->getNext();
	}
	return flag;
}

//search specific date
bool TermsLIST::search_date(const char* name, const char* date)
{
	if (head) //if head exists
	{
		TermsListNode* cur = head, * prev = nullptr;
		while (cur)
		{
			if (cur->getBST()->search_date(cur->getBST()->getRoot(), date, name)) //name found
			{
				cur->getBST()->delete_date(name, date);
				return 1;
			}
			else //name not found
				cur = cur->getNext();
		}
	}
	else  //no head
		return 0;

	return 0; //not found
}


//search whether date exists or not
bool TermsLIST::search_date_v2(TermsBSTNode* root, const char* date, const char* name)
{
	TermsBSTNode* cur = root;
	while (cur)
	{
		if (strncmp(cur->GetExpiredDate(), date, 8) < 0)
			cur = cur->getRight();
		else if (strncmp(cur->GetExpiredDate(), date, 8) > 0)
			cur = cur->getLeft();
		else if (strncmp(cur->GetExpiredDate(), date, 8) == 0)
		{
			if (strncmp(cur->GetName(), name, strlen(cur->GetName())) == 0)
			{
				return 1; //found
			}
			return 0;
		}

	} //while
	return 0; //not found
}

//delete node with specific name and date
bool TermsLIST::delete_date(const char* name, const char* date)
{
	TermsListNode* cur = head;
	TermsListNode* prev = cur;
	while (cur)
	{
		TermsBST* temp = cur->getBST();
		if (temp->search_date(temp->getRoot(), date, name))
		{
			if (!temp->delete_date(name, date)) //fail
				return 0;
			else  //success
			{
				cur->decNodeCnt();
				if (cur->getNodeCnt() == 0) //TermsListNode is empty
				{
					if (cur == head) //if cur == head
					{
						head = head->getNext();
						delete cur;
					}
					else //cur is not head
					{
						prev->setNext(cur->getNext());
						delete cur;
					}
				}
				return 1;
			}
		}
		prev = cur;
		cur = cur->getNext();
	} //while
	return 0;
}

//delete date with specific date
bool TermsLIST::delete_date_v2(const char* date)
{
	TermsListNode* cur = head;
	TermsListNode* prev = cur;

	while (cur)
	{
		TermsBST* temp = cur->getBST();
		if (temp->search_date_v2(temp->getRoot(), date)) //found delete node
		{
			if (temp->delete_date_v2(date)); //delete success
			{
				cur->decNodeCnt();
				if (cur->getBST()->getRoot() == nullptr)
				{
					if (cur == head) //if cur == head
					{
						head = head->getNext();
						delete cur;
					}
					else //cur is not head
					{
						prev->setNext(cur->getNext());
						delete cur;
					}
					return 1;
				}
			}
		}
		prev = cur;
		cur = cur->getNext();
	} //while
	return 0;
}
