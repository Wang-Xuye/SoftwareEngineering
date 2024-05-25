#include <bits/stdc++.h>
#include "graph.h"
#include "random.h"

Graph G;
extern int randomInt(int l, int r);


vector<string> textPreprocess(string str) {
    // �ı�Ԥ�������� 
    // ����һ���ַ�����������Ӣ����д���ı�����
    // �ı���Ϊ����
    // ���з������ո���
    // �����ŵ����ո���
    // ���Է���ĸ�ַ��������ո���
    // ����ֵΪ��������
    vector<string> wordList;
    string tmp = "";
    for(auto ch : str) {
        if('a' <= ch && ch <= 'z') tmp += ch;
        else if('A' <= ch && ch <= 'Z') tmp += (char)(ch - 'A' + 'a');
        else if(tmp.size()) wordList.pb(tmp), tmp = "";
    }
    if(tmp.size()) wordList.pb(tmp);
    return wordList;
}

Graph::Graph(string path = "") {
    // ����ͼ���캯���� 
    // ����Ϊ�ַ��������������ļ�·��
    // ͨ�������ļ��е��ı���������ͼ
    if(path == "") return ;
    ifstream file(path);
    if(!file.is_open()) {
        cerr << "Error: File not open! " << endl;
        return ;
    }

    this -> Index.clear();
    this -> Vertex.clear();
    this -> Edge.clear();
    this -> allEdge.clear();
    this -> vertexNumber = 0;
    this -> edgeNumber = 0;

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();
    vector<string> wordList = textPreprocess(content);

    for(auto str : wordList) {
        if(this -> Index.find(str) == this -> Index.end()) {
            this -> Index[str] = this -> vertexNumber;
            this -> Vertex.pb(str);
            this -> vertexNumber++;
        }
    }
    for(int i = 0, edgeSize = wordList.size(); i < edgeSize - 1; i++) {
        this -> allEdge[mp(this -> Index[wordList[i]], 
            this -> Index[wordList[i + 1]])]++;
    }

    this -> Edge.resize(this -> vertexNumber);
    this -> edgeNumber = this -> allEdge.size();
    for(auto [edge, value] : this -> allEdge) {
        auto [from, to] = edge;
        this -> Edge[from].pb(mp(to, value));
    }
}

int Graph::getVertexNumber() {
    return this -> vertexNumber;
}
int Graph::getEdgeNumber() {
    return this -> edgeNumber;
}

int Graph::findIndex(string word) {
    // ��ѯ��ź����� 
    // ����Ϊһ������
    // ����ֵΪ�õ��ʶ�Ӧ�ı��
    // ���������򷵻� -1
    if(this -> Index.find(word) == this -> Index.end())
        return -1;
    else return this -> Index[word];
}
string Graph::findWord(int index) {
    // ��ѯ���ʺ����� 
    // ����Ϊһ�����
    // ����ֵΪ�ñ�Ŷ�Ӧ�ĵ���
    // ���������򷵻ؿմ�
    if(index < 0 || index >= this -> vertexNumber) return "";
    else return this -> Vertex[index];
}

vector<pair<pair<string, string>, int>> Graph::getAllEdge() {
    // ��ȡ���бߺ���: 
    // ����ֵΪ���бߵ� from, to �� value
    vector<pair<pair<string, string>, int>> edge;
    for(auto [e, value] : this -> allEdge) {
        auto [from, to] = e;
        edge.pb(mp(mp(
            this -> Vertex[from], this -> Vertex[to]), value));
    }
    return edge;
}

vector<string> Graph::findBridgeWords(
    string word1, string word2) {
    // ��ѯ�ŽӴʺ����� 
    // ����Ϊ��ѯ�ŽӴʵ���������
    // ����ֵΪ�ŽӴ�����
    int index1 = this -> Index[word1];
    int index2 = this -> Index[word2];
    if(index1 == -1 || index2 == -1) return vector<string>();
    vector<string> wordList;
    for(int i = 0; i < this -> vertexNumber; i++) {
        if(this -> allEdge.find(mp(index1, i)) != this -> allEdge.end() && 
            this -> allEdge.find(mp(i, index2)) != this -> allEdge.end()) {
                wordList.pb(this -> Vertex[i]);
            }
    }
    return wordList;
}

string Graph::randomBridgeWords(string word1, string word2) {
    vector<string> wordList = this -> findBridgeWords(word1, word2);
    if(!wordList.size()) return "";
    else return wordList[randomInt(0, wordList.size() - 1)];
}

