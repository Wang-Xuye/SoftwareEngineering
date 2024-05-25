#include <bits/stdc++.h>
#include "random.h"
#include "graph.h"
using namespace std;

extern Graph G;

int main(int argc, char* argv[]) {
    if(argc != 1) {
        perror("parameters error\n");
        exit(1);
    }
    cerr << "Please input the path of the content file: ";
    // cerr << "请输入文本串所在文件路径：";
    string path; cin >> path;
    while(1) {
        ifstream file(path);
        if(file.is_open()) break;
        cerr << "Please reinput the path of the content file: ";
        // cerr << "请重新输入文本串所在文件路径：";
        cin >> path;
    }
    G = Graph(path);
    
    // system("clear");
    cerr << "Introduction: " << endl;
    cerr << "graph: Show digraph" << endl;
    cerr << "bridge word1 word2: Look for bridge words" << endl;
    cerr << "generate path: generate new content according to bridge words" << endl;
    cerr << "short1 word1 word2: Look for the shortest path between two words" << endl;
    cerr << "short2 word: Look for the shortest path from the word to other words" << endl;
    cerr << "walk: Random walk" << endl;
    cerr << "exit: Exit" << endl;
    // cerr << "功能介绍：" << endl;
    // cerr << "graph: 查看有向图" << endl;
    // cerr << "bridge word1 word2: 查询桥接词" << endl;
    // cerr << "generate path: 根据桥接词生成文本" << endl;
    // cerr << "short1 word1 word2: 查询两个单词之间的最短路径" << endl;
    // cerr << "short2 word: 查询单词到所有单词的最短路径" << endl;
    // cerr << "walk: 随机游走" << endl;
    // cerr << "exit: 退出" << endl;

    string cmd;
    while(1) {
        cerr << ">>> ";
        cin >> cmd;
        if(cmd == "exit") break;
        else if(cmd == "graph") showDirectedGraph("graph.png");
        else if(cmd == "bridge") {
            string word1, word2;
            cin >> word1 >> word2;
            cerr << queryBridgeWords(word1, word2) << endl;
        }
        else if(cmd == "generate") {
            string path;
            cin >> path;
            cerr << generateNewText(path) << endl;
        }
        else if(cmd == "short1") {
            string word1, word2;
            cin >> word1 >> word2;
            calcShortestPath1(word1, word2);
        }
        else if(cmd == "short2") {
            string word;
            cin >> word;
            calcShortestPath2(word);
        }
        else if(cmd == "walk") {
            cerr << randomWalk() << endl;
        }
        else {
            cerr << "Command \'" << cmd << "\' not found" << endl;
        }
    }
    return 0;
}