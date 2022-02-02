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

    // Convert the Cpp struct to the Java class and return the Java class
    jmethodID dummyDataClassConstructor =
            env->GetMethodID(dummyDataClass, "<init>", "(ILjava/lang/String;)V");
    return env->NewObject(dummyDataClass, dummyDataClassConstructor, dummyData.i, env->NewStringUTF(dummyData.str.c_str()));
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_bfr_buddy_jnidemo_MainActivity_createCustomObject(
        JNIEnv *env, jclass /*clazz*/, jint value) {
    // Get the Java class
    jclass dummyObjectClass = env->FindClass(
            "com/bfr/buddy/jnidemo/DummyObject");

    // get an unique id


    // Convert the Cpp struct to the Java class and return the Java class
    jmethodID dummyObjectlassConstructor =
            env->GetMethodID(dummyObjectClass, "<init>", "(I)V");
    return env->NewObject(dummyObjectClass, dummyObjectlassConstructor, value));

}

