#include "BpTree.h"
#include <map>

// Insert an element to B+ Tree
bool BpTree::Insert(LoanBookData *newData)
{
	if (!root) // root is empty
	{
		root = new BpTreeDataNode();
		root->insertDataMap(newData->getName(), newData);
	}
	else // root is not empty
	{
		BpTreeNode *pCur = root;
		string new_name = newData->getName();
		while (pCur->getMostLeftChild() != NULL)
			pCur = pCur->getMostLeftChild();
		while (pCur->getPrev() != NULL)
			pCur = pCur->getPrev();
		while(1)
		{
			auto temp = pCur->getDataMap()->begin();
			if (temp->first.compare(new_name) > 0)
			{
				if (pCur->getPrev() != NULL)
					pCur = pCur->getPrev();
				break;
			}
			if (pCur->getNext() == NULL)
			{
				break;
			}
			pCur = pCur->getNext();
		}
		
		pCur->insertDataMap(new_name, newData);
		if (pCur->getDataMap()->size() > 2)	//data node size is over 2
		{
			splitDataNode(pCur);	//split data node
		}
	}
	return true;
}

bool BpTree::excessDataNode(BpTreeNode *pDataNode)
{
	if (pDataNode->getDataMap()->size() > order - 1)
		return true; // order is equal to the number of elements
	else
		return false;
}

bool BpTree::excessIndexNode(BpTreeNode *pIndexNode)
{
	if (pIndexNode->getIndexMap()->size() > order - 1)
		return true; // order is equal to the number of elements
	else
		return false;
}

//split data node function
void BpTree::splitDataNode(BpTreeNode *pDataNode)
{
	BpTreeNode* ParentIndexNode = pDataNode->getParent();	//get root
	BpTreeNode* NewLeftDataNode = new BpTreeDataNode();	//new MostLeftNode;
	auto temp = pDataNode->getDataMap()->begin();	//get first element
	//depart Left node
	NewLeftDataNode->insertDataMap(temp->first, temp->second);	//store first element's information
	pDataNode->deleteMap(temp->first);	//delete first element
	NewLeftDataNode->setNext(pDataNode);

	temp = pDataNode->getDataMap()->begin();	//get second element
	string parent_name = temp->first;

	if (!ParentIndexNode)	//if root is empty
	{
		//cout << "no parent(data node)" << endl;
		ParentIndexNode = new BpTreeIndexNode();	//allocate memory
		//set parent
		ParentIndexNode->insertIndexMap(parent_name, pDataNode);	//set new Index node
		NewLeftDataNode->setParent(ParentIndexNode);
		pDataNode->setParent(ParentIndexNode);
		ParentIndexNode->setMostLeftChild(NewLeftDataNode);	//set MostLeftNode

		//Link pointer each DataNode
		pDataNode->setPrev(NewLeftDataNode);

		root = ParentIndexNode;	//set root
		//cout << "splited left node's next first node name : " << NewLeftDataNode->getNext()->getDataMap()->begin()->first << endl;
		return;
	}

	//set parent 
	ParentIndexNode->insertIndexMap(parent_name, pDataNode);	//inset middle element to parent Index map
	//set child's parent
	NewLeftDataNode->setParent(ParentIndexNode);	
	pDataNode->setParent(ParentIndexNode);	//modified
	string left_name = NewLeftDataNode->getDataMap()->begin()->first;	//get Leftnode name
	auto parent_temp = ParentIndexNode->getIndexMap()->begin();	//get first parent

	if (ParentIndexNode->getIndexMap()->size() == 2)	//split node has one parent
	{
		if (left_name < parent_temp->first)	//case1: left 
		{
			//cout << "two parent, left split(data node)" << endl;
			ParentIndexNode->setMostLeftChild(NewLeftDataNode);	//set MostLeftChild
		}
		else	//case2: right
		{
			//cout << "two parent, right split(data node)" << endl;
			parent_temp->second = NewLeftDataNode;
		}
		// NewLeftDataNode->setNext(pDataNode);
		if (pDataNode->getPrev() != NULL)
		{
			NewLeftDataNode->setPrev(pDataNode->getPrev());
			pDataNode->getPrev()->setNext(NewLeftDataNode);
		}
		pDataNode->setPrev(NewLeftDataNode);
	}	
	else //if (ParentIndexNode->getIndexMap()->size() > 2)	//split node has two parent
	{	
		if (left_name < parent_temp->first)	//case1: left
		{
			//cout << "three parent, left split(data node)" << endl;
			ParentIndexNode->setMostLeftChild(NewLeftDataNode);	//set MostLeftChild
			//pDataNode->setPrev(NewLeftDataNode);
			//modified
			if (pDataNode->getPrev() != NULL)
			{
				NewLeftDataNode->setPrev(pDataNode->getPrev());
				pDataNode->getPrev()->setNext(NewLeftDataNode);
			}
			pDataNode->setPrev(NewLeftDataNode);
		}
		else
		{
			parent_temp++;	//move to second element
			if (left_name < parent_temp->first)	//middle
			{
				//cout << "three parent, middle split(data node)" << endl;
				parent_temp = ParentIndexNode->getIndexMap()->begin();	//get first parent
				parent_temp->second = NewLeftDataNode;
			}
			else
			{
				//cout << "three parent, right split(data node)" << endl;
				parent_temp->second = NewLeftDataNode;
			}
			NewLeftDataNode->setPrev(pDataNode->getPrev());
			NewLeftDataNode->getPrev()->setNext(NewLeftDataNode);
			pDataNode->setPrev(NewLeftDataNode);
		}
		//cout << "splited left node's next first node name : " << NewLeftDataNode->getNext()->getDataMap()->begin()->first << endl;
		splitIndexNode(ParentIndexNode);	//split parent node
		//cout << "split parent node (done.)" << endl;
	}
	return;
}

