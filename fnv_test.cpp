#include <iostream>
#include <string>
using namespace std;

unsigned FNV32Hash(string key)
{
    const unsigned p = 16777619;
    unsigned hash = 2166136261;
    for (int i = 0; i < key.size(); ++i)
    {
        hash = (hash ^ key[i]) * p;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    return hash;
}

int main(int argc, char* argv[])
{
    string str1("192.168.1.1");
    string str2("192.168.1.2");
    string str3("192.168.1.3");
    string str4("192.168.1.4");
    string str5("a.csv");
    string str6("b.csv");
    string str7("数据1.txt");
    string str8("数据2.txt");
    cout << str1 << "\t的FNV哈希值为" << FNV32Hash(str1) << endl;
    cout << str2 << "\t的FNV哈希值为" << FNV32Hash(str2) << endl;
    cout << str3 << "\t的FNV哈希值为" << FNV32Hash(str3) << endl;
    cout << str4 << "\t的FNV哈希值为" << FNV32Hash(str4) << endl;
    cout << str5 << "\t\t的FNV哈希值为" << FNV32Hash(str5) << endl;
    cout << str6 << "\t\t的FNV哈希值为" << FNV32Hash(str6) << endl;
    cout << str7 << "\t的FNV哈希值为" << FNV32Hash(str7) << endl;
    cout << str8 << "\t的FNV哈希值为" << FNV32Hash(str8) << endl;
}
