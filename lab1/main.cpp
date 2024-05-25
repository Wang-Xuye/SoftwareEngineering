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
    // cerr << "�������ı��������ļ�·����";
    string path; cin >> path;
    while(1) {
        ifstream file(path);
        if(file.is_open()) break;
        cerr << "Please reinput the path of the content file: ";
        // cerr << "�����������ı��������ļ�·����";
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
    // cerr << "���ܽ��ܣ�" << endl;
    // cerr << "graph: �鿴����ͼ" << endl;
    // cerr << "bridge word1 word2: ��ѯ�ŽӴ�" << endl;
    // cerr << "generate path: �����ŽӴ������ı�" << endl;
    // cerr << "short1 word1 word2: ��ѯ��������֮������·��" << endl;
    // cerr << "short2 word: ��ѯ���ʵ����е��ʵ����·��" << endl;
    // cerr << "walk: �������" << endl;
    // cerr << "exit: �˳�" << endl;

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