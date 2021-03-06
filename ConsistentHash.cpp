#include "ConsistentHash.h"

ConsistentHash::ConsistentHash(HashFunc *func)
{
    if (func)
    {
        hashFunc = func;
    }
    else
    {
        hashFunc = new FNVHashFunc();
    }
}

ConsistentHash::~ConsistentHash()
{
    for (auto it = realNode.begin(); it != realNode.end();)
    {
        delete *it;
        realNode.erase(it++);
    }
}

bool ConsistentHash::addNode(std::string nodeName, int vNum)
{
    Node *node = new Node(nodeName, vNum);
    if (!addVirNode(node))
        return false;
    if (!addRealNode(node))
        return false;
    //auto it = allFile.begin();
    //auto itn = allNode.begin();
    //while (it != allFile.end() && itn != allNode.end())
    //{
    //    if (
    //}
    return true;
}

bool ConsistentHash::delNode(std::string nodeName)
{
    //找到该节点
    Node *node = findRealNode(nodeName);
    //删除节点
    if (!delRealNode(node))
        return false;
    if (!delVirNode(node))
        return false;
    auto it = nodeLoad.find(node->GetNodeName());
    //unsigned count = it->second;
    nodeLoad.erase(it);
    for (auto itadd = fileAtNode.begin(); itadd != fileAtNode.end(); ++itadd)
    {
        if (itadd->second == nodeName)
        {
            addFile(itadd->first);
        }
    } 
    delete node;
    return true;
}

bool ConsistentHash::addRealNode(Node *node)
{
    if (!node)
        return false;
    std::string value = node->GetNodeName();
    unsigned key = hashFunc->GetKey(value);
    realNode.push_back(node);
    allNode.insert(std::make_pair(key, value));
    //自己修改的，标记一下
    nodeLoad.insert(std::make_pair(value, 0));
    
    return true;
}

bool ConsistentHash::addVirNode(Node *node)
{
    if (!node)
    {
        return false;
    }
    int vNum = node->GetVNodeNum();//获取节点对应的虚拟节点个数
    if (vNum < 1)
    {
        return false;
    }
    unsigned key;
    std::string virName;
    std::string nodeName = node->GetNodeName();//获取真实节点名
    std::stringstream ss;
    //vNode添加后缀
    for (int i = 0; i < vNum; ++i)
    {
        ss << nodeName << "##" << i + 1;
        ss >> virName;
        ss.clear();
        key = hashFunc->GetKey(virName);
        allNode.insert(std::make_pair(key, nodeName));
    }
    return true;
}

bool ConsistentHash::delRealNode(Node *node)
{
    if (!node)
    {
        return false;
    }
    std::string nodeName = node->GetNodeName();
    unsigned key = hashFunc->GetKey(nodeName);
    int count = allNode.count(key);
    auto delIt = allNode.find(key);
    while (delIt != allNode.end() && count--)
    {
        if (delIt->second == nodeName)
        {
            allNode.erase(delIt);
            break;
        }
        ++delIt;
    }
    return true;
}

bool ConsistentHash::delVirNode(Node *node)
{
    if (!node)
    {
        return false;
    }
    int vNum = node->GetVNodeNum();
    int count;
    unsigned key;
    std::string virName;
    std::string nodeName = node->GetNodeName();
    std::stringstream ss;
    //vNode添加后缀
    for (int i = 0; i < vNum; ++i)
    {
        ss << nodeName << "##" << i + 1;
        ss >> virName;
        ss.clear();
        key = hashFunc->GetKey(virName);
        count = allNode.count(key);
        auto delIt = allNode.find(key);
        while (delIt != allNode.end() && count--)
        {
            if (delIt->second == nodeName)
            {
                allNode.erase(delIt++);
            }
            else
            {
                ++delIt;
            }
        }
    }
    return true;
}

