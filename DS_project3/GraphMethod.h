#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"

struct Kru
{
    int from;
    int to;
    int weight;
};

//used for Kruskal algorithm
void SimpleUnion (int* parent, int i, int j);
int SimpleFind(int* parent, int i);
int partition(vector<Kru>* v, int low, int high);
void InsertionSort(vector<Kru>* v, int low, int high);
void QuickSort(vector<Kru>* v, int low, int high);

//used for kwangwoon algorithm
int init(int s, int e, int n, int* tree);
int sum(int s, int e, int n, int l, int r, int* tree);
void update(int s, int e, int n, int idx, int v, int* tree);

bool BFS(Graph* graph, char option, int vertex, ofstream *fout);     
bool DFS(Graph* graph, char option,  int vertex, ofstream *fout);     
bool KWANGWOON(Graph* graph, int vertex, ofstream *fout);  
bool Kruskal(Graph* graph, ofstream *fout);
bool Dijkstra(Graph* graph, char option, int vertex, ofstream *fout);    //Dijkstra
bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex, ofstream *fout); //Bellman - Ford
bool FLOYD(Graph* graph, char option, ofstream *fout);   //FLoyd

#endif
