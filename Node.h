#ifndef NODE_H
#define NODE_H

#include <string>

class Node
{
public:
    Node(std::string name, int num) : nodeName(name), vNodeNum(num) { }
    ~Node()
    {}
    int GetVNodeNum()
    {
        return vNodeNum;
    }
    std::string GetNodeName()
    {
        return nodeName;
    }
private:
    std::string nodeName;//节点名字，即服务器名字（例如IP，或者编号等）
    int vNodeNum;//虚拟节点个数
};
#endif
