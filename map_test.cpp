#include <iostream>
#include <map>
#include <vector>
//#include <string>
#include "HashFunc.h"
#include "FNVHashFunc.h"
#include <sstream>

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
    std::map<unsigned, std::string> m_node;
    std::map<unsigned, std::string> m_mapping;
    std::vector<std::string> node = {"192.168.1.1", "192.168.1.2", "192.168.1.3", "192.168.1.4", "192.168.1.5", "192.168.1.6", "192.168.1.7"};
    std::vector<std::string> file;
    std::stringstream ss;
    std::string file_name;
    for (int i = 0; i < 10000; ++i)
    {
        ss << i + 1 << ".csv";
        ss >> file_name;
        ss.clear();
        file.push_back(file_name);
    }
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
    for (int i = 0; i < node_key.size(); ++i)
    {
        m_node.insert(std::make_pair(node_key[i], node[i]));
    }

    for (int i = 0; i < file_key.size(); ++i)
    {
        m_mapping.insert(std::make_pair(file_key[i], file[i]));
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
    std::cout << std::endl;
    for (auto it = m_save.begin(); it != m_save.end(); ++it)
    {
        std::cout << m_node[it->first] << " " << it->second << std::endl;
    }
}
