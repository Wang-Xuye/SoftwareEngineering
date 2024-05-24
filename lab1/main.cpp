#include <bits/stdc++.h>
#include "random.h"
#include "graph.h"
using namespace std;



int main(int argc, char* argv[]) {
    if(argc != 1) {
        perror("parameters error\n");
        exit(1);
    }
    cerr << "�������ı��������ļ�·����";
    string path; cin >> path;
    while(1) {
        ifstream file(path);
        if(file.is_open()) break;
        cerr << "�����������ı��������ļ�·����" << endl;
        cin >> path;
    }
    G = Graph(path);

    system("clear");
    cerr << "���ܽ��ܣ�" << endl;
    cerr << "graph: �鿴����ͼ" << endl;
    cerr << "bridge word1 word2: ��ѯ�ŽӴ�" << endl;
    cerr << "generate path: �����ŽӴ������ı�" << endl;
    cerr << "short1 word1 word2: ��ѯ��������֮������·��" << endl;
    cerr << "short2 word: ��ѯ���ʵ����е��ʵ����·��" << endl;
    cerr << "walk: �������" << endl;
    cerr << "exit: �˳�" << endl;

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
            cerr << "������Ϸ���ָ��" << endl;
        }
    }
    return 0;
}