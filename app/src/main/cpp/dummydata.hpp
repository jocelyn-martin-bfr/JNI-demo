#ifndef JNIDEMO_DUMMYDATA_HPP
#define JNIDEMO_DUMMYDATA_HPP

#include "exampleofenum.hpp"

struct DummyData
{
    int i = 0;
    std::string str = "";
    ExampleOfEnum exampleOfEnum = ExampleOfEnum::VALUE_1;
};


#endif // JNIDEMO_DUMMYDATA_HPP
