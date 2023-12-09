#include "LoanBookHeap.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) 
{
    LoanBookData* temp = pN->getBookData();
    //swap information (position)
    pN->setBookData(pN->getParent()->getBookData());
    pN->getParent()->setBookData(temp);

    while (pN->getParent()->getParent())
    {
        string p_name = pN->getParent()->getBookData()->getName();
        string pp_name = pN->getParent()->getParent()->getBookData()->getName();

        if (p_name < pp_name)   //sorting again
            heapifyUp(pN->getParent());
        pN = pN->getParent();
    }

    return;
}

void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN)
{
    LoanBookData* temp = pN->getBookData();
    
    //swap information (position)
    pN->setBookData(pN->getParent()->getBookData());
    pN->getParent()->setBookData(temp);

    return;
}

bool LoanBookHeap::RemoveRoot()
{
    if (!root)  //root is empty
    {
        return 0;
    }
    if (!root->getLeftChild() && !root->getRightChild()) //only root node exists
    {
        root->setBookData(NULL);
        root = NULL;
        return 1;
    }
    else
    {
        root->setBookData(NULL); //remove root data
        LoanBookHeapNode* pCur = root;
        int i = 0;
        while (pCur)
        {
            if (pCur->getRightChild())  //if right child is not empty
            {
                pCur = pCur->getRightChild();
                i = 0;
            }
            else if (pCur->getLeftChild())  //if left child is not empty
            {
                pCur = pCur->getLeftChild();
                i = 1;
            }
            else    //reach leaf node
                break;
        }
        //disconnect link
        if (i)
            pCur->getParent()->setLeftChild(NULL);
        else
            pCur->getParent()->setRightChild(NULL);
        //root->setBookData(NULL);
        root->setBookData(pCur->getBookData());
        delete pCur;    //remove data

        pCur = root;
        while (pCur)
        {
            string root_name = pCur->getBookData()->getName();
            string right_name, left_name;

            if (pCur->getRightChild() && pCur->getLeftChild()) //both child
            {
                right_name = pCur->getRightChild()->getBookData()->getName();
                left_name = pCur->getLeftChild()->getBookData()->getName();
                if ((right_name < root_name) && (left_name > right_name))   //exhange with right child
                {
                    heapifyUp(pCur->getRightChild());
                    pCur = pCur->getRightChild();
                }
                else if ((left_name < root_name) && (left_name < right_name))  //exchange with left child
                {
                    heapifyUp(pCur->getLeftChild());
                    pCur = pCur->getLeftChild();
                }
                else
                    break;
            }
            else if (!pCur->getRightChild() && pCur->getLeftChild()) //only left child
            {
                left_name = pCur->getLeftChild()->getBookData()->getName();
                if (root_name > left_name)
                {
                    heapifyUp(pCur->getLeftChild());
                    pCur = pCur->getLeftChild();
                }
                else    //no more resorting
                    break;
            }
            else    //no child
                break;
        }
    }
    return 1;
}

bool LoanBookHeap::Insert(LoanBookData* data) 
{
    LoanBookHeapNode* pCur = root;
    if (pCur == NULL)  //root is empty
    {
        pCur = new LoanBookHeapNode();
        pCur->setBookData(data);
        root = pCur;
        return 1;
    }
    else    //root is not empty
    {
        //new node
        LoanBookHeapNode* newChild = new LoanBookHeapNode();
        newChild->setBookData(data);
        while (pCur)
        {
            if (pCur->getLeftChild() == NULL)   //has no left child
            {
                newChild->setParent(pCur);
                pCur->setLeftChild(newChild);   //set left child
                if (pCur->getBookData()->getName() > data->getName())   //parent node is larger than data
                    heapifyUp(newChild);
                return 1;
            }
            else if (pCur->getRightChild() == NULL)    //has no right child
            {
                newChild->setParent(pCur);
                pCur->setRightChild(newChild);   //set left child
                if (pCur->getBookData()->getName() > data->getName())   //parent node is larger than data
                    heapifyUp(newChild);
                return 1;
            }
            //has both child
            if (pCur->getLeftChild()->getLeftChild() && pCur->getLeftChild()->getRightChild())  //left child node is full
            {
                if (pCur->getRightChild()->getLeftChild() && pCur->getRightChild()->getRightChild())    //right child node is full
                    pCur = pCur->getLeftChild();
                else    //right child node is not full
                    pCur = pCur->getRightChild();
            }
            else   //left child node is not full
                pCur = pCur->getLeftChild(); 
        }
    }
    return 0;
}
