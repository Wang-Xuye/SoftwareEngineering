// Copyright 2024 wangxuye

#include <functional>
#include <queue>
#include <set>
#include "include/graph.h"
#include "include/random.h"

Graph G;
extern int randomInt(int l, int r);


std::vector<std::string> textPreprocess(const std::string& str) {
    // 文本预处理函数：
    // 输入一个字符串，包含用英文书写的文本数据
    // 文本分为多行
    // 换行符当作空格处理
    // 标点符号当作空格处理
    // 忽略非字母字符（当作空格处理）
    // 返回值为单词序列
    std::vector<std::string> wordList;
    std::string tmp = "";
    for (auto ch : str) {
        if ('a' <= ch && ch <= 'z')
            tmp += ch;
        else if ('A' <= ch && ch <= 'Z')
            tmp += static_cast<char>(ch - 'A' + 'a');
        else if (tmp.size())
            wordList.pb(tmp), tmp = "";
    }
    if (tmp.size()) wordList.pb(tmp);
    return wordList;
}

Graph::Graph(const std::string& path = "") {
    // 有向图构造函数：
    // 输入为字符串，包含输入文件路径
    // 通过输入文件中的文本构造有向图
    if (path == "") return;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: File not open! " << std::endl;
        return;
    }

    this->Index.clear();
    this->Vertex.clear();
    this->Edge.clear();
    this->allEdge.clear();
    this->vertexNumber = 0;
    this->edgeNumber = 0;

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    std::vector<std::string> wordList = textPreprocess(content);

    for (auto str : wordList) {
        if ((this->Index.try_emplace(str, this->vertexNumber)).second) {
            this->Vertex.pb(str);
            this->vertexNumber++;
        }
    }
    for (int i = 0, edgeSize = wordList.size(); i < edgeSize - 1; i++) {
        this->allEdge[mp(this->Index[wordList[i]],
            this->Index[wordList[i + 1]])]++;
    }

    this->Edge.resize(this->vertexNumber);
    this->edgeNumber = this->allEdge.size();
    for (auto [edge, value] : this->allEdge) {
        auto [from, to] = edge;
        this->Edge[from].pb(mp(to, value));
    }
}

int Graph::getVertexNumber() {
    return this->vertexNumber;
}

int Graph::findIndex(const std::string& word) {
    // 查询编号函数：
    // 输入为一个单词
    // 返回值为该单词对应的编号
    // 若不存在则返回 -1
    if (this->Index.find(word) == this->Index.end())
        return -1;
    else
        return this->Index[word];
}
std::string Graph::findWord(int index) {
    // 查询单词函数：
    // 输入为一个编号
    // 返回值为该编号对应的单词
    // 若不存在则返回空串
    if (index < 0 || index >= this->vertexNumber)
        return "";
    else
        return this->Vertex[index];
}

std::vector<edgeString> Graph::getAllEdge() {
    // 获取所有边函数：
    // 返回值为所有边的 from, to 和 value
    std::vector<edgeString> edge;
    for (auto [e, value] : this->allEdge) {
        auto [from, to] = e;
        edge.pb(mp(mp(
            this->Vertex[from], this->Vertex[to]), value));
    }
    return edge;
}

std::vector<std::string> Graph::findBridgeWords(
    const std::string& word1, const std::string& word2) {
    // 查询桥接词函数：
    // 输入为查询桥接词的两个单词
    // 返回值为桥接词序列
    int index1 = this->Index[word1];
    int index2 = this->Index[word2];
    if (index1 == -1 || index2 == -1) return std::vector<std::string>();
    std::vector<std::string> wordList;
    for (int i = 0; i < this->vertexNumber; i++) {
        if (this->allEdge.find(mp(index1, i)) != this->allEdge.end() &&
            this->allEdge.find(mp(i, index2)) != this->allEdge.end()) {
                wordList.pb(this->Vertex[i]);
            }
    }
    return wordList;
}

std::string Graph::randomBridgeWords(
    const std::string& word1, const std::string& word2) {
    std::vector<std::string> wordList = this->findBridgeWords(word1, word2);
    if (!wordList.size())
        return "";
    else
        return wordList[randomInt(0, wordList.size() - 1)];
}