//split index node function
void BpTree::splitIndexNode(BpTreeNode *pIndexNode)
{
	BpTreeNode* ParentIndexNode = pIndexNode->getParent();	//get parent node
	BpTreeNode* NewLeftIndexNode = new BpTreeIndexNode();	//new MostLeftChild node
	auto temp = pIndexNode->getIndexMap()->begin();	//get first element

	//set Left node
	NewLeftIndexNode->insertIndexMap(temp->first, temp->second);	//store left child's information
	NewLeftIndexNode->setMostLeftChild(pIndexNode->getMostLeftChild());	//set MostLeftChild
	pIndexNode->deleteMap(temp->first);	//delete first element
	//set new parent node
	temp = pIndexNode->getIndexMap()->begin();	//get second element
	string parent_name = temp->first;
	pIndexNode->setMostLeftChild(temp->second);	//set right child's MostLeftChild
	pIndexNode->deleteMap(temp->first);	//delete second element
	temp = pIndexNode->getIndexMap()->begin();	//get third element

	if (!ParentIndexNode) //split node is root
	{
		//cout << "no parent (index node)" << endl;
		ParentIndexNode = new BpTreeIndexNode();	//allocate new parent node
		ParentIndexNode->insertIndexMap(parent_name, pIndexNode);	//add middle node to parent node
		ParentIndexNode->setMostLeftChild(NewLeftIndexNode);	//set parent's left child
		pIndexNode->setParent(ParentIndexNode);	//set right child's parent
		NewLeftIndexNode->setParent(ParentIndexNode);	//set left child's parent
		root = ParentIndexNode;	//set root node
		return;
	}
	//set parent
	ParentIndexNode->insertIndexMap(parent_name, pIndexNode);	//add middle node to parent node
	NewLeftIndexNode->setParent(ParentIndexNode);
	pIndexNode->setParent(ParentIndexNode);
	auto parent_temp = ParentIndexNode->getIndexMap()->begin();
	string left_name = NewLeftIndexNode->getIndexMap()->begin()->first;

	if (ParentIndexNode->getIndexMap()->size() == 2)	//split node is not root, has one parent
	{	
		if (left_name < parent_temp->first)	//case1: split left child
		{
			//cout << "two parent, left split (index node)" << endl;
			ParentIndexNode->setMostLeftChild(NewLeftIndexNode);	//set MostLeftChild
		}
		else	//case2: split right child, MostLeftChild exists
		{
			//cout << "two parent, right split (index node)" << endl;
			parent_temp->second = NewLeftIndexNode;	//set newLeftIndexNode to parent's middle child
		}
	}
	else //if (ParentIndexNode->getIndexMap()->size() > 2)	//split node has two parent
	{
		if (left_name < parent_temp->first)	//case1: left child
		{
			//cout << "three parent, left split (index node)" << endl;
			ParentIndexNode->setMostLeftChild(NewLeftIndexNode);	//set MostLeftNode
		}
		else
		{
			parent_temp++;	//move to second element
			if (left_name < parent_temp->first)	//case2: middle child
			{
				//cout << "three parent, middle split (index node)" << endl;
				parent_temp = ParentIndexNode->getIndexMap()->begin();	//move to first element
				parent_temp->second = NewLeftIndexNode;
			}
			else	//case3: right child
			{
				//cout << "three parent, right split (index node)" << endl;
				parent_temp->second = NewLeftIndexNode;
			}
		}
		splitIndexNode(ParentIndexNode);	//parent node has 3 elements
	}
	return;
}

//find specific name and return BpTreeNode
BpTreeNode *BpTree::searchDataNode(string name)
{
	if (!root)	//root is empty
		return nullptr;
	
	BpTreeNode* pCur = root;
	while(pCur->getMostLeftChild())	//until reach data node
	{	
		pCur = pCur->getMostLeftChild();
	}
	while (pCur->getPrev() != NULL)
		pCur = pCur->getPrev();
	while(pCur)	//until reach end of data node
	{
		auto temp = pCur->getDataMap()->begin();
		if (name.compare(temp->first) == 0)
		{
			return pCur;	//found
		}
		else if (pCur->getDataMap()->size() == 2)
		{
			temp++;
			if (name.compare(temp->first) == 0)	//found in second element
			{
				return pCur;
			}
		}
		pCur = pCur->getNext();
	}
	return nullptr;
}

