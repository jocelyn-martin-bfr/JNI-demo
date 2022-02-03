#include <regex>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <jni.h>
#include "androidlog.hpp"
#include "jobjectsconversions.hpp"
#include "dummydata.hpp"
#include "dummyobject.hpp"
#include "util.hpp"
#include "enumsindexes.hpp"

namespace {
    // Mutex to protect _idToDummyObject
    std::mutex _idToDummyObjectMutex;

    // Map of id to Cpp DummyObject
    std::map<jint, DummyObject> _idToDummyObject;
}


jint JNI_OnLoad(JavaVM *vm, void *reserved) {
#ifdef COUT_TO_ANDROID_LOG
    // Also initialize the forwarding of logs to Android.
    std::cout.rdbuf(new forward_to_android);
    // TODO: write this in a way that does not leak and does not conflict with other libraries
#endif // COUT_TO_ANDROID_LOG
    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_bfr_buddy_jnidemo_MainActivity_returnFortyTwo(
        JNIEnv *env, jclass /*clazz*/) {
    std::cout << "log from cpp" << std::endl;
    return 42;
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_bfr_buddy_jnidemo_MainActivity_addFortyTwo(
        JNIEnv *env, jclass /*clazz*/, jint value) {
    std::cout << "log from cpp" << std::endl;
    return value + 42;
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_bfr_buddy_jnidemo_MainActivity_returnString(
        JNIEnv *env, jclass /*clazz*/) {
    std::string result = "love";
    return env->NewStringUTF(result.c_str());
}


extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_bfr_buddy_jnidemo_MainActivity_returnStringArray(
        JNIEnv *env, jclass /*clazz*/) {
    return tojstringArray(env, {"titi", "toto"});
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_bfr_buddy_jnidemo_MainActivity_readCustomData(
        JNIEnv *env, jclass /*clazz*/, jobject jDummyData) {

    DummyData dummyData;

    // Get the Java class
    jclass dummyDataClass = env->FindClass(
            "com/bfr/buddy/jnidemo/DummyData");

    // Fill i attribute
    {
        jmethodID getIFun = env->GetMethodID(dummyDataClass,
                                             "getI", "()I");
        dummyData.i = env->CallIntMethod(jDummyData, getIFun) + 1;
    }

    // Fill str attribute
    {
        jmethodID getStrFun = env->GetMethodID(dummyDataClass,
                                             "getStr", "()Ljava/lang/String;");
        auto dummyDataJstr = reinterpret_cast<jstring>(env->CallObjectMethod(jDummyData, getStrFun));
        dummyData.str = toString(env, dummyDataJstr) + "_cpp_addition";
    }

    // Fill str attribute
    {
        jmethodID getExampleOfEnumFun = env->GetMethodID(dummyDataClass,
                                                         "getExampleOfEnum",
                                                         "()Lcom/bfr/buddy/jnidemo/ExampleOfEnum;");
        dummyData.exampleOfEnum = toExampleOfEnum(env, env->CallObjectMethod(jDummyData, getExampleOfEnumFun),
                                                  getSemanticEnumsIndexes(env));
    }

    jclass ExampleOfEnumClass    = env->FindClass("com/bfr/buddy/jnidemo/ExampleOfEnum");
    jfieldID enumField    = env->GetStaticFieldID(ExampleOfEnumClass , semanticVerbTense_toStr(dummyData.exampleOfEnum).c_str(),
                                               "Lcom/bfr/buddy/jnidemo/ExampleOfEnum;");
    jobject enumValue = env->GetStaticObjectField(ExampleOfEnumClass, enumField);


    // Convert the Cpp struct to the Java class and return the Java class
    jmethodID dummyDataClassConstructor =
            env->GetMethodID(dummyDataClass, "<init>",
                             "(ILjava/lang/String;Lcom/bfr/buddy/jnidemo/ExampleOfEnum;)V");
    return env->NewObject(dummyDataClass, dummyDataClassConstructor, dummyData.i, env->NewStringUTF(dummyData.str.c_str()), enumValue);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_bfr_buddy_jnidemo_MainActivity_throwFromCpp(
        JNIEnv *env, jclass /*clazz*/) {
    convertCppExceptionsToJavaExceptions(env, []{
            throw std::runtime_error("Cpp exception!");
    });
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_bfr_buddy_jnidemo_MainActivity_throwFromCppWithReturn(
        JNIEnv *env, jclass /*clazz*/, jint value) {
    return convertCppExceptionsToJavaExceptionsAndReturnTheResult<int>(env, [&]{
        if (value < 0)
          throw std::runtime_error("Value must not be negative");
        return value + 1;
    }, 0); // A default value should be specified even if it will not be used because the Cpp flow will not be stopped.
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_bfr_buddy_jnidemo_MainActivity_createCustomObject(
        JNIEnv *env, jclass /*clazz*/, jint value) {
    std::lock_guard<std::mutex> lock(_idToDummyObjectMutex);

    // Construct the Cpp object
    DummyObject dummyObject;
    dummyObject.load(value);

    // Get the Java class
    jclass dummyObjectClass = env->FindClass(
            "com/bfr/buddy/jnidemo/DummyObject");

    // get an unique id
    jint newId = findMissingKey(_idToDummyObject);

    // Link the id with the Cpp object
    _idToDummyObject.emplace(newId, std::move(dummyObject));

    // Convert the Cpp struct to the Java class and return the Java class
    jmethodID dummyObjectClassConstructor =
            env->GetMethodID(dummyObjectClass, "<init>", "(I)V");
    return env->NewObject(dummyObjectClass, dummyObjectClassConstructor, newId);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_bfr_buddy_jnidemo_DummyObject_disposeImplementation(
        JNIEnv *env, jobject jDummyObject) {
    convertCppExceptionsToJavaExceptions(env, [&]{
        std::lock_guard<std::mutex> lock(_idToDummyObjectMutex);

        // Get the Java class
        jclass disposableWithIdClass = env->FindClass(
                "com/bfr/buddy/jnidemo/DisposableWithId");

        // Get the getId function
        jmethodID getIdFun = env->GetMethodID(disposableWithIdClass,
                                              "getId", "()I");

        auto id = env->CallIntMethod(jDummyObject, getIdFun);
        auto it = _idToDummyObject.find(id);
        if (it != _idToDummyObject.end())
        {
            it->second.unload();
            _idToDummyObject.erase(it);
            return;
        }

        throw std::runtime_error("The Cpp implementation of the object is not found");
    });
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_bfr_buddy_jnidemo_MainActivity_getValueStoredInCppSideOfDummyObject(
        JNIEnv *env, jclass /*clazz*/, jobject jDummyObject) {

    return convertCppExceptionsToJavaExceptionsAndReturnTheResult<jint>(env, [&]{
        std::lock_guard<std::mutex> lock(_idToDummyObjectMutex);

        auto id = getIdOfDisposableWithId(env, jDummyObject);
        auto it = _idToDummyObject.find(id);
        if (it != _idToDummyObject.end())
            return it->second.getValue();

        throw std::runtime_error("The Cpp implementation of the object is not found");
    }, 0);
}

