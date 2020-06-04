#ifndef CONSISTENTHASH_H
#define CONSISTENTHASH_H

#include <map>
#include <list>
#include <string>
#include <vector>
#include <sstream>
#include "Node.h"
#include "HashFunc.h"
#include "FNVHashFunc.h"

class ConsistentHash
{
public:
    ConsistentHash(HashFunc *func = nullptr);
    ~ConsistentHash();
    bool addNode(std::string nodeName, int vNum);
    bool delNode(std::string nodeName);
    //根据client找对应的server
    std::string getServerName(std::string cliName);
    //获取真实节点个数
    int getRealNum();
    //获取某个真实节点的虚拟节点个数
    int getVirNum(std::string serName);
    //获取所有节点数量
    int getAllNodeNum();
    //打印节点
    std::string showTime();
private:
    bool addRealNode(Node *node);
    bool addVirNode(Node *node);
    bool delRealNode(Node *node);
    bool delVirNode(Node *node);

    Node* findRealNode(std::string &nodeName);
private:
    std::multimap<unsigned, std::string> allNode;//保存哈希值与存储节点的映射
    std::multimap<unsigned, std::string> allFile;//保存哈希值与文件的映射
    std::multimap<unsigned, unsigned> node2File;//保存存储节点与对应存储文件数的关系
    std::list<Node *> realNode;
    HashFunc *hashFunc;
};


#endif
