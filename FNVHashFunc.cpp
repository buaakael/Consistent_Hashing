#include "FNVHashFunc.h"

unsigned FNVHashFunc::GetKey(std::string key)
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
