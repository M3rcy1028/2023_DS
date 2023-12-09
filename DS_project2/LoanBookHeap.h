#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"

class LoanBookHeap
{
private:
    LoanBookHeapNode* root;

public:
    LoanBookHeap() {
        this->root = NULL;
    }
    ~LoanBookHeap() {
        //delete root;
    }
    
    void setRoot(LoanBookHeapNode* pN) { this->root = pN; }
    LoanBookHeapNode* getRoot() { return root; }

    void heapifyUp(LoanBookHeapNode* pN);
    void heapifyDown(LoanBookHeapNode* pN);
    
    bool RemoveRoot();
    bool Insert(LoanBookData* data);
};
