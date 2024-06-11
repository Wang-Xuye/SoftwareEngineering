// Copyright 2024 wangxuye

#include "include/random.h"
#include "include/graph.h"

extern Graph G;

int main(int argc, char* argv[]) {
    if (argc != 1) {
        perror("parameters error\n");
        exit(1);
    }
    std::cerr << "Please input the path of the content file: ";
    // std::cerr << "请输入文本串所在文件路径：";
    std::string path; std::cin >> path;
    while (1) {
        std::ifstream file(path);
        if (file.is_open()) break;
        std::cerr << "Please reinput the path of the content file: ";
        // std::cerr << "请重新输入文本串所在文件路径：";
        std::cin >> path;
    }
    G = Graph(path);

    system("clear");
    std::cerr << "Introduction: " << std::endl;
    std::cerr << "graph: Show digraph" << std::endl;
    std::cerr << "bridge word1 word2: Look for bridge words" << std::endl;
    std::cerr << "generate path: generate new content "
                 "according to bridge words" << std::endl;
    std::cerr << "short1 word1 word2: Look for the shortest path "
                 "between two words" << std::endl;
    std::cerr << "short2 word: Look for the shortest path "
                 "from the word to other words" << std::endl;
    std::cerr << "walk: Random walk" << std::endl;
    std::cerr << "exit: Exit" << std::endl;
    // std::cerr << "功能介绍：" << std::endl;
    // std::cerr << "graph: 查看有向图" << std::endl;
    // std::cerr << "bridge word1 word2: 查询桥接词" << std::endl;
    // std::cerr << "generate path: 根据桥接词生成文本" << std::endl;
    // std::cerr << "short1 word1 word2: "\
                    "查询两个单词之间的最短路径" << std::endl;
    // std::cerr << "short2 word: 查询单词到所有单词的最短路径" << std::endl;
    // std::cerr << "walk: 随机游走" << std::endl;
    // std::cerr << "exit: 退出" << std::endl;

    std::string cmd;
    while (1) {
        std::cerr << ">>> ";
        std::cin >> cmd;
        if (cmd == "exit") {
            break;
        } else if (cmd == "graph") {
            showDirectedGraph("graph.png");
        } else if (cmd == "bridge") {
            std::string word1, word2;
            std::cin >> word1 >> word2;
            std::cerr << queryBridgeWords(word1, word2) << std::endl;
        } else if (cmd == "generate") {
            std::string genPath;
            std::cin >> genPath;
            std::cerr << generateNewText(genPath) << std::endl;
        } else if (cmd == "short1") {
            std::string word1, word2;
            std::cin >> word1 >> word2;
            calcShortestPath1(word1, word2);
        } else if (cmd == "short2") {
            std::string word;
            std::cin >> word;
            calcShortestPath2(word);
        } else if (cmd == "walk") {
            std::cerr << randomWalk() << std::endl;
        } else {
            std::cerr << "Command \'" << cmd << "\' not found" << std::endl;
        }
    }
    return 0;
}
