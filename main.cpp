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
    for (auto it = nodeName.begin(); it != nodeName.end(); ++it)
    {
        cssHash.addNode(*it, 50);
    }
    for (int i = 0; i < 1000; ++i)
    {
        ss << i + 1 << ".csv";
        ss >> fileName;
        ss.clear();
        cssHash.addFile(fileName);
    }
    std::cout << cssHash.showNode() << std::endl;
    std::cout << cssHash.showFile() << std::endl;
    std::cout << cssHash.showLoadCondition() << std::endl;
    return 0;
}
