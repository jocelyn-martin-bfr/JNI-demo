#include "jobjectsconversions.hpp"
#include <list>
#include <sstream>


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


jint toDisposableWithIdId(JNIEnv *env, jobject object) {
    jclass semanticMemoryClass = env->FindClass("com/bfr/planner/DisposableWithId");
    jmethodID getIdFun = env->GetMethodID(semanticMemoryClass, "getId", "()I");
    return env->CallIntMethod(object, getIdFun);
}

