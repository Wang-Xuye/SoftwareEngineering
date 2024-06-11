// Copyright 2024 wangxuye

#ifndef LAB3_INCLUDE_GRAPH_H_
#define LAB3_INCLUDE_GRAPH_H_

#include <bits/stdc++.h>
#include <map>
#include <utility>
#include <vector>
#include <string>
#define pii std::pair<int, int>
#define mp std::make_pair
#define pb push_back
#define edgeString std::pair<std::pair<std::string, std::string>, int>
#define edgeInt std::pair<std::pair<std::int, std::int>, int>

class Graph {
 private:
    int vertexNumber, edgeNumber;
    std::map<std::string, int> Index;
    std::vector<std::string> Vertex;
    std::vector<std::vector<pii>> Edge;
    std::map<pii, int> allEdge;
    // 以 std::pair<int, int> 形式存储边，便于查询桥接词，权值表示出现次数
 public:
    Graph() {}
    explicit Graph(const std::string&);
    int getVertexNumber();
    int findIndex(const std::string&);
    std::string findWord(int);
    std::vector<edgeString> getAllEdge();
    std::vector<std::string> findBridgeWords(
      const std::string&, const std::string&);
    std::vector<int> shortestPath(int);
    std::string randomBridgeWords(const std::string&, const std::string&);
    int randomNextNodeIndex(int);
};
extern Graph G;

extern std::vector<std::string> textPreprocess(const std::string&);
extern void showDirectedGraph(const std::string&);
extern std::string queryBridgeWords(const std::string&, const std::string&);
extern std::string generateNewText(const std::string&);
extern void calcShortestPath1(const std::string&, const std::string&);
extern void calcShortestPath2(const std::string&);
extern std::string randomWalk();

extern std::mt19937 randint;
extern int randomInt(int l, int r);

#endif  // LAB3_INCLUDE_GRAPH_H_
