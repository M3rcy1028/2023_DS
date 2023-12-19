#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>
#include <algorithm>

using namespace std;
#define INF 1500000000

//Breadth First Search
bool BFS(Graph* graph, char option, int vertex, ofstream *fout)
{
    int sz = graph->getSize();
    bool* visited = new bool[sz];
    memset(visited, false, sz);
    visited[vertex - 1] = true;
    queue <int> mQueue;
    mQueue.push(vertex - 1);
    int v;
    map <int, int>* m = new map<int, int>[sz];
    vector <int> route;
    //directed
   if (option == 'Y')
   {
        while(!mQueue.empty()) //while queue is not empty
        {
            v = mQueue.front();
            route.push_back(v);
            mQueue.pop();
            graph->getAdjacentEdgesDirect(v, m + v);  //copy map

            for (auto temp = m[v].begin(); temp != m[v].end(); temp++)
            {
                int tar = temp->first - 1;
                if (!visited[tar])  //not visitied
                {
                    mQueue.push(tar);
                    visited[tar] = true;
                }
            }
        } //while
   }
   //undirected
   else
   {
        while(!mQueue.empty()) //while queue is not empty
        {
            v = mQueue.front();
            route.push_back(v);
            mQueue.pop();
            graph->getAdjacentEdges(v, m + v);  //copy map

            for (auto temp = m[v].begin(); temp != m[v].end(); temp++)
            {
                int tar = temp->first - 1;
                if (!visited[tar])  //not visitied
                {
                    mQueue.push(tar);
                    visited[tar] = true;
                }
            }
        } //while
    }
    delete[] visited;
    delete[] m;
    sz = route.size();
    (*fout) << "======== BFS ========" << endl;
    if (option == 'Y')
        (*fout) << "Directed Graph BFS result" << endl;
    else
        (*fout) << "Undirected Graph BFS result" << endl;
    (*fout) << "startvertex: " << vertex << endl << vertex;
    for (int i = 1; i < sz; i++)
       (*fout) << " -> " << route[i] + 1;
    (*fout) << endl << "=====================" << endl << endl;
    return 1;
}

//Depth First Search
bool DFS(Graph* graph, char option, int vertex, ofstream *fout)
{
    int sz = graph->getSize();
    bool* visited = new bool[sz];
    memset(visited, false, sz);
    visited[vertex - 1] = true;
    stack <int> mStack;
    mStack.push(vertex - 1);
    int v;
    map <int, int>* m = new map<int, int>[sz];
    vector <int> route;
    route.push_back(v);
    //directed
   if (option == 'Y')
   {
        while(!mStack.empty()) //while queue is not empty
        {
            v = mStack.top();
            mStack.pop();
            graph->getAdjacentEdgesDirect(v, m + v);  //copy map

            for (auto temp = m[v].begin(); temp != m[v].end(); temp++)
            {
                int tar = temp->first - 1;
                if (!visited[tar])  //not visitied
                {
                    mStack.push(v);
                    mStack.push(tar);
                    route.push_back(tar);
                    visited[tar] = true;
                    break;
                }
            }
        } //while
   }
   //undirected
   else
   {
        while(!mStack.empty()) //while queue is not empty
        {
            v = mStack.top();
            mStack.pop();
            graph->getAdjacentEdges(v, m + v);  //copy map

            for (auto temp = m[v].begin(); temp != m[v].end(); temp++)
            {
                int tar = temp->first - 1;
                if (!visited[tar])  //not visitied
                {
                    mStack.push(v);
                    mStack.push(tar);
                    route.push_back(tar);
                    visited[tar] = true;
                    break;
                }
            }
        } //while
    }
    delete[] visited;
    delete[] m;
    sz = route.size();
    (*fout) << "======== DFS ========" << endl;
    if (option == 'Y')
        (*fout) << "Directed Graph BFS result" << endl;
    else
        (*fout) << "Undirected Graph BFS result" << endl;
    (*fout) << "startvertex: " << vertex << endl << vertex;
    for (int i = 1; i < sz; i++)
       (*fout) << " -> " << route[i] + 1;
    (*fout) << endl << "=====================" << endl << endl;
    return 1;
}

