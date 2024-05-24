#include <bits/stdc++.h>
#include "random.h"
#include "graph.h"
using namespace std;



int main(int argc, char* argv[]) {
    if(argc != 1) {
        perror("parameters error\n");
        exit(1);
    }
    cerr << "请输入文本串所在文件路径：";
    string path; cin >> path;
    while(1) {
        ifstream file(path);
        if(file.is_open()) break;
        cerr << "请重新输入文本串所在文件路径：" << endl;
        cin >> path;
    }
    G = Graph(path);

    system("clear");
    cerr << "功能介绍：" << endl;
    cerr << "graph: 查看有向图" << endl;
    cerr << "bridge word1 word2: 查询桥接词" << endl;
    cerr << "generate path: 根据桥接词生成文本" << endl;
    cerr << "short1 word1 word2: 查询两个单词之间的最短路径" << endl;
    cerr << "short2 word: 查询单词到所有单词的最短路径" << endl;
    cerr << "walk: 随机游走" << endl;
    cerr << "exit: 退出" << endl;

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
            calcShortestPath(word1, word2);
        }
        else if(cmd == "short2") {
            string word;
            cin >> word;
            calcShortestPath(word);
        }
        else if(cmd == "walk") {
            cerr << randomWalk() << endl;
        }
        else {
            cerr << "请输入合法的指令" << endl;
        }
    }
    return 0;
}