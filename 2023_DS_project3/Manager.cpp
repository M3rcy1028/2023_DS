#include "Manager.h"
#include "GraphMethod.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

Manager::Manager()	
{
	graph = nullptr;	
	fout.open("log.txt", ios::app);
	load = 0;	//Anything is not loaded
}

Manager::~Manager()
{
	if(load)	//if graph is loaded, delete graph
		delete graph;	
	if(fout.is_open())	//if fout is opened, close file
		fout.close();	//close log.txt File
}

void Manager::run(const char* command_txt){
	ifstream fin;	//Command File Input File Stream
	fin.open(command_txt, ios_base::in);//File open with read mode
	if(!fin) { //If command File cannot be read, Print error
		fout<<"command file open error"<<endl;
		return;	//Return
	}

	string buffer;	//store line
	while (!fin.eof())
	{
		//cout << buffer << endl;
		getline(fin, buffer);	//read line

		if (buffer.find("LOAD") != string::npos)	//LOAD
		{
			if (!LOAD(buffer.substr(5, 15).c_str()))
				printErrorCode(100);
			else
			{
				fout << "======== LOAD ========" << endl;
				fout << "Success" << endl;
				fout << "======================" << endl << endl;
			}
		} 
		else if (buffer.find("PRINT") != string::npos)
		{
			if (!PRINT())
				printErrorCode(200);
		}
		else if (buffer.find("BFS") != string::npos)
		{
			//missing start vertex or option
			if (buffer.length() < 6) printErrorCode(300);
			else 
			{
				char option = buffer[4];
				int vertex = atoi(buffer.substr(6).c_str());
				if (!mBFS(option, vertex))
					printErrorCode(300);
			}
		}
		else if (buffer.find("DFS") != string::npos)
		{
			//missing start vertex or option
			if (buffer.length() < 6) printErrorCode(400);
			else
			{
				char option = buffer[4];
				int vertex = atoi(buffer.substr(6).c_str());
				if (!mDFS(option, vertex))
					printErrorCode(400);
			}
		}
		else if (buffer.find("KWANGWOON") != string::npos)
		{
			if (!mKwangWoon(1))
				printErrorCode(500);
		}
		else if (buffer.find("KRUSKAL") != string::npos)
		{
			if (!mKRUSKAL())
				printErrorCode(600);
		}
		else if (buffer.find("DIJKSTRA") != string::npos)
		{
			//missing start vertex or option
			if (buffer.length() < 10) printErrorCode(700);
			else
			{
				char option = buffer[9];
				int vertex = atoi(buffer.substr(11).c_str());
				if (!mDIJKSTRA(option, vertex))
					printErrorCode(700);
			}
		}
		else if (buffer.find("BELLMANFORD") != string::npos)
		{
			//missing start vertex or option
			if (buffer.length() < 16) printErrorCode(800);
			else
			{
				char option = buffer[12];
				int pos = 14;
				int blank = buffer.find(' ', pos);
				int s = atoi(buffer.substr(pos, blank - pos).c_str());
				int e = atoi(buffer.substr(blank + 1).c_str());
				if (!mBELLMANFORD(option, s, e))
					printErrorCode(800);
			}
		}
		else if (buffer.find("FLOYD") != string::npos)
		{
			char option = buffer[6];
			if (!mFLOYD(option))
				printErrorCode(900);
		}
		else if (buffer.find("EXIT") != string::npos)	//EXIT
		{
			fout << "======== EXIT ========" << endl;
			fout << "Success" << endl;
			fout << "======================" << endl << endl;
			break;	//end program
		}
		else printErrorCode(1000);
	}

	fout.close();
	fin.close();
	delete graph;
	return;
}