void showDirectedGraph(string path) {
    // չʾ����ͼ������
    // ����Ϊ����ͼ������ļ�·��
    // ʹ�� graphviz ���������ͼ
    // �����Ƶ�����ͼ������ path ��
    ofstream out("tmp.dot", ios::out);
	out << "digraph G {" << endl;

    auto allEdge = G.getAllEdge();
    for(auto [edge, value] : allEdge) {
        auto [from, to] = edge;
        out << "\t" << from << " -> " << to
            << " [label = " << value << "];" << endl;
    }
	out << "}" << endl;
	out.close();

	string tmp = "dot -Tpng tmp.dot -o " + path;
	system(tmp.c_str());
	remove("tmp.dot");
}

string queryBridgeWords(string word1, 
    string word2) {
    // ��ѯ�ŽӴʺ����� 
    // ����Ϊ����ͼ�Ͳ�ѯ�ŽӴʵ���������
    // ����ֵΪ�ŽӴʲ�ѯ���
    int index1 = G.findIndex(word1), index2 = G.findIndex(word2);
    string tmp = "";
    if(index1 == -1 || index2 == -1) {
        if(index1 == -1 && index2 == -1) {
            tmp = "No \'" + word1 + "\' and \'" 
                + word2 + "\' in the graph! ";
        }
        else if(index1 == -1) {
            tmp = "No \'" + word1 + "\' in the graph! ";
        }
        else if(index2 == -1) {
            tmp = "No \'" + word2 + "\' in the graph! ";
        }
    }
    else {
        auto wordList = G.findBridgeWords(word1, word2);
        switch(wordList.size()) {
            case 0: 
                tmp = "No bridge words from \'" 
                    + word1 + "\' to \'" + word2 + "\'! ";
                break;
            case 1: 
                tmp = "The bridge word from \'" 
                    + word1 + "\' to \'" + word2 
                    + "\' is: " + wordList[0] + ". ";
                break;
            default: 
                tmp = "The bridge words from \'" 
                    + word1 + "\' to \'" + word2 + "\' are: ";
                for(auto word : wordList) tmp += word + ", ";
                tmp[tmp.size() - 2] = '.';
                break;
        }
    }
    return tmp;
}

