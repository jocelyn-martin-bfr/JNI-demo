#include "jobjectsconversions.hpp"
#include "enumsindexes.hpp"
#include "util.hpp"
#include <list>
#include <sstream>
#include <string>
#include <vector>

namespace {
    std::string
    _getStringFromMethod(JNIEnv *pEnv, jclass pClass, jobject pOjbect, const char *pFunctionName) {
        jmethodID getFun = pEnv->GetMethodID(pClass, pFunctionName, "()Ljava/lang/String;");
        auto jStr = reinterpret_cast<jstring>(pEnv->CallObjectMethod(pOjbect, getFun));
        return toString(pEnv, jStr);
    }

    /**
 * Convert a jobject to an enum value.
 * @param env JNI environment.
 * @param jobj jobject.
 * @param enumClassName Name of the java enum.
 * @param javaOrdinalToCpp Indexes from java orinal to cpp enum values.
 */
    template<typename ENUM_TYPE>
    ENUM_TYPE _toEnum(
            JNIEnv *env,
            jobject exampleOfEnumJobj,
            const std::string &enumClassName,
            const std::vector<ENUM_TYPE> &javaOrdinalToCpp) {
        // Get the ordinal
        jclass enumClass = env->FindClass(enumClassName.c_str());
        jmethodID ordinalFun = env->GetMethodID(enumClass, "ordinal", "()I");
        int ordinal = env->CallIntMethod(exampleOfEnumJobj, ordinalFun);
        // Report if the ordinal is not valid
        if (ordinal < 0 || ordinal >= javaOrdinalToCpp.size()) {
            std::stringstream ss;
            ss << "invalid " << enumClassName << " ordinal " << ordinal;
            throw std::runtime_error(ss.str());
        }
        // Return the corresponding enum value
        return javaOrdinalToCpp[ordinal];
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


jint getIdOfDisposableWithId(JNIEnv *env, jobject object) {
    jclass semanticMemoryClass = env->FindClass("com/bfr/buddy/jnidemo/DisposableWithId");
    jmethodID getIdFun = env->GetMethodID(semanticMemoryClass, "getId", "()I");
    return env->CallIntMethod(object, getIdFun);
}


ExampleOfEnum toExampleOfEnum(
        JNIEnv *env,
        jobject exampleOfEnumJobj,
        const SemanticEnumsIndexes &pSemanticEnumsIndexes) {
    return _toEnum(env, exampleOfEnumJobj, pSemanticEnumsIndexes.exampleOfEnumClassName,
                   pSemanticEnumsIndexes.javaOrdinalExampleOfEnumToCpp);
}
