#ifndef HASHFUNC_H
#define HASHFUNC_H
#include "HashFunc.h"

class FNVHashFunc : public HashFunc
{
public:
    virtual unsigned GetKey(std::string key) override;
};

#endif
