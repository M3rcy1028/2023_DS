#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

//create new matrix graph
MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
    m_Mat = new int*[size];
    for (int i = 0; i < size; i++)
        m_Mat[i] = new int[size];
    //initialization
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            m_Mat[i][j] = 0;
    }
}

//destructor
MatrixGraph::~MatrixGraph()
{
    for (int i = 0; i < getSize(); i++)
        delete[] m_Mat[i];

    delete[] m_Mat;
}

//get undirected adjacent edges
void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{	
    int sz = getSize();
    //insert vertex values
    for (int i = 0; i < sz; i++)
    {
        int weight = m_Mat[vertex][i];
        if (weight != 0)
            m->insert({i + 1, weight});
    }
    //insert non-vertex values
    for (int j = 0; j < sz; j++)
    {
        int weight = m_Mat[j][vertex];
        if (weight != 0)
            m->insert({j + 1, weight});
    }
    return;
}

//get directed adjacent edges
void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)
{
	for (int i = 0; i < getSize(); i++)
    {
        int weight = m_Mat[vertex][i];
        if (weight != 0)
            m->insert({i + 1, weight});
    }
    return;
}

//inter edges
void MatrixGraph::insertEdge(int from, int to, int weight)	
{
	m_Mat[from - 1][to - 1] = weight;
    return;
}

//print matrix graph
bool MatrixGraph::printGraph(ofstream *fout)	
{
	(*fout) << "======== PRINT ========" << endl;
    for (int i = 0; i < getSize(); i++)
        (*fout) << "\t[ " << i + 1 << " ]";
    (*fout) << endl;
    for (int i = 0; i < getSize(); i++)
    {
        (*fout) << "[ " << i + 1 << " ]\t";
        for (int j = 0; j < getSize(); j++)
            (*fout) << m_Mat[i][j] << "\t";
        (*fout) << endl;
    }
    (*fout) << "=======================" << endl << endl;
    return 1;
}