void showDirectedGraph(const std::string& path) {
    // 展示有向图函数：
    // 输入为有向图和输出文件路径
    // 使用 graphviz 库绘制有向图
    // 将绘制的有向图保存在 path 中
    std::ofstream out("tmp.dot", std::ios::out);
    out << "digraph G {" << std::endl;

    auto allEdge = G.getAllEdge();
    for (auto [edge, value] : allEdge) {
        auto [from, to] = edge;
        out << "\t" << from << "->" << to
            << " [label = " << value << "];" << std::endl;
    }
    out << "}" << std::endl;
    out.close();

    std::string tmp = "dot -Tpng tmp.dot -o " + path;
    system(tmp.c_str());
    remove("tmp.dot");
}

std::string connect(const std::string& acc, const std::string& num) {
    return acc + num + ", ";
}
std::string queryBridgeWords(const std::string& word1,
    const std::string& word2) {
    // 查询桥接词函数：
    // 输入为有向图和查询桥接词的两个单词
    // 返回值为桥接词查询结果
    int index1 = G.findIndex(word1), index2 = G.findIndex(word2);
    std::string tmp = "";
    if (index1 == -1 || index2 == -1) {
        if (index1 == -1 && index2 == -1) {
            tmp = "No \'" + word1 + "\' and \'"
                + word2 + "\' in the graph! ";
        } else if (index1 == -1) {
            tmp = "No \'" + word1 + "\' in the graph! ";
        } else if (index2 == -1) {
            tmp = "No \'" + word2 + "\' in the graph! ";
        }
    } else {
        auto wordList = G.findBridgeWords(word1, word2);
        switch (wordList.size()) {
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
                // for (auto word : wordList) tmp += word + ", ";
                tmp = std::accumulate(wordList.begin(),
                        wordList.end(), tmp, connect);
                tmp[tmp.size() - 2] = '.';
                break;
        }
    }
    return tmp;
}

std::string generateNewText(const std::string& path) {
    // 根据桥接词生成新文本函数：
    // 输入为文本串路径
    // 如果两个单词无桥接词，则保持不变
    // 如果两个单词之间存在多个桥接词，
    // 则随机从中选择一个插入进去形成新文本
    // 返回值为新生成的文本串

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: File not open! " << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    std::vector<std::string> wordList = textPreprocess(content);

    std::string output = "";
    for (int i = 0, wordNumber = wordList.size(); i < wordNumber; i++) {
        output += wordList[i];
        if (i < wordNumber - 1) {
            std::string bridgeWord = G.randomBridgeWords(
                wordList[i], wordList[i + 1]);
            if (bridgeWord != "") output += " " + bridgeWord;
            output += " ";
        }
    }
    return output;
}


