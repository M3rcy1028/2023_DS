#include "TermsBST.h"

TermsBST::TermsBST() : root(nullptr)
{

}
TermsBST::~TermsBST()
{
	delete root;
}

//return root
TermsBSTNode* TermsBST::getRoot()
{
	return root;
}
//set root
void TermsBST::setRoot(TermsBSTNode* node)
{
	root = node;
	return;
}

// insert TermsBSTNode
void TermsBST::insert(TermsBSTNode* NewNode)
{
	//if root is empty
	if (root == nullptr)
		root = NewNode;
	else //root is not empty
	{
		TermsBSTNode* Cur = root;

		while (Cur)	//find position for NewNode
		{
			if (strcmp(NewNode->GetExpiredDate(), Cur->GetExpiredDate()) < 0) //NewNode is smaller than Cur
			{
				//left node does not exist
				if (Cur->getLeft() == nullptr)
				{
					Cur->setLeft(NewNode);
					break;
				}
				Cur = Cur->getLeft();	//Move to Left
			}
			else //NewNode is greater than Cur
			{
				if (Cur->getRight() == nullptr)
				{
					Cur->setRight(NewNode);
					break;
				}
				Cur = Cur->getRight();	//Move to Right
			}
		} //while
		mem++;
	}
	return;
}

// print all BST member nodes
void TermsBST::print(TermsBSTNode* temp, ofstream& flog)
{
	if (temp == nullptr)
		return;
	if (root == nullptr)
		return;
	print(temp->getLeft(), flog);		//get left
	temp->print(flog);					//print information
	print(temp->getRight(), flog);		//get right
	return;
}

//search whether date exists or not
bool TermsBST::search_date(TermsBSTNode* root, const char* date, const char* name)
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

//search member with specific date infromation
bool TermsBST::search_date_v2(TermsBSTNode* root, const char* date)
{
	TermsBSTNode* cur = root;
	while (cur)
	{
		if (strncmp(cur->GetExpiredDate(), date, 8) < 0)
			return 1; //found
		else if (strncmp(cur->GetExpiredDate(), date, 8) >= 0)
			cur = cur->getLeft();

	} //while
	return 0; //not found
}

//delete date with specific name 
bool TermsBST::delete_date(const char* name, const char* date)
{
	TermsBSTNode* cur = root;
	TermsBSTNode* prev = nullptr;
	TermsBSTNode* prevprev = nullptr;

	if (cur == nullptr)	//if root is empty
		return 0;
	else
	{
		while (cur)
		{
			if (strncmp(cur->GetName(), name, strlen(cur->GetName())) == 0) //find node
			{
				if (cur == root)	//cur is root
				{
					root = nullptr;
					break;
				}
				//cur had no child
				else if (!cur->getLeft() && !cur->getRight())
				{
					if (prev->getLeft() == cur) //cur is left child
						prev->setLeft(nullptr);
					else //cur is right child
						prev->setRight(nullptr);
					delete cur;	//delete cur
				}
				//cur has both children
				else if (cur->getLeft() && cur->getRight())
				{
					TermsBSTNode* del = cur; //delete node
					TermsBSTNode* del_prev = prev; //delete prev node
					prev = cur;
					cur = cur->getRight(); //move to right
					while (cur) //move to the left until cur == nullptr
					{
						cur = cur->getLeft();
						prev = prev->getLeft();
						prevprev = prevprev->getLeft();
					} //while
					if (prev) //prev(= replace node) exists
					{
						if (del_prev->getLeft() == del) //if del is left node of del_prev
							del_prev->setLeft(prev);
						else //if del is right node of del_prev
							del_prev->setRight(prev);
						prev->setRight(del->getRight()); //set prev right node
						//set prev left node
						if (del->getLeft() != prev)
							prev->setLeft(del->getLeft());
						else
							prev->setLeft(nullptr);
						delete del;	//delete delete node
					}
				}
				//cur has one child
				else if (cur->getLeft() || cur->getRight())
				{
					if (cur->getLeft()) //cur has left child
						prevprev = cur->getLeft();
					else //cur has right child
						prevprev = cur->getRight();
					//set prev node
					if (prev->getLeft() == cur) //cur is left child
						prev->setLeft(prevprev);
					else //cur is right child
						prev->setRight(prevprev);
					delete cur; //delete cur
				}
				else //error
					return 0;

			}
			else if (strcmp(cur->GetExpiredDate(), date) >= 0)
			{	//if date is smaller than cur date, move to left
				prevprev = prev;
				prev = cur;
				cur = cur->getRight();
			}
		} //while
	} //root is not empty
	mem--;
	return 1;	//delete node is found
}

//delete date and return name
bool TermsBST::delete_date_v2(const char* date)
{
	TermsBSTNode* cur = root;
	TermsBSTNode* prev = nullptr;

	if (cur == nullptr)	//if root is empty
		return 0;
	else
	{
		while (cur)
		{
			if (strncmp(cur->GetExpiredDate(), date, 8) < 0) //find node
			{
				if (prev) //prev exists
				{
					prev->setLeft(cur->getRight());
					delete cur;
				}
				else //prev does not exist
				{
					root = root->getRight();
					delete cur;
				}
				return 1;
			}
			else
			{	
				prev = cur;
 				cur = cur->getLeft();
			}
		} //while
	} //root is not empty
	return 0;
}
