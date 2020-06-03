#ifndef FNVHASHFUNC_H
#define FNVHASHFUNC_H
#include <string>
#include "HashFunc.h"

class FNVHashFunc : public HashFunc
{
public:
    unsigned GetKey(std::string key);
};
#endif