//Kruskal Search
bool Kruskal(Graph* graph, ofstream *fout)
{
    //cout << endl << "Kruskal" << endl;
    int sz = graph->getSize();
    int* parent = new int[sz + 1];
    memset(parent, -1, sizeof(int)* (sz + 1));
    map <int, int>* m = new map<int, int>[sz];
    //get all vertex and weight information
    for (int i = 0; i < sz; i++)
        graph->getAdjacentEdges(i, m + i);
    //make struct vector
    vector <Kru>* v = new vector<Kru>;
    int edge = 0;
    for (int i = 0; i < sz; i++)
    {
        for (auto temp = m[i].begin(); temp != m[i].end(); temp++)
        {
            Kru newKru = {i + 1, temp->first, temp->second};
            v->push_back(newKru);
            edge++;
        }
    }
    QuickSort(v, 0, v->size() - 1);
    //cout << "end sorting" << endl;
    sz = graph->getSize();
    int cost = 0;
    map <int, int>* route = new map<int, int>[sz]; //store route
    //find and union parent
    int cnt = 0;
    for (int i = 0; i < edge; i++)
    {
        int p1 = SimpleFind(parent, v->at(i).from);
        int p2 = SimpleFind(parent, v->at(i).to);
        if (p1 != p2)
        {
            SimpleUnion(parent, p1, p2);
            route[v->at(i).from - 1].insert({v->at(i).to, v->at(i).weight});
            route[v->at(i).to - 1].insert({v->at(i).from, v->at(i).weight});
            cost += v->at(i).weight;
            cnt++;
            if (--sz == 1) break;
        }
    }
    bool success = false;
    if (cnt == graph->getSize() - 1) success = true;
    //print result
    if (success) 
    {
        sz = graph->getSize();
        (*fout) << "======== Kruskal ========" << endl;
        for (int i = 0; i < sz; i++)
        {
            (*fout) << "[ " << i + 1 << " ]\t";
            for (auto temp = route[i].begin(); temp != route[i].end(); temp++)
                (*fout) << temp->first << "(" << temp->second << ") ";
            (*fout) << endl;
        }
        (*fout) << "cost: " << cost << endl;
        (*fout) << "=========================" << endl << endl;
    }
    //delete memory
    delete[] parent;
    delete[] route;
    delete v;
    delete[] m;
    return success;
}

//find parent
void SimpleUnion (int* parent, int i, int j)
{
    parent[i] = j;
}

//find parent
int SimpleFind(int* parent, int i)
{
    //parent root is -1
    while (parent[i] >= 0)
    {
        i = parent[i];
    }
    return i;
}

//Insertion sorting
void InsertionSort(vector<Kru>* v, int low, int high)
{
    for (int i = low + 1; i <= high; i++)
    {
        int j = i - 1;
        Kru e = v->at(i);
        while (j >= low && e.weight < v->at(j).weight)
        {
            v->at(j + 1) = v->at(j);
            j--;
        }
        v->at(j + 1) = e;
    }
}

//Quick sorting
void QuickSort(vector<Kru>* v, int low, int high)
{
    if (low < high)
    {
        if (high - low + 1 <= 6)
            InsertionSort(v, low, high);
        else
        {
            int pivot = partition(v, low, high);
            QuickSort(v, low, pivot - 1);
            QuickSort(v, pivot + 1, high);
        }
    }
    return;
}

//get new pivot
int partition(vector<Kru>* v, int low, int high)
{
    int pivot = v->at(low).weight;
    int i = low;
    int j = high + 1;
    do
    {
        do {i++;} while(v->at(i).weight < pivot);
        do {j--;} while(v->at(j).weight > pivot);
        if (i < j) swap(v->at(i), v->at(j));
    } while (i < j);  //while

    swap(v->at(j), v->at(low));
    //set new pivot
    pivot = j;
    return pivot;
}

