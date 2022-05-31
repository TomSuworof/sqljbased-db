#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "com_dreamteam_sqljbaseddb_repositories_NativeAdapter.h"
#include "Native.h"

JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_Native_delete
        (JNIEnv* env,
         jclass clazz,
         jstring database,
         jstring username,
         jstring password)
{
    const char *databaseNtv = env->GetStringUTFChars(database, nullptr);
    const char *usernameNtv = env->GetStringUTFChars(username, nullptr);
    const char *passwordNtv = env->GetStringUTFChars(password, nullptr);

    printf(databaseNtv);
    printf(usernameNtv);
    printf(passwordNtv);

    delete_database(databaseNtv, usernameNtv, passwordNtv);

    env->ReleaseStringUTFChars(database, databaseNtv);
    env->ReleaseStringUTFChars(username, usernameNtv);
    env->ReleaseStringUTFChars(password, passwordNtv);

    return true;
}