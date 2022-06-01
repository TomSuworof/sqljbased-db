/* Processed by ecpg (12.4) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "NativeAdapter.pgc"
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "com_dreamteam_sqljbaseddb_repositories_NativeAdapter.h"

#define BUFSIZE 64

JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_delete
        (JNIEnv* env,
         jclass clazz,
         jstring database,
         jstring username,
         jstring password)
{
    const char *databaseNtv = (*env)->GetStringUTFChars(env, database, NULL);
    const char *usernameNtv = (*env)->GetStringUTFChars(env, username, NULL);
    const char *passwordNtv = (*env)->GetStringUTFChars(env, password, NULL);

    printf(databaseNtv);
    printf(usernameNtv);
    printf(passwordNtv);

    /* exec sql begin declare section */
     
     
     
    
#line 26 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 27 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 28 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
/* exec sql end declare section */
#line 29 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, usernameNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); }
#line 38 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 40 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from delete_database ( $1  , $2  , $3  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 41 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 41 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 43 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 43 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 44 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 44 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    return true;

  error_lab:
    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
}