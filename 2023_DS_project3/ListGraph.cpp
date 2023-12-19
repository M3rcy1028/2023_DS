#include "ListGraph.h"
#include <iostream>
#include <utility>

//create new list graph
ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	m_List = new map<int, int>[size];
}

//destructor
ListGraph::~ListGraph()	
{
	delete[] m_List;
}

//get undirected adjacent edges
void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)	 //Definition of getAdjacentEdges(No Direction == Undirected)
{
    //insert vertex values
    for (auto temp = m_List[vertex].begin(); temp != m_List[vertex].end(); temp++)
        m->insert({temp->first, temp->second}); 
    //insert non-vertex values
    for (int i = 0; i < getSize(); i++)
    {
        if (i == vertex)
            continue;
        for (auto temp = m_List[i].begin(); temp != m_List[i].end(); temp++)
        {
            if (temp->first == vertex + 1)
                m->insert({i + 1, temp->second});
        }
    }
    return;
}

//get directed adjacent edges
void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)	//Definition of getAdjacentEdges(Directed graph)
{
	for (auto temp = m_List[vertex].begin(); temp != m_List[vertex].end(); temp++)
        m->insert({temp->first, temp->second}); 
    return;
}

//insert edges
void ListGraph::insertEdge(int from, int to, int weight) //Definition of insertEdge
{
	m_List[from - 1].insert({to, weight});
    return;
}

//print list graph
bool ListGraph::printGraph(ofstream *fout)	//Definition of print Graph
{
	(*fout) << "======== PRINT ========" << endl;
    for (int i = 0; i < getSize(); i++)
    {
        (*fout) << "[ " << i + 1 << " ]";
        int size = m_List[i].size();
        for (auto temp = m_List[i].begin(); temp != m_List[i].end(); temp++)
            (*fout) << "-> (" << temp->first << "," << temp->second << ") ";
        (*fout) << endl;
    }
    (*fout) << "=======================" << endl << endl;
    return 1;
}