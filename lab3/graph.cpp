#include <bits/stdc++.h>
#include "graph.h"
#include "random.h"

Graph G;
extern int randomInt(int l, int r);


vector<string> textPreprocess(string str) {
    // 文本预处理函数： 
    // 输入一个字符串，包含用英文书写的文本数据
    // 文本分为多行
    // 换行符当作空格处理
    // 标点符号当作空格处理
    // 忽略非字母字符（当作空格处理）
    // 返回值为单词序列
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
    // 有向图构造函数： 
    // 输入为字符串，包含输入文件路径
    // 通过输入文件中的文本构造有向图
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
    // 查询编号函数： 
    // 输入为一个单词
    // 返回值为该单词对应的编号
    // 若不存在则返回 -1
    if(this -> Index.find(word) == this -> Index.end())
        return -1;
    else return this -> Index[word];
}
string Graph::findWord(int index) {
    // 查询单词函数： 
    // 输入为一个编号
    // 返回值为该编号对应的单词
    // 若不存在则返回空串
    if(index < 0 || index >= this -> vertexNumber) return "";
    else return this -> Vertex[index];
}

vector<pair<pair<string, string>, int>> Graph::getAllEdge() {
    // 获取所有边函数: 
    // 返回值为所有边的 from, to 和 value
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
    // 查询桥接词函数： 
    // 输入为查询桥接词的两个单词
    // 返回值为桥接词序列
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
    // 展示有向图函数：
    // 输入为有向图和输出文件路径
    // 使用 graphviz 库绘制有向图
    // 将绘制的有向图保存在 path 中
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
    // 查询桥接词函数： 
    // 输入为有向图和查询桥接词的两个单词
    // 返回值为桥接词查询结果
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
    // 根据桥接词生成新文本函数： 
    // 输入为文本串路径
    // 如果两个单词无桥接词，则保持不变
    // 如果两个单词之间存在多个桥接词，
    // 则随机从中选择一个插入进去形成新文本
    // 返回值为新生成的文本串

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
    // 求最短路函数： 
    // 输入为起点单词编号
    // 返回值为起点单词到各个单词的最短路长度
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
    // 计算两个单词之间的最短路径函数： 
    // 输入为两个单词
    // 提示两个单词不可达
    // 或者在文件 shortestPath.txt 中输出所有最短路
    // 并且在图片 shortestPath.png 展示其中一条
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
    
    // 记录所有路径到 shortestPath.txt
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

    // 展示其中一条路径到 shortestPath.png
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
    // 计算单词到所有单词的最短路径函数： 
    // 输入为一个单词
    // 在文件 shortestPathAll.txt 中输出所有最短路
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
    // 随机取下一个单词编号函数： 
    // 输入为当前单词编号
    // 在这个单词所有出边中随机选择一条出边
    // 返回值为选中的出边指向的单词的编号
    // 若没有出边，则返回 -1
    if(!Edge[index].size()) return -1;
    return Edge[index][randomInt(0, Edge[index].size() - 1)].first;
}
string randomWalk() {
    // 随机游走函数： 
    // 程序随机的从图中选择一个节点，
    // 以此为起点沿出边进行随机遍历，
    // 记录经过的所有节点和边，
    // 直到出现第一条重复的边为止，
    // 或者进入的某个节点不存在出边为止。
    // 在遍历过程中，用户也可随时停止遍历。
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