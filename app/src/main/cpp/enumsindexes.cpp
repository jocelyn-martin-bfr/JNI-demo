#include "enumsindexes.hpp"
#include "jobjectsconversions.hpp"
#include <sstream>
#include <map>


namespace {
    static const std::map<std::string, ExampleOfEnum> _javaToCppPartOfExampleOfEnum{
            {"VALUE_1",         ExampleOfEnum::VALUE_1},
            {"VALUE_2",         ExampleOfEnum::VALUE_2}
    };

    int _getOrdinal(
            JNIEnv *env,
            jclass pJClass,
            const char *pEnumValue,
            const char *pClassNameReturnType,
            jmethodID ordinalFun) {
        jfieldID enumField = env->GetStaticFieldID(pJClass, pEnumValue, pClassNameReturnType);
        shared_jobject enumObject(env, env->GetStaticObjectField(pJClass, enumField));
        return env->CallIntMethod(enumObject.get(), ordinalFun);
    }

    template<typename ENUM_TYPE>
    std::vector<ENUM_TYPE> _getVectorOfCppEnumValues(
            JNIEnv *env,
            const std::string &enumClassName,
            const std::map<std::string, ENUM_TYPE> &pJavaEnumValuesToCppEnumValues) {
        std::stringstream enumClassNameReturnTypeSs;
        enumClassNameReturnTypeSs << "L" << enumClassName << ";";
        auto enumClassNameReturnTypeStr = enumClassNameReturnTypeSs.str();
        const char *enumClassNameReturnType = enumClassNameReturnTypeStr.c_str();
        jclass enumClass = env->FindClass(enumClassName.c_str());
        jmethodID ordinalFun = env->GetMethodID(enumClass, "ordinal", "()I");

        auto map = std::map<int, ENUM_TYPE>();
        for (const auto &currElt : pJavaEnumValuesToCppEnumValues)
            map.emplace(_getOrdinal(env, enumClass, currElt.first.c_str(),
                                    enumClassNameReturnType,
                                    ordinalFun), currElt.second);
        std::vector<ENUM_TYPE> res(map.size());
        int currentIndex = 0;
        for (const auto &currElt : map) {
            if (currElt.first != currentIndex) {
                std::stringstream ss;
                ss << "the mapping of an enum of " << enumClassName
                   << " from java to cpp is missing. Or the ordinals of "
                   << enumClassName << " are not from 0 to x without any gap";
                throw std::runtime_error(ss.str());
            }
            res[currentIndex++] = currElt.second;
        }
        return res;
    }
}


SemanticEnumsIndexes::SemanticEnumsIndexes(JNIEnv *env)
        : exampleOfEnumClassName("com/bfr/buddy/jnidemo/ExampleOfEnum"),
          javaOrdinalExampleOfEnumToCpp(
                  _getVectorOfCppEnumValues(env,
                                            exampleOfEnumClassName,
                                            _javaToCppPartOfExampleOfEnum)) {
}


const SemanticEnumsIndexes &getSemanticEnumsIndexes(JNIEnv *env) {
    static std::map<JNIEnv *, SemanticEnumsIndexes> envToIndexes;
    auto it = envToIndexes.find(env);
    if (it != envToIndexes.end())
        return it->second;
    return envToIndexes.emplace(env, SemanticEnumsIndexes(env)).first->second;
}