Node* ConsistentHash::findRealNode(std::string &nodeName)
{
    Node *node = nullptr;
    //先找到node 并在list中删除
    for (auto it = realNode.begin(); it != realNode.end(); ++it)
    {
        if ((*it)->GetNodeName() == nodeName)
        {
            node = *it;
            realNode.erase(it);
            break;
        }
    }
    if (!node)//没有找到真实节点
    {
    }
    return node;
}

bool ConsistentHash::addFile(std::string fileName)
{
    if (fileName.size() == 0)
    {
        return false;
    }
    std::string serName;
    unsigned fileKey = hashFunc->GetKey(fileName);
    allFile.insert(std::make_pair(fileKey, fileName));
    auto it = allNode.begin();
    while (it != allNode.end())
    {
        if (fileKey < it->first)
        {
            serName = it->second;
            break;
        }
        ++it;
    }
    if (it == allNode.end())
    {
        serName = allNode.begin()->second;
    }
    nodeLoad[serName]++;
    fileAtNode.insert(std::make_pair(fileName, serName));
    return true;
}

bool ConsistentHash::delFile(std::string fileName)
{
    std::string serName;
    unsigned fileKey = hashFunc->GetKey(fileName);
    int count = allFile.count(fileKey);
    if (count == 0)
    {
        return false;
    }
    auto delIt = allFile.find(fileKey);
    while (delIt != allFile.end() && count--)
    {
        if (delIt->second == fileName)
        {
            allFile.erase(delIt);
            break;
        }
        ++delIt;
    }
    auto delIt2 = fileAtNode.find(fileName);
    serName = delIt2->second;
    fileAtNode.erase(delIt2);
    //auto it = allNode.begin();
    //while (it != allNode.end())
    //{
    //    if (fileKey < it->first)
    //    {
    //        serName = it->second;
    //        break;
    //    }
    //    ++it;
    //}
    //if (it == allNode.end())
    //{
    //    serName = allNode.begin()->second;
    //}
    nodeLoad[serName]--;
    return true;
}

std::string ConsistentHash::getServerName(std::string fileName)
{
    //根据文件名找到其存储的节点
    std::string serName;
    unsigned fileKey = hashFunc->GetKey(fileName);
    auto it = allNode.begin();
    while (it != allNode.end())
    {
        if (fileKey < it->first)
        {
            serName = it->second;
            break;
        }
        ++it;
    }
    if (it == allNode.end())
    {
        serName = allNode.begin()->second;
    }
    return serName;
}

std::string ConsistentHash::showLoadCondition()
{
    std::ostringstream oss;
    for (auto it = nodeLoad.begin(); it != nodeLoad.end(); ++it)
    {
        oss << "node : " << it->first << "\tload : " << it->second << "\n"; 
    }
    return oss.str();
}

int ConsistentHash::getVirNum(std::string serName)
{
    Node *node = nullptr;
    for (auto it = realNode.begin(); it != realNode.end(); ++it)
    {
        if ((*it)->GetNodeName() == serName)
        {
            node = *it;
        }
    }
    if (!node)
        return -1;
    return node->GetVNodeNum();
}

int ConsistentHash::getRealNum()
{
    return realNode.size();
}

int ConsistentHash::getAllNodeNum()
{
    return allNode.size();
}

std::string ConsistentHash::showNode()
{
    std::ostringstream oss;
    for (auto it = allNode.begin(); it != allNode.end(); ++it)
    {
        oss << "key : " << it->first << "\tvalue : " << it->second << "\n"; 
    }
    return oss.str();
}

std::string ConsistentHash::showFile()
{
    std::ostringstream oss;
    for (auto it = allFile.begin(); it != allFile.end(); ++it)
    {
        oss << "key : " << it->first << "\tvalue : " << it->second << "\n"; 
    }
    return oss.str();
}

std::string ConsistentHash::showFileAtNode()
{
    std::ostringstream oss;
    for (auto it = fileAtNode.begin(); it != fileAtNode.end(); ++it)
    {
        oss << "file : " << it->first << "\tvalue : " << it->second << "\n"; 
    }
    return oss.str();
}








