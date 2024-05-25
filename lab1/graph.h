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
	// �� pair<int, int> ��ʽ�洢�ߣ����ڲ�ѯ�ŽӴʣ�Ȩֵ��ʾ���ִ���
public:
	Graph() {}
	Graph(string);
	int getVertexNumber();
	int getEdgeNumber();
	int findIndex(string);
    string findWord(int);
	vector<pair<pair<string, string>, int>> getAllEdge();
	vector<string> findBridgeWords(string, string);
	vector<int> shortestPath(int);
	string randomBridgeWords(string, string);
    int randomNextNodeIndex(int);
} ;
extern Graph G;

extern vector<string> textPreprocess(string);
extern void showDirectedGraph(string);
extern string queryBridgeWords(string, string);
extern string generateNewText(string);
extern void calcShortestPath1(string, string);
extern void calcShortestPath2(string);
extern string randomWalk();

extern mt19937 randint;
extern int randomInt(int l, int r);

#endif