//Dijstra Search
bool Dijkstra(Graph* graph, char option, int vertex, ofstream *fout)
{
    int sz = graph->getSize();
    bool* visited = new bool[sz];
    int* dist = new int[sz];
    int* prev = new int[sz];
    //initialization
    memset(visited, false, sz);
    for (int i = 0; i < sz; i++)
        dist[i] = INF;
    memset(prev, -1, sz);

    //get all vertex and weight information
    map <int, int>* m = new map<int, int>[sz];
    if (option == 'Y')  //directed
    {
        for (int i = 0; i < sz; i++)
            graph->getAdjacentEdgesDirect(i, m + i);
    }
    else    //undirected
    {
        for (int i = 0; i < sz; i++)
            graph->getAdjacentEdges(i, m + i);
    }
    
    //find negative weights
    for (int i = 0; i < sz; i++)
    {
        for (auto temp = m[i].begin(); temp != m[i].end(); temp++)
            if (temp->second < 0) return 0; //if negative weight exists, return false
    }

    dist[vertex - 1] = 0;
    visited[vertex - 1] = true;
    //initialization from vertex to reachable node
    for (auto temp = m[vertex - 1].begin(); temp != m[vertex - 1].end(); temp++)
    {
        dist[temp->first - 1] = temp->second;
        prev[temp->first - 1] = vertex;
    }

    //compute shortest path 
    while(1)
    {
        //traversal
        int minimum = INF;
        int source = -1;
        //find minimum dist which is not visited
        for (int i = 0; i < sz; i++)
        {
            if (dist[i] < minimum && visited[i] == false)
            {
                source = i;
                minimum = dist[i];
            }
        }
        if (source == -1) break;    //visited all vertices
        visited[source] = true;
        int path = dist[source];
        for (auto temp = m[source].begin(); temp != m[source].end(); temp++)
        {
            int to = temp->first - 1;
            int weight = temp->second;
            int shortpath = min(dist[to], path + weight);
            if (shortpath != dist[to])    //short path is updated
            {
                dist[to] = shortpath;
                prev[to] = source + 1;
            }
        }
    }
    //print result
    (*fout) << "======== DIJKSTRA ========" << endl;
    if (option == 'Y')
        (*fout) << "Directed Graph Dijkstra result" << endl;
    else
        (*fout) << "Undirected Graph Dijkstra result" << endl;
    (*fout) << "startvertex: " << vertex << endl;
    stack<int> Print;
    for (int i = 0; i < sz; i++)
    {
        if (i == vertex - 1) continue;  //do not print start vertex
        (*fout) << "[ " << i + 1 << " ] ";
        if (prev[i] == -1) (*fout) << "x" << endl;  //if has no route
        else
        {
            int s = i;
            int shortpath = dist[i];
            while(prev[s] != -1)
            {
                Print.push(prev[s]);
                s = prev[s] - 1;
            }
            while(!Print.empty())
            {
                s = Print.top();
                Print.pop();
                if (Print.empty()) 
                {
                    (*fout) << s << " (" << dist[i] << ")" << endl;
                    break;
                }
                else (*fout) << s << " -> ";
            }
            
        }
    }
    (*fout) << "==========================" << endl << endl;
    //delete memory
    delete[] visited;
    delete[] dist;
    delete[] prev;
    delete[] m;
    return 1;
}

/*
int len = 0;
int beforeV = v;
while(beforeV != -1)
{
    len += dist[beforeV];
    beforeV = prev[v];
}
*/

