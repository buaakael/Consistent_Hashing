#include <iostream>
#include <map>
#include <vector>
//#include <string>
#include "HashFunc.h"
#include "FNVHashFunc.h"

void printVector(const std::vector<unsigned> &key, const std::vector<std::string> &value)
{
    for (int i = 0; i < key.size() && i < value.size(); ++i)
    {
        std::cout << "key " << key[i] << " 对应的string为 " << value[i] << std::endl;
    }
}

void printMap(const std::map<unsigned, unsigned> &m_save, const std::map<unsigned, std::string> &m_mapping)
{
}

int main()
{
    //实例化哈希函数
    HashFunc *hashFunc = new FNVHashFunc();
    //建立存储节点与一致性哈希ID对应的pair
    std::map<unsigned, unsigned> m_save;
    //建立ID与文件名对应的pair
    std::map<unsigned, std::string> m_mapping;
    std::vector<std::string> node = {"192.168.1.1", "192.168.1.2", "192.168.1.3", "192.168.1.4"};
    std::vector<std::string> file = {"a.csv", "b.csv", "数据1.txt", "数据2.txt"};
    std::vector<unsigned> node_key;
    std::vector<unsigned> file_key;
    //用哈希函数生成ID
    for (int i = 0; i < node.size(); ++i)
    {
        node_key.push_back(hashFunc->GetKey(node[i]));
    }
    for (int i = 0; i < file.size(); ++i)
    {
        file_key.push_back(hashFunc->GetKey(file[i]));
    }
    //用生成的ID组成pair
    for (int i = 0; i < node_key.size(); ++i)
    {
        m_save.insert(std::make_pair(node_key[i], 0));
    }
    for (auto it = m_save.begin(); it != m_save.end(); ++it)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }

    for (int i = 0; i < file_key.size(); ++i)
    {
        m_mapping.insert(std::make_pair(file_key[i], file[i]));
    }
    for (auto it = m_mapping.begin(); it != m_mapping.end(); ++it)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
    auto it_node = m_save.begin();
    auto it_file = m_mapping.begin();
    while (it_file != m_mapping.end() && it_node != m_save.end())
    {
        if (it_file->first <= it_node->first)
        {
            m_save[it_node->first] = it_node->second + 1; 
            ++it_file;
        }
        else
        {
            ++it_node;
            if (it_node == m_save.end())
            {
                auto it = m_save.begin();
                while (it_file != m_mapping.end())
                {
                    m_save[it->first] = it->second + 1;
                    ++it_file;
                }
            }
        }

    }
    printVector(node_key, node);
    printVector(file_key, file);
    for (auto it = m_save.begin(); it != m_save.end(); ++it)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
}
