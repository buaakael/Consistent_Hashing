#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "HashFunc.h"
#include "FNVHashFunc.h"

void printVector(const std::vector<unsigned> &key, const std::vector<std::string> &value)
{
    for (int i = 0; i < key.size() && i < value.size(); ++i)
    {
        std::cout << "key " << key[i] << " 对应的string为 " << value[i] << std::endl;
    }
}

int main()
{
    HashFunc *hashFunc = new FNVHashFunc();
    std::map<unsigned, unsigned> m_save;
    std::map<unsigned, std::string> m_mapping;
    std::vector<std::string> node = {"192.168.1.1", "192.168.1.2", "192.168.1.3", "192.168.1.4"};
    std::vector<std::string> file = {"a.csv", "b.csv", "数据1.txt", "数据2.txt"};
    std::vector<unsigned> node_key;
    std::vector<unsigned> file_key;
    for (int i = 0; i < node.size(); ++i)
    {
        node_key.push_back(hashFunc->GetKey(node[i]));
    }
    for (int i = 0; i < file.size(); ++i)
    {
        file_key.push_back(hashFunc->GetKey(file[i]));
    }
    printVector(node_key, node);
    printVector(file_key, file);
}