//Bellmanford Search
bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex, ofstream *fout) 
{
    int sz = graph->getSize();
    //get all vertex and weight information
    map <int, int>* m = new map<int, int>[sz];
    if (option == 'Y')  //directed
    {
        for (int i = 0; i < sz; i++)
            graph->getAdjacentEdgesDirect(i, m + i);
    }
    else    //undirected
    {
        for (int i = 0; i < sz; i++)
            graph->getAdjacentEdges(i, m + i);
    }
    //Get all edges
    vector <Kru>* v = new vector<Kru>;
    int edge = 0;
    for (int i = 0; i < sz; i++)
    {
        for (auto temp = m[i].begin(); temp != m[i].end(); temp++)
        {
            Kru newKru = {i + 1, temp->first, temp->second};
            v->push_back(newKru);
            edge++;
        }
    }
    int* dist = new int[sz];    //store distance
    int* prev = new int[sz];    //sotre prev vertex
    //initializate all distance to INFINITY
    for (int i = 0; i < sz; i++)    
    {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[s_vertex - 1] = 0; //start vertex 
    //find shortest path
    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < edge; j++)
        {
            int from = v->at(j).from - 1;
            int to = v->at(j).to - 1;
            int weight = v->at(j).weight;
            if (dist[from] == INF) continue;
            if (dist[to] > dist[from] + weight) 
            {
                //negative cycle
                if (i == sz - 1)  return 0; //error
                else
                {
                    dist[to] = dist[from] + weight;
                    prev[to] = from + 1;
                }
            }
        }
    }
    //store route
    int s = e_vertex - 1;
    //if can't reach end vertex
    if (prev[s] == -1) return 0;
    vector<int> result;
    result.push_back(e_vertex);
    while(prev[s] != -1)
    {
        result.push_back(prev[s]);
        s = prev[s] - 1;
    }
    sz = result.size(); //the size of vector
    //print result
    (*fout) << "======== Bellman-Ford ========" << endl;
    if (option == 'Y')
        (*fout) << "Directed Graph Bellman-Ford result" << endl;
    else
        (*fout) << "Undirected Graph Bellman-Ford result" << endl;
    for (int i = sz - 1; i >= 0; i--)
    {
        (*fout) << result[i];
        if (i != 0) (*fout) << " -> ";
    }
    (*fout) << endl << "cost: " << dist[e_vertex - 1] << endl;
    (*fout) << "==============================" << endl << endl;

    //delete memory
    delete[] dist;
    delete[] prev;
    delete[] m;
    delete v;

    return 1;
}

//Floyd Search
bool FLOYD(Graph* graph, char option, ofstream *fout)
{
    int sz = graph->getSize();
    //create shortest path table
    int** path = new int*[sz];
    for (int i = 0; i < sz; i++)
        path[i] = new int[sz];
    //initializate matrix
    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            if (i == j) path[i][j] = 0;
            else path[i][j] = INF;
        }
    }
    //get all vertex and weight information
    map <int, int>* m = new map<int, int>[sz];
    if (option == 'Y')  //directed
    {
        for (int i = 0; i < sz; i++)
            graph->getAdjacentEdgesDirect(i, m + i);
    }
    else    //undirected
    {
        for (int i = 0; i < sz; i++)
            graph->getAdjacentEdges(i, m + i);
    }
    //fill initial matrix
    for (int i = 0; i < sz; i++)
    {
        for (auto temp = m[i].begin(); temp != m[i].end(); temp++)
            path[i][temp->first - 1] = temp->second;
    }
    //find shortest path
    for (int k = 0; k < sz; k++)
    {
        for (int i = 0; i < sz; i++)
        {
            for (int j = 0; j < sz; j++)
            {
                if (path[i][k] != INF && path[k][j] != INF) 
                    path[i][j] = min(path[i][j], path[i][k] + path[k][j]);
            }  
        }
    }
    //if negative cycle exists -> return 0 (fail)
    for (int i = 0; i < sz; i++)
    {
        if (path[i][i] < 0)
            return 0;
    }

    //print result
    (*fout) << "======== FLOYD ========" << endl;
    if (option == 'Y')
        (*fout) << "Directed Graph FLOYD result" << endl;
    else
        (*fout) << "Undirected Graph FLOYD result" << endl;
    (*fout) << "\t";
    for (int i = 0; i <sz; i++)
        (*fout) << "[ " << i + 1 << " ]\t";
    (*fout) << endl;
    for (int i = 0; i < sz; i++)
    {
        (*fout) << "[ " << i + 1 << " ]\t";
        for (int j = 0; j < sz; j++)
        {
            if (path[i][j] == INF) (*fout) << "x\t";    //if value is infinite
            else (*fout) << path[i][j] << "\t";
        }
        (*fout) << endl;
    }
    (*fout) << "======================" << endl << endl;

    //delete memory
    for (int i = 0; i < sz; i++)
        delete[] path[i];
    delete[] path;
    delete[] m;

    return 1;
}

