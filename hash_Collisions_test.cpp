#include <iostream>
#include <vector>
//#include <string>
#include "HashFunc.h"
#include "FNVHashFunc.h"
#include <sstream>
#include <set>

int main()
{
    //实例化哈希函数
    HashFunc *hashFunc = new FNVHashFunc();
    std::vector<std::string> file;
    std::vector<unsigned> hash;
    std::stringstream ss;
    std::string file_name;
    std::set<unsigned> hash_set;
    std::cout << "创建文件名数组" << std::endl;
    for (int i = 0; i < 10000; ++i)
    {
        ss << i + 1 << ".csv";
        ss >> file_name;
        ss.clear();
        file.push_back(file_name);
    }
    std::cout << "创建文件名的hash数组" << std::endl;
    for (int i = 0; i < file.size(); ++i)
    {
        hash.push_back(hashFunc->GetKey(file[i]));
    }
    std::cout << "把hash数组放入set中，查重" << std::endl;
    for (int i = 0; i < hash.size(); ++i)
    {
        hash_set.insert(hash[i]);
    }
    std::cout << "hash数组共 " << hash.size() << "个元素" << std::endl;
    std::cout << "hash_set数组共 " << hash_set.size() << "个元素" << std::endl;
}
