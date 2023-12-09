#pragma once
#include "SelectionTreeNode.h"

#include <fstream>
#include <iostream>

class SelectionTree
{
private:
    SelectionTreeNode* root;
    ofstream* fout;
    SelectionTreeNode* streeArr[14];

public:
    SelectionTree(ofstream* fout) 
    {
        this->root = NULL;
        this->fout = fout;

        for (int i = 0; i < 15; i++)
        {
            streeArr[i] = new SelectionTreeNode();
            streeArr[i]->setBookData(NULL);
        }
        for (int i = 0; i < 15; i++)
        {
            if (i != 0) //index 0 is root
            {   //set parent node
                if (i % 2 == 0) //right child
                    streeArr[i]->setParent(streeArr[i % 2 - 1]);    //set parent
                else    //left child
                    streeArr[i]->setParent(streeArr[i % 2]);    //set parent
            }
            if (i < 7)  //not a leaf node
            {   //set child
                streeArr[i]->setLeftChild(streeArr[i * 2 + 1]);
                streeArr[i]->setRightChild(streeArr[i * 2 + 2]);
            }
        }
        root = streeArr[0];
    }
    
    ~SelectionTree() 
    {
        for (int i = 0; i < 15; i++)
        {
            delete streeArr[i];
        }
    }

    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    //add to selection tree
    bool Insert(LoanBookData* newData);
    //delete root
    bool Delete();
    void DeleteRoot();
    //print abc
    bool printBookData(int bookCode);
};