string generateNewText(string path) {
    // �����ŽӴ��������ı������� 
    // ����Ϊ�ı���·��
    // ��������������ŽӴʣ��򱣳ֲ���
    // �����������֮����ڶ���ŽӴʣ�
    // ���������ѡ��һ�������ȥ�γ����ı�
    // ����ֵΪ�����ɵ��ı���

    ifstream file(path);
    if(!file.is_open()) {
        cerr << "Error: File not open! " << endl;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();
    vector<string> wordList = textPreprocess(content);

    string output = "";
    for(int i = 0, wordNumber = wordList.size(); i < wordNumber; i++) {
        output += wordList[i];
        if(i < wordNumber - 1) {
            string bridgeWord = G.randomBridgeWords(
                wordList[i], wordList[i + 1]);
            if(bridgeWord != "") output += " " + bridgeWord;
            output += " ";
        }
    }
    return output;
}


vector<int> Graph::shortestPath(int index) {
    // �����·������ 
    // ����Ϊ��㵥�ʱ��
    // ����ֵΪ��㵥�ʵ��������ʵ����·����
    vector<int> dis(this -> vertexNumber, -1);
    dis[index] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push(mp(0, index));
    vector<bool> vis(this -> vertexNumber, false);
    while(q.size()) {
        auto [d, x] = q.top(); q.pop();
        if(vis[x]) continue;
        vis[x]=true;
        for(auto [y, z] : this -> Edge[x]) {
            if(dis[y] == -1 || dis[x] + z < dis[y]) {
                dis[y] = dis[x] + z;
                q.push(mp(dis[y], y));
            }
        }
    }
    return dis;
}
void calcShortestPath1(string word1, string word2) {
    // ������������֮������·�������� 
    // ����Ϊ��������
    // ��ʾ�������ʲ��ɴ�
    // �������ļ� shortestPath.txt ������������·
    // ������ͼƬ shortestPath.png չʾ����һ��
    int index1 = G.findIndex(word1);
    int index2 = G.findIndex(word2);
    if(index1 == -1 || index2 == -1) {
        cerr << "unreachable" << endl;
        return ;
    }

    vector<int> dis = G.shortestPath(index1);
    if(dis[index2] == -1) {
        cerr << "unreachable" << endl;
        return ;
    }
    vector<vector<int>> pre(G.getVertexNumber(), vector<int>());
    auto allEdge = G.getAllEdge();
    for(auto [edge, value] : allEdge) {
        auto [fromWord, toWord] = edge;
        int from = G.findIndex(fromWord);
        int to = G.findIndex(toWord);
        if(dis[from] + value == dis[to]) pre[to].pb(from);
    }
    
    // ��¼����·���� shortestPath.txt
    ofstream out("shortestPath.txt", ios::out);
    out << "Shortest Path from \'" << word1 
        << "\' to \'" << word2 << "\': " << endl;
    
    function<void(int, string)> getShortestPath = [&](
        int now, string path) -> void {
        if(now == index1) {
            out << path << endl;
            return ;
        }
        for(auto lst : pre[now]) {
            getShortestPath(lst, G.findWord(lst) + " -> " + path);
        }
    };
    getShortestPath(index2, word2);

    out.close();

    // չʾ����һ��·���� shortestPath.png
    ofstream ouf("tmp.dot", ios::out);
	ouf << "digraph G {" << endl;

    set<pii> path;
    for(int now = index2, lst; now != index1; now = lst) {
        lst = pre[now][0];
        path.insert(mp(lst, now));
    }
    for(auto [edge, value] : allEdge) {
        auto [fromWord, toWord] = edge;
        int from = G.findIndex(fromWord);
        int to = G.findIndex(toWord);
        if(path.find(mp(from, to)) == path.end()) 
            ouf << fromWord << " -> " << toWord << " [label = " 
                << value << "];" << endl;
        else 
            ouf << fromWord << " -> " << toWord << " [label = " 
                << value << ", color = red];" << endl;
    }
    ouf << "}" << endl;
    ouf.close();
    
	string tmp = "dot -Tpng tmp.dot -o shortestPath.png";
	system(tmp.c_str());
	remove("tmp.dot");
}
void calcShortestPath2(string word) {
    // ���㵥�ʵ����е��ʵ����·�������� 
    // ����Ϊһ������
    // ���ļ� shortestPathAll.txt ������������·
    int index = G.findIndex(word);
    if(index == -1) {
        cerr << "Word not exists" << endl;
        return ;
    }

    vector<int> dis = G.shortestPath(index);
    vector<vector<int>> pre(G.getVertexNumber(), vector<int>());
    auto allEdge = G.getAllEdge();
    for(auto [edge, value] : allEdge) {
        auto [fromWord, toWord] = edge;
        int from = G.findIndex(fromWord);
        int to = G.findIndex(toWord);
        if(dis[from] + value == dis[to]) pre[to].pb(from);
    }


    ofstream out("shortestPathAll.txt", ios::out);

    function<void(int, string)> getShortestPath = [&](
        int now, string path) -> void {
        if(now == index) {
            out << path << endl;
            return ;
        }
        for(auto lst : pre[now]) {
            getShortestPath(lst, G.findWord(lst) + " -> " + path);
        }
    };

    for(int i = 0, n = G.getVertexNumber(); i < n; i++) {
        if(i == index) continue;
        string word2 = G.findWord(i);
        out << "Shortest Path from \'" << word 
            << "\' to \'" << word2 << "\': " << endl;
        getShortestPath(i, word2);
        out << endl;
    }
    out.close();
}


int Graph::randomNextNodeIndex(int index) {
    // ���ȡ��һ�����ʱ�ź����� 
    // ����Ϊ��ǰ���ʱ��
    // ������������г��������ѡ��һ������
    // ����ֵΪѡ�еĳ���ָ��ĵ��ʵı��
    // ��û�г��ߣ��򷵻� -1
    if(!Edge[index].size()) return -1;
    return Edge[index][randomInt(0, Edge[index].size() - 1)].first;
}
string randomWalk() {
    // ������ߺ����� 
    // ��������Ĵ�ͼ��ѡ��һ���ڵ㣬
    // �Դ�Ϊ����س��߽������������
    // ��¼���������нڵ�ͱߣ�
    // ֱ�����ֵ�һ���ظ��ı�Ϊֹ��
    // ���߽����ĳ���ڵ㲻���ڳ���Ϊֹ��
    // �ڱ��������У��û�Ҳ����ʱֹͣ������
    int index = randomInt(0, G.getVertexNumber() - 1);
    string walkList = G.findWord(index);
    set<pii> edgeExist;
    while(1) {
        int nextIndex = G.randomNextNodeIndex(index);
        if(nextIndex == -1) break;
        walkList += " -> " + G.findWord(nextIndex);
        if(edgeExist.find(mp(index, nextIndex)) 
            != edgeExist.end()) break;
        edgeExist.insert(mp(index, nextIndex));
        index = nextIndex;
    }
    return walkList;
}