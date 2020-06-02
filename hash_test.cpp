#include <iostream>
#include <string>
#include <map>
using namespace std;

size_t ipToHash(string IP)
{
    string temp;
    size_t a[4];
    size_t pos;
    size_t i = 3;
    while (1)
    {
        pos = IP.find(".");
        if (pos != string::npos)
        {
            temp = IP.substr(0, pos);
//            cout << temp << endl;
            a[i] = atoi(temp.c_str());
            i--;
            IP.erase(0, pos + 1);
        }
        else
        {
            temp = IP;
//            cout << temp << endl;
            a[i] = atoi(temp.c_str());
            break;
        }
    }
//    cout << a[3] << " " << a[2] << " " << a[1] << " " << a[0] << endl;
    size_t result = (a[3] << 24) + (a[2] << 16) + (a[1] << 8) + a[0];
    return result;
}

int main(int argc, char* argv[])
{
    map<string, size_t> ch;
    string IP;
    size_t hash;
    while (cin >> IP)
    {
        hash = ipToHash(IP) % (0xffffffff - 1);
//        cout << hash << endl;
        ch.insert(make_pair(IP, hash));
    }
    for (map<string, size_t>::const_iterator it = ch.begin(); it != ch.end(); it++)
    {
        cout << "输入的IP地址为" << it->first << "\t映射的哈希值为" << it->second << endl;
    }
}

