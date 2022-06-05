/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_dreamteam_sqljbaseddb_repositories_NativeAdapter */

#ifndef _Included_com_dreamteam_sqljbaseddb_repositories_NativeAdapter
#define _Included_com_dreamteam_sqljbaseddb_repositories_NativeAdapter
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_dreamteam_sqljbaseddb_repositories_NativeAdapter
 * Method:    getAll
 * Signature: (Ljava/lang/String;Ljava/lang/String;)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_getAll
  (JNIEnv *, jclass, jstring, jstring);

/*
 * Class:     com_dreamteam_sqljbaseddb_repositories_NativeAdapter
 * Method:    test
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_test
  (JNIEnv *, jclass, jstring, jstring, jstring);

/*
 * Class:     com_dreamteam_sqljbaseddb_repositories_NativeAdapter
 * Method:    save
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_save
  (JNIEnv *, jclass, jstring, jstring, jstring);

/*
 * Class:     com_dreamteam_sqljbaseddb_repositories_NativeAdapter
 * Method:    delete
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_delete
  (JNIEnv *, jclass, jstring, jstring, jstring);

/*
 * Class:     com_dreamteam_sqljbaseddb_repositories_NativeAdapter
 * Method:    getAllItems
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)[[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_getAllItems
  (JNIEnv *, jclass, jstring, jstring, jstring);

/*
 * Class:     com_dreamteam_sqljbaseddb_repositories_NativeAdapter
 * Method:    getItemsByParam
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)[[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_getItemsByParam
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring, jstring);

/*
 * Class:     com_dreamteam_sqljbaseddb_repositories_NativeAdapter
 * Method:    addItem
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;JLjava/lang/String;JILjava/lang/String;Z)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_addItem
  (JNIEnv *, jclass, jstring, jstring, jstring, jlong, jstring, jlong, jint, jstring, jboolean);

/*
 * Class:     com_dreamteam_sqljbaseddb_repositories_NativeAdapter
 * Method:    deleteItem
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_deleteItem
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring, jstring);

/*
 * Class:     com_dreamteam_sqljbaseddb_repositories_NativeAdapter
 * Method:    existsByUsername
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_existsByUsername
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring);

/*
 * Class:     com_dreamteam_sqljbaseddb_repositories_NativeAdapter
 * Method:    addSuperuser
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_addSuperuser
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring);

/*
 * Class:     com_dreamteam_sqljbaseddb_repositories_NativeAdapter
 * Method:    addCasual
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_addCasual
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif
