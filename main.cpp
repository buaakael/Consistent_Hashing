#include <iostream>
#include <vector>
#include <algorithm>
#include "ConsistentHash.h"

int main(int argc, char* argv[])
{
    std::string fileName;
    std::stringstream ss;
    ConsistentHash cssHash;
    std::vector<std::string> nodeName;
    nodeName.push_back("192.168.1.1");
    nodeName.push_back("192.168.1.2");
    nodeName.push_back("192.168.1.3");
    nodeName.push_back("192.168.1.4");
    nodeName.push_back("192.168.1.5");
    nodeName.push_back("192.168.1.6");
    nodeName.push_back("192.168.1.7");
    nodeName.push_back("192.168.1.8");
    for (auto it = nodeName.begin(); it != nodeName.end(); ++it)
    {
        cssHash.addNode(*it, 100);
    }
    for (int i = 0; i < 100000; ++i)
    {
        ss << i + 1 << ".csv";
        ss >> fileName;
        ss.clear();
        cssHash.addFile(fileName);
    }
    //std::cout << cssHash.showNode() << std::endl;
    //std::cout << cssHash.showFile() << std::endl;
    std::cout << cssHash.showLoadCondition() << std::endl;
    std::cout << cssHash.getAllNodeNum() << std::endl;
    cssHash.delNode("192.168.1.1");
    std::cout << cssHash.showLoadCondition() << std::endl;
    std::cout << cssHash.getAllNodeNum() << std::endl;
    //std::cout << cssHash.showFileAtNode() << std::endl;
    return 0;
}
