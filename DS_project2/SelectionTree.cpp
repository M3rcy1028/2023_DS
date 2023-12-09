#include "SelectionTree.h"
#include <queue>
#include <map>
#include <algorithm>

bool SelectionTree::Insert(LoanBookData* newData) 
{
    int index = (newData->getCode() / 100) + 7;    //0 ~ 7

    auto temp = streeArr[index]->getHeap();
    temp->Insert(newData);  //insert to laon book heap
    //add to run
    streeArr[index]->setBookData(temp->getRoot()->getBookData());    //update inforation
    //cout << "streeArr[" << (index - 7) * 100 << "] root is : " << streeArr[index]->getBookData()->getName() << endl;
    //resort selection tree 
    int parent_index, cmp_index;
    string cmp_name;
    string new_name = newData->getName();
    auto pCur = streeArr[index];
    //update selection tree
    while (pCur && (index != 0))
    {
        if (index % 2 == 0)  //index number is even, compare with left child
        {
            cmp_index = index - 1;
            parent_index = index / 2 - 1;  //get next index
        }
        else    //odd, compare with right child
        {
            cmp_index = index + 1;
            parent_index = index / 2;  //get next index
        }
        if (streeArr[cmp_index]->getBookData() != NULL)    //sibling node is not empty
        {
            cmp_name = streeArr[cmp_index]->getBookData()->getName();   //get name
            //compare name
            if (cmp_name < new_name)
                streeArr[parent_index]->setBookData(streeArr[cmp_index]->getBookData());
            else
                streeArr[parent_index]->setBookData(streeArr[index]->getBookData());
        }
        else    //sibling node is empty   //set parent node
        {
            streeArr[parent_index]->setBookData(streeArr[index]->getBookData());
        }
        //move to next node
        pCur = streeArr[parent_index];
        index = parent_index;
    }
    root = streeArr[0];
   return 1;
}

bool SelectionTree::Delete() 
{
    if (!root)
        return 0;
    // if (root->getBookData() == NULL)  //root is empty
    // {
    //     root->setBookData(NULL);
    //     delete root;
    // }
    if (!root->getLeftChild() && !root->getRightChild())
    {
        root->setBookData(NULL);
        delete root;
    }
    else    //root is not empty
    {
        string root_name = root->getBookData()->getName();
        // cout << "14th name : " << streeArr[14]->getBookData()->getName() << endl;
        SelectionTreeNode* pCur = root;
        int index = 0;
        
        while (pCur->getLeftChild())
        {
            if (pCur->getLeftChild()->getBookData() != NULL)    //move to left child
            {   
                if (pCur->getLeftChild()->getBookData()->getName() == root_name)
                {
                    pCur->setBookData(NULL);
                    pCur = pCur->getLeftChild();   //move to left
                    index = index * 2 + 1;
                }
                else   //move to right child
                {
                    pCur->setBookData(NULL);
                    pCur = pCur->getRightChild();  //move to right
                    index = (index + 1) * 2;
                }
            }
            else   //move to right child
            {
                pCur->setBookData(NULL);
                pCur = pCur->getRightChild();  //move to right
                index = (index + 1) * 2;
            }
        }
        streeArr[index]->getHeap()->RemoveRoot();  //resorting heap
        if (streeArr[index]->getHeap()->getRoot())
            streeArr[index]->setBookData(streeArr[index]->getHeap()->getRoot()->getBookData()); //set new information
        else
            streeArr[index]->setBookData(NULL);
        //tournament again
        index = 7;  //left node index
        int empty = 7;
        for (int i = 0; i < 8; i++)
        {
            if (streeArr[i + 7]->getHeap()->getRoot())
                empty -= 1;
        }
        if (empty == 7)
        {
            (*this->fout) << "========DELETE========" << endl;
            (*this->fout) << "Success" << endl;
            (*this->fout) << "======================" << endl << endl;
            root->setBookData(NULL);
            root = NULL;
            return 1;
        }
        while (1)
        {
            if (!streeArr[index]->getBookData() && !streeArr[index + 1]->getBookData())  //left and right node is empty
            {
                index += 2;
            } 
            else if (streeArr[index]->getBookData() && !streeArr[index + 1]->getBookData())    //right node is empty
            {
                streeArr[index / 2]->setBookData(streeArr[index]->getBookData());
                index += 2;
            }
            else if (!streeArr[index]->getBookData() && streeArr[index + 1]->getBookData())   //left node is empty
            {
                streeArr[index / 2]->setBookData(streeArr[index + 1]->getBookData());
                index += 2;
            }
            else    //both nodes are not empty
            {
                if (streeArr[index]->getBookData()->getName() > streeArr[index + 1]->getBookData()->getName())  //left node is larger
                    streeArr[index / 2]->setBookData(streeArr[index + 1]->getBookData());
                else    //right node is larger
                    streeArr[index / 2]->setBookData(streeArr[index]->getBookData());
                index += 2;
            }
            
            //set index
            if (index == 15) //move to level 3
                index = 3;
            else if (index == 7 )    //move to level 2
                index = 1;
            else if (index - 3 == 0)
                break;
        }
    }
    root = streeArr[0];
    //cout << "selection tree root : " << root->getBookData()->getName() << endl;
    (*this->fout) << "========DELETE========" << endl;
	(*this->fout) << "Success" << endl;
	(*this->fout) << "======================" << endl << endl;
    return 1;
}

//print heap with specific book code
bool SelectionTree::printBookData(int bookCode) 
{
    //cout << "selection tree :: printBookData " << bookCode << endl;
    if (!root)
    {
        //cout << "selection tree root is empty" << endl;
        return 0;
    } 
    if (!root->getBookData())
    {
        //cout << "selection tree root data is empty" << endl;
        return 0;
    }
    int idex = (bookCode / 100) + 7;
    
    if (streeArr[idex]->getHeap()->getRoot() == NULL)   //heap is empty
    {
        //cout << bookCode << " index heap root is empty" << endl;
        return 0;
    }
    else
    {
        auto temp = streeArr[idex]->getHeap()->getRoot();
        //cout << "print [" << bookCode << "] and root is : " << temp->getBookData()->getName() << endl;
        map<string, LoanBookData*> m;
        queue<LoanBookHeapNode*> q;    //queue vector
        q.push(temp);   //insert root
        m.insert({temp->getBookData()->getName(), temp->getBookData()});
        LoanBookHeapNode* pCur;
        //level traversal
        while (!q.empty())
        {
            pCur = q.front();    //get first element
            q.pop();    //remove first element 
            if (pCur->getLeftChild())   //left child exists
            {
                m.insert({pCur->getLeftChild()->getBookData()->getName(), pCur->getLeftChild()->getBookData()});
                q.push(pCur->getLeftChild());
            }
            if (pCur->getRightChild()) //right child exists
            {
                m.insert({pCur->getRightChild()->getBookData()->getName(), pCur->getRightChild()->getBookData()});
                q.push(pCur->getRightChild());
            }
        }
        //print sorted information
        int sz = m.size();
        auto ptr = m.begin();
        string bk = to_string(bookCode);
        if (bookCode == 0)
            bk = "000";
        (*fout) << "========PRINT_ST========" << endl;
        for (int i = 0; i < sz; i++)
        {
            (*fout) << ptr->second->getName() << "/" << bk << "/" << ptr->second->getAuthor() << "/" << ptr->second->getYear() << "/" << ptr->second->getLoanCount() << endl;
            ptr++;
        }
        (*fout) << "========================" << endl << endl;
        return 1;
    }
    return 0;
}