//Kwangwoon search
bool KWANGWOON(Graph* graph, int vertex, ofstream *fout) 
{
    int sz = graph->getSize();
    int** tree = new int*[sz];  //segment tree
    bool* visited = new bool[sz];
    int prev = 1;
    memset(visited, false, sz);
    queue<int> route;
    map <int, int>* m = new map<int, int>[sz];
    for (int i = 0; i < sz; i++)
    {
        graph->getAdjacentEdges(i, m + i);
        int e = m[i].size();
        //create segment tree array
        tree[i] = new int[4*e];
        memset(tree[i], 0, sizeof(int)*4*e);
        init(0, e - 1, 1, tree[i]); //initialization
    }
    visited[0] = true;  //vertex 1
    vector <int>* kw_graph = new vector<int>[sz];
    for (int i = 0; i < sz; i++)
    {
        for (auto temp = m[i].begin(); temp != m[i].end(); temp++)
            kw_graph[i].push_back(temp->first);
    }

    //traversal
    for (int i = 0; i < sz; i++)
    {
        visited[prev - 1] = true;   //check visited
        route.push(prev);           //insert vertex
        for (int j = 0; j < sz; j++)
        {
            if(visited[j]) continue;
            auto temp = find(kw_graph[j].begin(), kw_graph[j].end(), prev);
            if (temp != kw_graph[j].end())
            {
                int idx = temp - kw_graph[j].begin();
                int e = m[j].size() - 1;
                update(0, e, 1, idx, -1, tree[j]);
            }
        }
        //set prev
        int high = 0, low = sz + 1, cnt = 0;
        for (auto temp = m[prev - 1].begin(); temp != m[prev - 1].end(); temp++)
        {
            int vt = temp->first;
            if (!visited[vt - 1])
            {
                high = max(high, vt);
                low = min(low, vt);
                cnt++;
            }
        }
        cout << "current vertex : " << prev << "/ high : " << high << " / low : " << low << " / count : " << cnt;
        if (cnt == 0) break;    //visited all vertices
        if (cnt % 2) prev = high;  //odd
        else prev = low;  //even
        cout << " / new vertex : " << prev << endl; 
    }

    //print result
    (*fout) << "======== KWANGWOON ========" << endl;
    (*fout) << "startvertex: 1" << endl;
    (*fout) << route.front();
    route.pop();
    while (!route.empty())
    {
        (*fout) << " -> " << route.front();
        route.pop();
    }
    (*fout) << endl << "===========================" << endl << endl;

    for (int i = 0; i < sz; i++)
        delete[] tree[i];
    delete[] tree;
    delete[] visited;

    return 1;
}

//create tree recursively
int init(int s, int e, int n, int* tree)
{
    if (s == e) return tree[n] = 1;
    int m = (s + e) / 2;
    return tree[n] = init(s, m, n * 2, tree) + init(m + 1, e, n * 2 + 1, tree);
}

//compute sum
int sum(int s, int e, int n, int l, int r, int* tree)
{
    //out of range
    if (l > e || r < s) return 0;
    //in range
    if (l <= s && e <= r) return tree[n];
    //compute sum
    int m = (s + e) / 2;
    return sum(s, m, n * 2, l, r, tree) + sum(m + 1, e, n * 2 + 1, l, r, tree);
}

//update sum
void update(int s, int e, int n, int idx, int v, int* tree)
{
    //out of range
    if (idx < s || idx > e) return;
    //in range
    tree[n] += v;
    if (s == e) return;
    int m = (s + e) / 2;
    update(s, m, n * 2, idx, v, tree);
    update(m + 1, e, n * 2 + 1, idx, v, tree);
    return;
}
