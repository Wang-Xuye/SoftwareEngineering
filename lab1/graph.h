#ifndef __GRAPH_H
#define __GRAPH_H

#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define mp make_pair
#define pb push_back

class Graph {
private:
	int vertexNumber, edgeNumber;
	
	map<string, int> Index;
    vector<string> Vertex;
    vector<vector<pii>> Edge;
	map<pii, int> allEdge;
	// 以 pair<int, int> 形式存储边，便于查询桥接词，权值表示出现次数
public:
	Graph(string);
	int getVertexNumber();
	int findIndex(string);
    string findWord(int);
	vector<pair<pair<string, string>, int>> getAllEdge();
	vector<string> findBridgeWords(string, string);
	vector<int> shortestPath(int);
	string randomBridgeWords(string, string);
    int randomNextNodeIndex(int);
} ;
Graph G;

extern vector<string> textPreprocess(string);
extern void showDirectedGraph(string);
extern string queryBridgeWords(string, string);
extern string generateNewText(string);
extern void calcShortestPath(string, string);
extern void calcShortestPath(string);
extern string randomWalk();


#endif