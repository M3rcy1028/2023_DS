#include "NameBST.h"

NameBST::NameBST() : root(nullptr)
{

}
NameBST::~NameBST()
{
	delete root;
}

NameBSTNode* NameBST::getRoot()
{
	return root;
}

// insert NameBSTNode
void NameBST::insert(NameBSTNode* NewNode)
{
	if (root == nullptr) //if root is empty
		root = NewNode;
	else //root is not empty
	{
		NameBSTNode* cur = root;
		while (cur)
		{
			if (strcmp(NewNode->GetName(), cur->GetName()) < 0) //left node
			{
				if (cur->getLeft() == nullptr) //if left node is empty
				{
					cur->setLeft(NewNode);	//set left node
					break;
				}
				cur = cur->getLeft(); //move to left node
			}
			else //right node
			{
				if (cur->getRight() == nullptr) //if right node is empty
				{
					cur->setRight(NewNode);	//set right node
					break;
				}
				cur = cur->getRight(); //move to right node
			}
		} //while
	} //else
	return;
}

// search specific name
bool NameBST::search(const char* find, ofstream& flog)
{
	NameBSTNode* cur = root;
	bool flag = 0;
	while (cur)
	{
		if (strcmp(cur->GetName(), find) == 0)	//name found
		{
			flag = 1;
			flog << "===== SEARCH =====" << endl;
			cur->print(flog);
			flog << "===============" << endl << endl;;
			return flag;
		}
		else if (strcmp(find, cur->GetName()) < 0)
			cur = cur->getLeft();	//move to left
		else if (strcmp(find, cur->GetName()) >= 0)
			cur = cur->getRight();	//move to right
		else //error
			return 0;
	}
	return flag;
}

// print all nodes in NameBST
void NameBST::print(NameBSTNode* temp, ofstream& flog)
{
	if (temp == nullptr)
		return;
	print(temp->getLeft(), flog);		//get left
	temp->print(flog);					//print information
	print(temp->getRight(), flog);		//get right
	return;
}

// delete specific name
char* NameBST::delete_name(const char* find)
{
	NameBSTNode* cur = root;
	NameBSTNode* prev = nullptr;
	NameBSTNode* prevprev = nullptr;

	if (cur == nullptr)	//if root is empty
		return 0;
	else
	{
		while (cur)
		{
			if (strcmp(cur->GetName(), find) == 0) //find node
			{
				//cur had no child
				if (!cur->getLeft() && !cur->getRight())
				{
					if (prev->getLeft() == cur) //cur is left child
						prev->setLeft(nullptr);
					else //cur is right child
						prev->setRight(nullptr);
					strcpy(return_date, cur->GetExpiredDate());
					delete cur;	//delete cur
				}
				//cur has both children
				else if (cur->getLeft() && cur->getRight())
				{
					NameBSTNode* del = cur; //delete node
					NameBSTNode* del_prev = prev; //delete prev node
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
						strcpy(return_date, del->GetExpiredDate());
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
					strcpy(return_date, cur->GetExpiredDate());
					delete cur; //delete cur
				}
				else //error
					return nullptr;

			}
			else if (strcmp(cur->GetName(), find) >= 0)
			{	//if find is smaller than cur name, move to left
				prevprev = prev;
				prev = cur;
				cur = cur->getLeft();
			}
			else if (strcmp(cur->GetName(), find) < 0)
			{	//if find is greater than cur name, move to right
				prevprev = prev;
				prev = cur;
				cur = cur->getRight();
			}
		} //while
	} //root is not empty
	return return_date;	//delete node is not found
}

//delete name with sepcific date
bool NameBST::delete_name_v2(NameBSTNode* ptr, NameBSTNode* ptr_prev, const char* date)
{
	if (!ptr)
	{
		return 0;
	}
	delete_name_v2(ptr->getLeft(), ptr, date);
	delete_name_v2(ptr->getRight(), ptr, date);
	if (strcmp(ptr->GetExpiredDate(), date) < 0)
	{
		if (ptr_prev == nullptr) //ptr is root
		{
			//root has no chile
			if (!ptr->getLeft() && !ptr->getRight())
			{
				delete ptr;
			}
			else if (!ptr->getLeft() && ptr->getRight()) //has only right child
			{
				root = ptr->getRight();
				delete ptr;
			}
			else if (ptr->getLeft() && !ptr->getRight()) //has only left child
			{
				root = ptr->getLeft();
				delete ptr;
			}
			else //has both children
			{
				NameBSTNode* prevprev = root;
				ptr_prev = root->getRight();
				ptr = ptr_prev->getLeft();

				while (ptr) //Move to left
				{
					prevprev = ptr_prev;
					ptr_prev = ptr;
					ptr = ptr->getLeft();
				} //while

				if (prevprev == root) //prevprev is root
				{
					root = ptr_prev; //set new root
					delete prevprev; //delete root
				}
				else //prevprev is not root
				{
					prevprev->setLeft(ptr_prev->getRight());
					ptr_prev->setLeft(root->getLeft());
					ptr_prev->setRight(root->getRight());
					delete root;	//delete node
					root = ptr_prev; //set new root
				}
			}
		}
		else //ptr is not root
		{
			NameBSTNode* del = ptr; //delete node
			NameBSTNode* del_prev = ptr_prev; //delete node
			NameBSTNode* prevprev = ptr_prev;
			ptr_prev = ptr;
			ptr = ptr->getRight();

			while (ptr) //move to left
			{
				prevprev = ptr_prev;
				ptr_prev = ptr;
				ptr = ptr->getLeft();
			} //while

			if (del == del_prev->getLeft()) //del is left node
				del_prev->setLeft(ptr_prev);
			else //del is left node
				del_prev->setRight(ptr_prev);

			if (ptr_prev == prevprev->getLeft()) //ptr_prev is left node
				prevprev->setLeft(nullptr);
			else //ptr_prev is left node
				prevprev->setRight(nullptr);

			ptr_prev->setLeft(del->getLeft());
			ptr_prev->setRight(del->getRight());
			delete del;
		}
	}
	return 1;
}
