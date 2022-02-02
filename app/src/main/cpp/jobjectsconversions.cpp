#include "jobjectsconversions.hpp"
#include <list>
#include <sstream>
#include <string>
#include <vector>

namespace {
    std::string _getStringFromMethod(JNIEnv *pEnv, jclass pClass, jobject pOjbect, const char * pFunctionName)
    {
        jmethodID getFun = pEnv->GetMethodID(pClass, pFunctionName, "()Ljava/lang/String;");
        auto jStr = reinterpret_cast<jstring>(pEnv->CallObjectMethod(pOjbect, getFun));
        return toString(pEnv, jStr);
    }
}


std::string toString(JNIEnv *env, jstring inputString) {
    if (env == nullptr)
        return "";
    const char *cstring;
    if (!(cstring = env->GetStringUTFChars(inputString, nullptr)))
        return "";
    std::string string = cstring;
    env->ReleaseStringUTFChars(inputString, cstring);
    return string;
}

jobjectArray tojstringArray(JNIEnv *env, const std::vector<std::string> &pStrs) {
    jobjectArray result;
    result = (jobjectArray) env->NewObjectArray(pStrs.size(),
                                                env->FindClass("java/lang/String"),
                                                env->NewStringUTF(""));

    jsize arrayElt = 0;
    for (const auto &currStr : pStrs)
        env->SetObjectArrayElement(result, arrayElt++,
                                   env->NewStringUTF(currStr.c_str()));
    return result;
}


jint toDisposableWithIdId(JNIEnv *env, jobject object) {
    jclass semanticMemoryClass = env->FindClass("com/bfr/planner/DisposableWithId");
    jmethodID getIdFun = env->GetMethodID(semanticMemoryClass, "getId", "()I");
    return env->CallIntMethod(object, getIdFun);
}

