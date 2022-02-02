#include <regex>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <jni.h>
#include "androidlog.hpp"


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