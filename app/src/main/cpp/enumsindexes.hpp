#ifndef JNI_DEMO_ANDROID_SEMANTICENUMSINDEXES_HPP
#define JNI_DEMO_ANDROID_SEMANTICENUMSINDEXES_HPP

#include <jni.h>
#include <vector>
#include <string>
#include "exampleofenum.hpp"



/**
 * Class to help the conversion of semantic java enums to cpp enums.
 * The indexes of the vectors correspond to the ordinal of the java values.
 * The values of the vectors correspond to the cpp enum values.
 */
struct SemanticEnumsIndexes {
    SemanticEnumsIndexes(JNIEnv *env);

    std::string exampleOfEnumClassName;
    std::vector<ExampleOfEnum> javaOrdinalExampleOfEnumToCpp;
};

const SemanticEnumsIndexes &getSemanticEnumsIndexes(JNIEnv *env);

#endif // JNI_DEMO_ANDROID_SEMANTICENUMSINDEXES_HPP
