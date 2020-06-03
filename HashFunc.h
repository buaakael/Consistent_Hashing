#ifndef HASHFUNC_H
#define HASHFUNC_H

#include<string>

class HashFunc
{
public:
    virtual unsigned GetKey(std::string key) = 0;
};
#endif
