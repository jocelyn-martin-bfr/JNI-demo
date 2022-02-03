#ifndef JNI_DEMO_ANDROID_JOBJECTSTOCPPTYPES_HPP
#define JNI_DEMO_ANDROID_JOBJECTSTOCPPTYPES_HPP

#include <map>
#include <string>
#include <jni.h>
#include "exampleofenum.hpp"
#include "enumsindexes.hpp"


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
        //_env->DeleteLocalRef(_object);
    }
    jobject get() { return _object; }
    JNIEnv* getEnv() { return _env; }

private:
    JNIEnv* _env;
    jobject _object;
};


std::string toString(JNIEnv *env, jstring inputString);

jobjectArray tojstringArray(JNIEnv *env, const std::vector<std::string> &pStrs);

jint getIdOfDisposableWithId(JNIEnv *env, jobject object);

ExampleOfEnum toExampleOfEnum(
        JNIEnv *env,
        jobject exampleOfEnumJobj,
        const SemanticEnumsIndexes &pSemanticEnumsIndexes);


#endif // JNI_DEMO_ANDROID_JOBJECTSTOCPPTYPES_HPP