//load graph information
bool Manager::LOAD(const char* filename)
{
	ifstream fread;
	fread.open(filename, ios_base::in);
	if (!fread) return 0; //cannot open file

	string buffer;
	//get type
	if (!getline(fread, buffer)) return 0; 

	if (buffer == "L") //List Graph
	{
		if (graph) delete graph; //graph alreadt exists
		getline(fread, buffer);
		graph = new ListGraph(0, atoi(buffer.c_str()));
		
		getline(fread, buffer);	//get first vertex
		int vertex = atoi(buffer.c_str());
		while(getline(fread, buffer))
		{
			if (buffer.find(' ') == string::npos)	
				vertex = atoi(buffer.c_str());
			else	//insert new vertex
			{
				int blank = buffer.find(" ");
				int dest = atoi(buffer.substr(0, blank).c_str());
				int weight = atoi(buffer.substr(blank + 1).c_str());
				graph->insertEdge(vertex, dest, weight);
				//cout << "From : " << vertex << " / To : " << dest << " / Weight : " << weight << endl;
			}

		}
	}
	else	//Matrix Graph
	{
		if (graph) delete graph; //graph alreadt exists
		getline(fread, buffer);
		int sz = atoi(buffer.c_str());
		graph = new MatrixGraph(1, sz);
		//cout << "Matrix Size : " << sz;
		//cout << endl;
		for (int i = 0; i < sz; i++)	//i = vertex
		{
			getline(fread, buffer);
			int pos = 0;
			int blank = buffer.find(" ");
			for (int j = 0; j < sz; j++)
			{
				//cout << "Pos : " << pos << " Blank : " << blank << endl;
				int weight = 0;
				if (blank == string::npos)
					weight = atoi(buffer.substr(pos).c_str());
				else
					weight = atoi(buffer.substr(pos, blank - pos).c_str());
				if (weight != 0)
				{
					graph->insertEdge(i + 1, j + 1, weight);
					//cout << "From : " << i + 1 << " / To : " << j + 1 << " / Weight : " << weight << endl;
				}
				pos = blank + 1;
				blank = buffer.find(' ', pos);
			}
		}
	}
	return 1;
}

//print graph
bool Manager::PRINT()	
{
	if (graph == nullptr) return 0;
	graph->printGraph(&fout);
	return 1;
}

//BFS method
bool Manager::mBFS(char option, int vertex)	
{
	//error
	if (!graph) return 0;
	if (vertex > graph->getSize()) return 0;
	if (vertex < 0) return 0;
	if (option != 'Y' && option != 'N') return 0;
	return BFS(graph, option, vertex, &fout);	//return result
}

//DFS method
bool Manager::mDFS(char option, int vertex)	
{
	//error
	if (!graph) return 0;
	if (vertex > graph->getSize()) return 0;
	if (vertex < 0) return 0;
	if (option != 'Y' && option != 'N') return 0;
	return DFS(graph, option, vertex, &fout);	//return result
}

//DIJKSTRA method
bool Manager::mDIJKSTRA(char option, int vertex)	
{
	//error
	if (!graph) return 0;
	if (vertex > graph->getSize()) return 0;
	if (vertex < 0) return 0;
	if (option != 'Y' && option != 'N') return 0;
	return Dijkstra(graph, option, vertex, &fout);	//return result
}

//KRUSKAL method
bool Manager::mKRUSKAL()
{
 	if (!graph) return 0;	//error
	return Kruskal(graph, &fout);	//return result
}

//BELLMAN FORD method
bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex) 
{
	//error
	if (!graph) return 0;
	if (s_vertex > graph->getSize() || e_vertex > graph->getSize()) return 0;
	if (s_vertex < 0 || e_vertex < 0) return 0;
	if (option != 'Y' && option != 'N') return 0;
	//return result
	return Bellmanford(graph, option, s_vertex, e_vertex, &fout);
}

//FLOYD method
bool Manager::mFLOYD(char option)
{
	if (!graph) return 0;	//error
	if (option != 'Y' && option != 'N') return 0;
	return FLOYD(graph, option, &fout);	//return result
}

//KWANGWOON method
bool Manager::mKwangWoon(int vertex) 
{
	if (!graph) return 0;	//error
	if (graph->getType()) return 0;
	return KWANGWOON(graph, 1, &fout);	//return result
}

//print error code
void Manager::printErrorCode(int n)
{
	fout<<"========ERROR======="<<endl;
	fout<<n<<endl;
	fout<<"===================="<<endl << endl;
}


