#ifndef JNI_DEMO_ANDROID_EXAMPLEOFENUM_HPP
#define JNI_DEMO_ANDROID_EXAMPLEOFENUM_HPP

#include <map>
#include <vector>
#include <string>


#define EXAMPLEOFENUM_TABLE                                          \
  ADD_EXAMPLEOFENUM(VALUE_1, "VALUE_1")                              \
  ADD_EXAMPLEOFENUM(VALUE_2, "VALUE_2")


#define ADD_EXAMPLEOFENUM(a, b) a,
enum class ExampleOfEnum
{
    EXAMPLEOFENUM_TABLE
};
#undef ADD_EXAMPLEOFENUM




#define ADD_EXAMPLEOFENUM(a, b) b,
static const std::vector<std::string> _exampleOfEnum_toStr = {
        EXAMPLEOFENUM_TABLE
};
#undef ADD_EXAMPLEOFENUM

#define ADD_EXAMPLEOFENUM(a, b) {b, ExampleOfEnum::a},
static const std::map<std::string, ExampleOfEnum> _exampleOfEnum_fromStr = {
        EXAMPLEOFENUM_TABLE
};
#undef ADD_EXAMPLEOFENUM


static inline ExampleOfEnum semanticVerbTense_fromStr(const std::string& pExampleOfEnumStr)
{
    auto it = _exampleOfEnum_fromStr.find(pExampleOfEnumStr);
    if (it != _exampleOfEnum_fromStr.end())
        return it->second;
    assert(false);
    return ExampleOfEnum::VALUE_1;
}

static inline std::string semanticVerbTense_toStr(ExampleOfEnum pExampleOfEnum)
{
    return _exampleOfEnum_toStr[static_cast<char>(pExampleOfEnum)];
}


#endif // JNI_DEMO_ANDROID_EXAMPLEOFENUM_HPP
