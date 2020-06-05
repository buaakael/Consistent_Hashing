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
    //增加新的存储节点
    bool addNode(std::string nodeName, int vNum);
    //删除现有存储节点
    bool delNode(std::string nodeName);
    //导入文件进行存储
    bool addFile(std::string fileName);
    //删除存储的文件
    bool delFile(std::string fileName);
    //查询单个文件存储在那个节点上
    std::string getServerName(std::string fileName);
    //获取节点负载情况
    std::string showLoadCondition();
    //获取真实节点个数
    int getRealNum();
    //获取某个真实节点的虚拟节点个数
    int getVirNum(std::string serName);
    //获取所有节点数量
    int getAllNodeNum();
    //打印节点信息
    std::string showNode();
    //打印文件信息
    std::string showFile();
    //打印文件所在节点信息
    std::string showFileAtNode();
private:
    bool addRealNode(Node *node);
    bool addVirNode(Node *node);
    bool delRealNode(Node *node);
    bool delVirNode(Node *node);

    Node* findRealNode(std::string &nodeName);
private:
    std::multimap<unsigned, std::string> allNode;//保存哈希值与存储节点的映射
    std::multimap<unsigned, std::string> allFile;//保存哈希值与文件的映射
    std::multimap<std::string, std::string> fileAtNode;//保存文件名与文件存储节点的映射
    std::map<std::string, unsigned> nodeLoad;//保存存储节点与对应存储文件数的关系
    std::list<Node *> realNode;
    HashFunc *hashFunc;
};


#endif
