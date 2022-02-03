#ifndef JNI_DEMO_ANDROID_UTIL_HPP
#define JNI_DEMO_ANDROID_UTIL_HPP


/**
 * Find the first identifier of the map that is not present.
 */
template<typename T>
jint findMissingKey(const std::map<jint, T> &pIdToObj) {
    jint currentId = 0;
    for (const auto &currMemory : pIdToObj) {
        int nextId = currentId + 1;
        if (currMemory.first > nextId)
            return nextId;
        currentId = currMemory.first;
    }
    return currentId + 1;
}



/**
 * Convert C++ exception to java exception.
 * /!\ Java exceptions don't stop the Cpp flow.
 */
static void
convertCppExceptionsToJavaExceptions(JNIEnv *env, const std::function<void()> &pFunction) {
    try {
        pFunction();
    } catch (const std::exception &e) {
        env->ThrowNew(env->FindClass("java/lang/RuntimeException"), e.what());
    }
}

/**
 * Convert C++ exception to java exception and as java exceptions don't stop the flow,
 * we need to return an object that corresponds to what the JNI wants. (that is why we have a default value)
 */
template<typename T>
T convertCppExceptionsToJavaExceptionsAndReturnTheResult(
        JNIEnv *env,
        const std::function<T()> &pFunction,
        const T &pDefaultReturn) {
    try {
        return pFunction();
    } catch (const std::exception &e) {
        env->ThrowNew(env->FindClass("java/lang/RuntimeException"), e.what());
    }
    return pDefaultReturn;
}


#endif // JNI_DEMO_ANDROID_UTIL_HPP