void BpTree::printAllDataNode()
{
	BpTreeNode* pCur = root;
	while(pCur->getMostLeftChild())	//until reach data node
	{	
		pCur = pCur->getMostLeftChild();
	}
	while (pCur->getPrev() != NULL)
		pCur = pCur->getPrev();
	while(pCur)	//until reach end of data node
	{
		auto temp = pCur->getDataMap()->begin();
		string bk = to_string(temp->second->getCode());
        if (bk == "0")
            bk = "000";

		if (!temp->second->getDel())
			(*this->fout) << temp->second->getName() << "/" << bk << "/" << temp->second->getAuthor() << "/" << temp->second->getYear()<< "/" << temp->second->getLoanCount() << endl;
		if (pCur->getDataMap()->size() == 2)
		{
			temp++;
			bk = to_string(temp->second->getCode());
			if (bk == "0")
				bk = "000";
			if (!temp->second->getDel())
				(*this->fout) << temp->second->getName() << "/" << bk << "/" << temp->second->getAuthor() << "/" << temp->second->getYear()<< "/" << temp->second->getLoanCount() << endl;
		}
		pCur = pCur->getNext();
	}
	//fwrite.close();
}

bool BpTree::searchBook(string name)
{
	if (!root)	//root is empty
		return 0;
	
	BpTreeNode* pCur = root;
	while(pCur->getMostLeftChild())	//until reach data node
	{	
		pCur = pCur->getMostLeftChild();
	}
	while (pCur->getPrev() != NULL)
		pCur = pCur->getPrev();
	while(pCur)	//until reach end of data node
	{
		auto temp = pCur->getDataMap()->begin();
		if (temp->first == name)
		{
			if (temp->second->getDel())
				return 0;
			return 1;	//found
		}
		else if (pCur->getDataMap()->size() == 2)
		{
			temp++;
			//cout << ">>>>second name : " << temp->first << endl;
			if (temp->first == name)	//found in second element
			{
				if (temp->second->getDel())
					return 0;
				return 1;
			}
		}
		pCur = pCur->getNext();
	}
	return 0;
}

bool BpTree::searchRange(string start, string end)
{
	if (!root)
		return 0;
	BpTreeNode* pCur = root;
	while(pCur->getMostLeftChild())	//until reach data node
	{
		pCur = pCur->getMostLeftChild();
	}
	while (pCur->getPrev() != NULL)
		pCur = pCur->getPrev();
	//(*this->fout) << "========SEARCH_BP========" << endl;
	map<string, LoanBookData*> m;
	while(pCur)	//until reach end of data node
	{
		auto temp = pCur->getDataMap()->begin();
		string c_first = temp->first.substr(0, 1);
		if ((start.compare(c_first) <= 0) && (end.compare(c_first) >= 0))
		{
			string bk = to_string(temp->second->getCode());
			if (bk == "0")
				bk = "000";
			if (!temp->second->getDel())
				m.insert({temp->second->getName(), temp->second});
				//(*this->fout) << temp->second->getName() << "/" << bk << "/" << temp->second->getAuthor() << "/" << temp->second->getYear()<< "/" << temp->second->getLoanCount() << endl;
		}
		if (pCur->getDataMap()->size() == 2)
		{
			temp++;
			c_first = temp->first.substr(0, 1);
			if ((start.compare(c_first) <= 0) && (end.compare(c_first) >= 0))
			{
				string bk = to_string(temp->second->getCode());
				if (bk == "0")
					bk = "000";
				if (!temp->second->getDel())
					m.insert({temp->second->getName(), temp->second});
					//(*this->fout) << temp->second->getName() << "/" << bk << "/" << temp->second->getAuthor() << "/" << temp->second->getYear()<< "/" << temp->second->getLoanCount() << endl;
			}
		}
		if (end.compare(c_first) < 0)
			break;
		pCur = pCur->getNext();
	}
	int sz = m.size();
	auto ptr = m.begin();
	
	if (ptr == m.end()) return 0;

	(*this->fout) << "========SEARCH_BP========" << endl;
	for (int i = 0; i < sz; i++)
	{
		string bk = to_string(ptr->second->getCode());
		if (bk == "0")
			bk = "000";
		(*fout) << ptr->second->getName() << "/" << bk << "/" << ptr->second->getAuthor() << "/" << ptr->second->getYear() << "/" << ptr->second->getLoanCount() << endl;
		ptr++;
	}
	(*this->fout) << "=========================" << endl << endl;
	return 1;
}
