#ifndef ROBOTPLANNER_ANDROID_JOBJECTSTOCPPTYPES_HPP
#define ROBOTPLANNER_ANDROID_JOBJECTSTOCPPTYPES_HPP

#include <map>
#include <string>
#include <jni.h>

/**
 * All these jni conversions functions are called without thread protections.
 */



/**
 * Class to store a jobject.
 * The reference of this jobject will be deleted from the jni environment at the destruction of this object.
 */
class shared_jobject {
public:
    shared_jobject(
            JNIEnv *env,
            jobject object)
            : _env(env),
              _object(object) {}
    ~shared_jobject() {
        _env->DeleteLocalRef(_object);
    }
    jobject get() { return _object; }

private:
    JNIEnv* _env;
    jobject _object;
};


std::string toString(JNIEnv *env, jstring inputString);

jint toDisposableWithIdId(JNIEnv *env, jobject object);


#endif // ROBOTPLANNER_ANDROID_JOBJECTSTOCPPTYPES_HPP