std::vector<int> Graph::shortestPath(int index) {
    // 求最短路函数：
    // 输入为起点单词编号
    // 返回值为起点单词到各个单词的最短路长度
    std::vector<int> dis(this->vertexNumber, -1);
    dis[index] = 0;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
    q.push(mp(0, index));
    std::vector<bool> vis(this->vertexNumber, false);
    while (q.size()) {
        auto [d, x] = q.top(); q.pop();
        if (vis[x]) continue;
        vis[x] = true;
        for (auto [y, z] : this->Edge[x]) {
            if (dis[y] == -1 || dis[x] + z < dis[y]) {
                dis[y] = dis[x] + z;
                q.push(mp(dis[y], y));
            }
        }
    }
    return dis;
}
void calcShortestPath1(const std::string& word1, const std::string& word2) {
    // 计算两个单词之间的最短路径函数：
    // 输入为两个单词
    // 提示两个单词不可达
    // 或者在文件 shortestPath.txt 中输出所有最短路
    // 并且在图片 shortestPath.png 展示其中一条
    int index1 = G.findIndex(word1);
    int index2 = G.findIndex(word2);
    if (index1 == -1 || index2 == -1) {
        std::cerr << "unreachable" << std::endl;
        return;
    }

    std::vector<int> dis = G.shortestPath(index1);
    if (dis[index2] == -1) {
        std::cerr << "unreachable" << std::endl;
        return;
    }
    std::vector<std::vector<int>> pre(G.getVertexNumber(), std::vector<int>());
    auto allEdge = G.getAllEdge();
    for (auto [edge, value] : allEdge) {
        auto [fromWord, toWord] = edge;
        int from = G.findIndex(fromWord);
        int to = G.findIndex(toWord);
        if (dis[from] + value == dis[to]) pre[to].pb(from);
    }

    // 记录所有路径到 shortestPath.txt
    std::ofstream out("shortestPath.txt", std::ios::out);
    out << "Shortest Path from \'" << word1
        << "\' to \'" << word2 << "\': " << std::endl;

    std::function<void(int, const std::string&)> getShortestPath = [&](
        int now, const std::string& path)->void {
        if (now == index1) {
            out << path << std::endl;
            return;
        }
        for (auto lst : pre[now]) {
            getShortestPath(lst, G.findWord(lst) + "->" + path);
        }
    };
    getShortestPath(index2, word2);

    out.close();

    // 展示其中一条路径到 shortestPath.png
    std::ofstream ouf("tmp.dot", std::ios::out);
    ouf << "digraph G {" << std::endl;

    std::set<pii> path;
    for (int now = index2, lst; now != index1; now = lst) {
        lst = pre[now][0];
        path.insert(mp(lst, now));
    }
    for (auto [edge, value] : allEdge) {
        auto [fromWord, toWord] = edge;
        int from = G.findIndex(fromWord);
        int to = G.findIndex(toWord);
        if (path.find(mp(from, to)) == path.end())
            ouf << fromWord << "->" << toWord << " [label = "
                << value << "];" << std::endl;
        else
            ouf << fromWord << "->" << toWord << " [label = "
                << value << ", color = red];" << std::endl;
    }
    ouf << "}" << std::endl;
    ouf.close();

    std::string tmp = "dot -Tpng tmp.dot -o shortestPath.png";
    system(tmp.c_str());
    remove("tmp.dot");
}
void calcShortestPath2(const std::string& word) {
    // 计算单词到所有单词的最短路径函数：
    // 输入为一个单词
    // 在文件 shortestPathAll.txt 中输出所有最短路
    int index = G.findIndex(word);
    if (index == -1) {
        std::cerr << "Word not exists" << std::endl;
        return;
    }

    std::vector<int> dis = G.shortestPath(index);
    std::vector<std::vector<int>> pre(G.getVertexNumber(), std::vector<int>());
    auto allEdge = G.getAllEdge();
    for (auto [edge, value] : allEdge) {
        auto [fromWord, toWord] = edge;
        int from = G.findIndex(fromWord);
        int to = G.findIndex(toWord);
        if (dis[from] + value == dis[to]) pre[to].pb(from);
    }


    std::ofstream out("shortestPathAll.txt", std::ios::out);

    std::function<void(int, const std::string&)> getShortestPath = [&](
        int now, const std::string& path)->void {
        if (now == index) {
            out << path << std::endl;
            return;
        }
        for (auto lst : pre[now]) {
            getShortestPath(lst, G.findWord(lst) + "->" + path);
        }
    };

    for (int i = 0, n = G.getVertexNumber(); i < n; i++) {
        if (i == index) continue;
        std::string word2 = G.findWord(i);
        out << "Shortest Path from \'" << word
            << "\' to \'" << word2 << "\': " << std::endl;
        getShortestPath(i, word2);
        out << std::endl;
    }
    out.close();
}


int Graph::randomNextNodeIndex(int index) {
    // 随机取下一个单词编号函数：
    // 输入为当前单词编号
    // 在这个单词所有出边中随机选择一条出边
    // 返回值为选中的出边指向的单词的编号
    // 若没有出边，则返回 -1
    if (!Edge[index].size()) return -1;
    return Edge[index][randomInt(0, Edge[index].size() - 1)].first;
}
std::string randomWalk() {
    // 随机游走函数：
    // 程序随机的从图中选择一个节点，
    // 以此为起点沿出边进行随机遍历，
    // 记录经过的所有节点和边，
    // 直到出现第一条重复的边为止，
    // 或者进入的某个节点不存在出边为止。
    // 在遍历过程中，用户也可随时停止遍历。
    int index = randomInt(0, G.getVertexNumber() - 1);
    std::string walkList = G.findWord(index);
    std::set<pii> edgeExist;
    while (1) {
        int nextIndex = G.randomNextNodeIndex(index);
        if (nextIndex == -1) break;
        walkList += "->" + G.findWord(nextIndex);
        if (edgeExist.find(mp(index, nextIndex))
            != edgeExist.end()) break;
        edgeExist.insert(mp(index, nextIndex));
        index = nextIndex;
    }
    return walkList;
}
