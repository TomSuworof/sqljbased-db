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

char *randstring(size_t length) {
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    char *randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {
            for (int n = 0;n < length;n++) {
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

JNIEXPORT jobjectArray JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_getAll
        (JNIEnv* env,
         jclass clazz,
         jstring username,
         jstring password)
{
    const char *usernameNtv = (*env)->GetStringUTFChars(env, username, NULL);
    const char *passwordNtv = (*env)->GetStringUTFChars(env, password, NULL);

    /* exec sql begin declare section */
     
     
     
       
       
    
#line 40 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 41 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 42 "NativeAdapter.pgc"
 char databases [ BUFSIZE ] [ BUFSIZE ] ;
 
#line 43 "NativeAdapter.pgc"
 int num_databases = BUFSIZE ;
 
#line 44 "NativeAdapter.pgc"
 char * conn_name = randstring ( 5 ) ;
/* exec sql end declare section */
#line 45 "NativeAdapter.pgc"


    /* declare curs cursor for select dbname from get_all_databases ( ) */
#line 48 "NativeAdapter.pgc"


    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 55 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 56 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 56 "NativeAdapter.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select count ( dbname ) from get_all_databases ( )", ECPGt_EOIT, 
	ECPGt_int,&(num_databases),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 58 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 58 "NativeAdapter.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare curs cursor for select dbname from get_all_databases ( )", ECPGt_EOIT, ECPGt_EORT);
#line 60 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 60 "NativeAdapter.pgc"


    for (int i = 0; i < num_databases; i++)
    {
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next from curs", ECPGt_EOIT, 
	ECPGt_char,(databases[i]),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 64 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 64 "NativeAdapter.pgc"

    }

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close curs", ECPGt_EOIT, ECPGt_EORT);
#line 67 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 67 "NativeAdapter.pgc"


    { ECPGdisconnect(__LINE__, conn_name);
#line 69 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 69 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    jobjectArray ret = (jobjectArray) (*env)->NewObjectArray(env, num_databases, (*env)->FindClass(env, "java/lang/String"), (*env)->NewStringUTF(env, ""));

    for (int i = 0; i < num_databases; i++)
    {
        (*env)->SetObjectArrayElement(env, ret, i, (*env)->NewStringUTF(env, databases[i]));
    }

    return ret;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 84 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 84 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return NULL;
}

JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_test
        (JNIEnv* env,
         jclass clazz,
         jstring database,
         jstring username,
         jstring password)
{
    const char *databaseNtv = (*env)->GetStringUTFChars(env, database, NULL);
    const char *usernameNtv = (*env)->GetStringUTFChars(env, username, NULL);
    const char *passwordNtv = (*env)->GetStringUTFChars(env, password, NULL);

    /* exec sql begin declare section */
     
     
     
       
    
#line 101 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 102 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 103 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 104 "NativeAdapter.pgc"
 char * conn_name = randstring ( 6 ) ;
/* exec sql end declare section */
#line 105 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 114 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 115 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 115 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, conn_name);
#line 116 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 116 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 125 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 125 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
}

JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_save
        (JNIEnv* env,
         jclass clazz,
         jstring database,
         jstring username,
         jstring password)
{
    const char *databaseNtv = (*env)->GetStringUTFChars(env, database, NULL);
    const char *usernameNtv = (*env)->GetStringUTFChars(env, username, NULL);
    const char *passwordNtv = (*env)->GetStringUTFChars(env, password, NULL);

    /* exec sql begin declare section */
     
     
     
       
    
#line 142 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 143 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 144 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 145 "NativeAdapter.pgc"
 char * conn_name = randstring ( 7 ) ;
/* exec sql end declare section */
#line 146 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 155 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 155 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 157 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from create_database ( $1  , $2  , $3  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 158 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 158 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 160 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 160 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, conn_name);
#line 161 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 161 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 170 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 170 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
}

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

    /* exec sql begin declare section */
     
     
     
       
    
#line 187 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 188 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 189 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 190 "NativeAdapter.pgc"
 char * conn_name = randstring ( 8 ) ;
/* exec sql end declare section */
#line 191 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 200 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 200 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 202 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from delete_database ( $1  , $2  , $3  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 203 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 203 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 205 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 205 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 206 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 206 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 215 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 215 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
}

JNIEXPORT jstring JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_getNumberOfAllItems
        (JNIEnv* env,
         jclass clazz,
         jstring database,
         jstring username,
         jstring password)
{
    const char *databaseNtv = (*env)->GetStringUTFChars(env, database, NULL);
    const char *usernameNtv = (*env)->GetStringUTFChars(env, username, NULL);
    const char *passwordNtv = (*env)->GetStringUTFChars(env, password, NULL);

    /* exec sql begin declare section */
     
     
     
     
       
    
#line 232 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 233 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 234 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 235 "NativeAdapter.pgc"
 char num_all_items [ BUFSIZE ] ;
 
#line 236 "NativeAdapter.pgc"
 char * conn_name = randstring ( 9 ) ;
/* exec sql end declare section */
#line 237 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 246 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 247 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 247 "NativeAdapter.pgc"


    { ECPGdo(__LINE__, 0, 1, conn_name, 0, ECPGst_normal, "select count from count_all_from_database ( $1  , $2  , $3  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,(num_all_items),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 249 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 249 "NativeAdapter.pgc"


    { ECPGdisconnect(__LINE__, conn_name);
#line 251 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 251 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    return (*env)->NewStringUTF(env, num_all_items);

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 260 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 260 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return (*env)->NewStringUTF(env, "0");
}

JNIEXPORT jobjectArray JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_getAllItems
        (JNIEnv* env,
         jclass clazz,
         jstring database,
         jstring username,
         jstring password,
         jlong numberOfItems)
{
    const char *databaseNtv = (*env)->GetStringUTFChars(env, database, NULL);
    const char *usernameNtv = (*env)->GetStringUTFChars(env, username, NULL);
    const char *passwordNtv = (*env)->GetStringUTFChars(env, password, NULL);

    /* exec sql begin declare section */
     
     
     

     
     
     
     
     
     

       
    
#line 278 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 279 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 280 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 282 "NativeAdapter.pgc"
 char item_ids [ numberOfItems ] [ BUFSIZE ] ;
 
#line 283 "NativeAdapter.pgc"
 char item_names [ numberOfItems ] [ BUFSIZE ] ;
 
#line 284 "NativeAdapter.pgc"
 char item_amounts [ numberOfItems ] [ BUFSIZE ] ;
 
#line 285 "NativeAdapter.pgc"
 char item_prices [ numberOfItems ] [ BUFSIZE ] ;
 
#line 286 "NativeAdapter.pgc"
 char item_colors [ numberOfItems ] [ BUFSIZE ] ;
 
#line 287 "NativeAdapter.pgc"
 char item_refurbisheds [ numberOfItems ] [ BUFSIZE ] ;
 
#line 289 "NativeAdapter.pgc"
 char * conn_name = randstring ( 10 ) ;
/* exec sql end declare section */
#line 290 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    ECPGset_var( 0, &( user_passwd ), __LINE__);\
 ECPGset_var( 1, &( user_name ), __LINE__);\
 ECPGset_var( 2, &( database_name ), __LINE__);\
 /* declare item_curs cursor for select id , name , amountavailable , price , color , refurbished from select_all_from_database ( $1  , $2  , $3  ) */
#line 300 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;
#line 300 "NativeAdapter.pgc"

#line 300 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 302 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 303 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 303 "NativeAdapter.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare item_curs cursor for select id , name , amountavailable , price , color , refurbished from select_all_from_database ( $1  , $2  , $3  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 305 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 305 "NativeAdapter.pgc"


    for (long i = 0; i < numberOfItems; i++)
    {
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next from item_curs", ECPGt_EOIT, 
	ECPGt_char,(item_ids[i]),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(item_names[i]),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(item_amounts[i]),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(item_prices[i]),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(item_colors[i]),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(item_refurbisheds[i]),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 309 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 309 "NativeAdapter.pgc"

    }

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close item_curs", ECPGt_EOIT, ECPGt_EORT);
#line 312 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 312 "NativeAdapter.pgc"


    { ECPGdisconnect(__LINE__, conn_name);
#line 314 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 314 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    jobjectArray firstItem = (jobjectArray) (*env)->NewObjectArray(env, 6, (*env)->FindClass(env, "java/lang/String"), (*env)->NewStringUTF(env, ""));
    (*env)->SetObjectArrayElement(env, firstItem, 0, (*env)->NewStringUTF(env, item_ids[0]));
    (*env)->SetObjectArrayElement(env, firstItem, 1, (*env)->NewStringUTF(env, item_names[0]));
    (*env)->SetObjectArrayElement(env, firstItem, 2, (*env)->NewStringUTF(env, item_amounts[0]));
    (*env)->SetObjectArrayElement(env, firstItem, 3, (*env)->NewStringUTF(env, item_prices[0]));
    (*env)->SetObjectArrayElement(env, firstItem, 4, (*env)->NewStringUTF(env, item_colors[0]));
    (*env)->SetObjectArrayElement(env, firstItem, 5, (*env)->NewStringUTF(env, item_refurbisheds[0]));

    jobjectArray items = (jobjectArray) (*env)->NewObjectArray(env, numberOfItems, (*env)->GetObjectClass(env, firstItem), firstItem);

    for (long i = 1; i < numberOfItems; i++)
    {
        jobjectArray item = (jobjectArray) (*env)->NewObjectArray(env, 6, (*env)->FindClass(env, "java/lang/String"), (*env)->NewStringUTF(env, ""));
        (*env)->SetObjectArrayElement(env, item, 0, (*env)->NewStringUTF(env, item_ids[i]));
        (*env)->SetObjectArrayElement(env, item, 1, (*env)->NewStringUTF(env, item_names[i]));
        (*env)->SetObjectArrayElement(env, item, 2, (*env)->NewStringUTF(env, item_amounts[i]));
        (*env)->SetObjectArrayElement(env, item, 3, (*env)->NewStringUTF(env, item_prices[i]));
        (*env)->SetObjectArrayElement(env, item, 4, (*env)->NewStringUTF(env, item_colors[i]));
        (*env)->SetObjectArrayElement(env, item, 5, (*env)->NewStringUTF(env, item_refurbisheds[i]));

        (*env)->SetObjectArrayElement(env, items, i, item);
    }

    return items;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 346 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 346 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return NULL;
}

JNIEXPORT jstring JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_getNumberOfItemsPyParam
        (JNIEnv* env,
         jclass clazz,
         jstring database,
         jstring username,
         jstring password,
         jstring paramName,
         jstring paramValue)
{
    const char *databaseNtv = (*env)->GetStringUTFChars(env, database, NULL);
    const char *usernameNtv = (*env)->GetStringUTFChars(env, username, NULL);
    const char *passwordNtv = (*env)->GetStringUTFChars(env, password, NULL);
    const char *paramNameNtv = (*env)->GetStringUTFChars(env, paramName, NULL);
    const char *paramValueNtv = (*env)->GetStringUTFChars(env, paramValue, NULL);

    /* exec sql begin declare section */
     
     
     
     
     
     
       
    
#line 367 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 368 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 369 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 370 "NativeAdapter.pgc"
 char param_name [ BUFSIZE ] ;
 
#line 371 "NativeAdapter.pgc"
 char param_value [ BUFSIZE ] ;
 
#line 372 "NativeAdapter.pgc"
 char num_items [ BUFSIZE ] ;
 
#line 373 "NativeAdapter.pgc"
 char * conn_name = randstring ( 11 ) ;
/* exec sql end declare section */
#line 374 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;
    strncpy(param_name, paramNameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(param_value, paramValueNtv, BUFSIZE - 1);
    param_value[BUFSIZE - 1] = 0;

    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 387 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 388 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 388 "NativeAdapter.pgc"


    { ECPGdo(__LINE__, 0, 1, conn_name, 0, ECPGst_normal, "select count from count_from_database_by_param ( $1  , $2  , $3  , $4  , $5  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(param_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(param_value),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,(num_items),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 390 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 390 "NativeAdapter.pgc"


    { ECPGdisconnect(__LINE__, conn_name);
#line 392 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 392 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);
    (*env)->ReleaseStringUTFChars(env, paramName, paramNameNtv);
    (*env)->ReleaseStringUTFChars(env, paramValue, paramValueNtv);

    return (*env)->NewStringUTF(env, num_items);

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 403 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 403 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return (*env)->NewStringUTF(env, "0");
}

JNIEXPORT jobjectArray JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_getItemsByParam
        (JNIEnv* env,
         jclass clazz,
         jstring database,
         jstring username,
         jstring password,
         jstring paramName,
         jstring paramValue,
         jlong numberOfItems)
{
    const char *databaseNtv = (*env)->GetStringUTFChars(env, database, NULL);
    const char *usernameNtv = (*env)->GetStringUTFChars(env, username, NULL);
    const char *passwordNtv = (*env)->GetStringUTFChars(env, password, NULL);
    const char *paramNameNtv = (*env)->GetStringUTFChars(env, paramName, NULL);
    const char *paramValueNtv = (*env)->GetStringUTFChars(env, paramValue, NULL);

    /* exec sql begin declare section */
     
     
     
     
     

     
     
     
     
     
     

       
    
#line 425 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 426 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 427 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 428 "NativeAdapter.pgc"
 char param_name [ BUFSIZE ] ;
 
#line 429 "NativeAdapter.pgc"
 char param_value [ BUFSIZE ] ;
 
#line 431 "NativeAdapter.pgc"
 char item_ids [ numberOfItems ] [ BUFSIZE ] ;
 
#line 432 "NativeAdapter.pgc"
 char item_names [ numberOfItems ] [ BUFSIZE ] ;
 
#line 433 "NativeAdapter.pgc"
 char item_amounts [ numberOfItems ] [ BUFSIZE ] ;
 
#line 434 "NativeAdapter.pgc"
 char item_prices [ numberOfItems ] [ BUFSIZE ] ;
 
#line 435 "NativeAdapter.pgc"
 char item_colors [ numberOfItems ] [ BUFSIZE ] ;
 
#line 436 "NativeAdapter.pgc"
 char item_refurbisheds [ numberOfItems ] [ BUFSIZE ] ;
 
#line 438 "NativeAdapter.pgc"
 char * conn_name = randstring ( 12 ) ;
/* exec sql end declare section */
#line 439 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;
    strncpy(param_name, paramNameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(param_value, paramValueNtv, BUFSIZE - 1);
    param_value[BUFSIZE - 1] = 0;

    ECPGset_var( 3, &( param_value ), __LINE__);\
 ECPGset_var( 4, &( param_name ), __LINE__);\
 ECPGset_var( 5, &( user_passwd ), __LINE__);\
 ECPGset_var( 6, &( user_name ), __LINE__);\
 ECPGset_var( 7, &( database_name ), __LINE__);\
 /* declare item_curs_with_param cursor for select id , name , amountavailable , price , color , refurbished from select_from_database_by_param ( $1  , $2  , $3  , $4  , $5  ) */
#line 453 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;
#line 453 "NativeAdapter.pgc"

#line 453 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 455 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 456 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 456 "NativeAdapter.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare item_curs_with_param cursor for select id , name , amountavailable , price , color , refurbished from select_from_database_by_param ( $1  , $2  , $3  , $4  , $5  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(param_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(param_value),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 458 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 458 "NativeAdapter.pgc"


    for (long i = 0; i < numberOfItems; i++)
    {
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next from item_curs_with_param", ECPGt_EOIT, 
	ECPGt_char,(item_ids[i]),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(item_names[i]),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(item_amounts[i]),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(item_prices[i]),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(item_colors[i]),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(item_refurbisheds[i]),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 462 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 462 "NativeAdapter.pgc"

    }

    printf("items collected\n");

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close item_curs_with_param", ECPGt_EOIT, ECPGt_EORT);
#line 467 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 467 "NativeAdapter.pgc"


    { ECPGdisconnect(__LINE__, conn_name);
#line 469 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 469 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);
    (*env)->ReleaseStringUTFChars(env, paramName, paramNameNtv);
    (*env)->ReleaseStringUTFChars(env, paramValue, paramValueNtv);

    jobjectArray firstItem = (jobjectArray) (*env)->NewObjectArray(env, 6, (*env)->FindClass(env, "java/lang/String"), (*env)->NewStringUTF(env, ""));
    (*env)->SetObjectArrayElement(env, firstItem, 0, (*env)->NewStringUTF(env, item_ids[0]));
    (*env)->SetObjectArrayElement(env, firstItem, 1, (*env)->NewStringUTF(env, item_names[0]));
    (*env)->SetObjectArrayElement(env, firstItem, 2, (*env)->NewStringUTF(env, item_amounts[0]));
    (*env)->SetObjectArrayElement(env, firstItem, 3, (*env)->NewStringUTF(env, item_prices[0]));
    (*env)->SetObjectArrayElement(env, firstItem, 4, (*env)->NewStringUTF(env, item_colors[0]));
    (*env)->SetObjectArrayElement(env, firstItem, 5, (*env)->NewStringUTF(env, item_refurbisheds[0]));

    jobjectArray items = (jobjectArray) (*env)->NewObjectArray(env, numberOfItems, (*env)->GetObjectClass(env, firstItem), firstItem);

    for (long i = 1; i < numberOfItems; i++)
    {
        jobjectArray item = (jobjectArray) (*env)->NewObjectArray(env, 6, (*env)->FindClass(env, "java/lang/String"), (*env)->NewStringUTF(env, ""));
        (*env)->SetObjectArrayElement(env, item, 0, (*env)->NewStringUTF(env, item_ids[i]));
        (*env)->SetObjectArrayElement(env, item, 1, (*env)->NewStringUTF(env, item_names[i]));
        (*env)->SetObjectArrayElement(env, item, 2, (*env)->NewStringUTF(env, item_amounts[i]));
        (*env)->SetObjectArrayElement(env, item, 3, (*env)->NewStringUTF(env, item_prices[i]));
        (*env)->SetObjectArrayElement(env, item, 4, (*env)->NewStringUTF(env, item_colors[i]));
        (*env)->SetObjectArrayElement(env, item, 5, (*env)->NewStringUTF(env, item_refurbisheds[i]));

        (*env)->SetObjectArrayElement(env, items, i, item);
    }

    return items;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 503 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 503 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return NULL;
}

JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_addItem
        (JNIEnv* env,
         jclass clazz,
         jstring database,
         jstring username,
         jstring password,
         jlong id,
         jstring name,
         jlong amount,
         jint price,
         jstring color,
         jboolean refurbished)
{
    const char *databaseNtv = (*env)->GetStringUTFChars(env, database, NULL);
    const char *usernameNtv = (*env)->GetStringUTFChars(env, username, NULL);
    const char *passwordNtv = (*env)->GetStringUTFChars(env, password, NULL);
    long idNtv = (long) id;
    const char *nameNtv = (*env)->GetStringUTFChars(env, name, NULL);
    long amountNtv = (long) amount;
    int priceNtv = (int) price;
    const char *colorNtv = (*env)->GetStringUTFChars(env, color, NULL);
    bool refurbishedNtv = (bool) refurbished;

    /* exec sql begin declare section */
     
     
     

     
     
     
     
     
     

       
    
#line 532 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 533 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 534 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 536 "NativeAdapter.pgc"
 long item_id ;
 
#line 537 "NativeAdapter.pgc"
 char item_name [ BUFSIZE ] ;
 
#line 538 "NativeAdapter.pgc"
 long item_amount ;
 
#line 539 "NativeAdapter.pgc"
 int item_price ;
 
#line 540 "NativeAdapter.pgc"
 char item_color [ BUFSIZE ] ;
 
#line 541 "NativeAdapter.pgc"
 bool item_refurbished ;
 
#line 543 "NativeAdapter.pgc"
 char * conn_name = randstring ( 13 ) ;
/* exec sql end declare section */
#line 544 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    item_id = idNtv;
    strncpy(item_name, nameNtv, BUFSIZE - 1);
    item_name[BUFSIZE - 1] = 0;
    item_amount = amountNtv;
    item_price = priceNtv;
    strncpy(item_color, colorNtv, BUFSIZE - 1);
    item_color[BUFSIZE - 1] = 0;
    item_refurbished = refurbishedNtv;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 562 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 562 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 564 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from insert_into_database ( $1  , $2  , $3  , $4  , $5  , $6  , $7  , $8  , $9  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(item_id),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(item_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_long,&(item_amount),(long)1,(long)1,sizeof(long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(item_price),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(item_color),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_bool,&(item_refurbished),(long)1,(long)1,sizeof(bool), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 565 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 565 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 567 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 567 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, conn_name);
#line 568 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 568 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    (*env)->ReleaseStringUTFChars(env, name, nameNtv);
    (*env)->ReleaseStringUTFChars(env, color, colorNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 580 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 580 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
}

JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_deleteItem
        (JNIEnv* env,
         jclass clazz,
         jstring database,
         jstring username,
         jstring password,
         jstring paramName,
         jstring paramValue)
{
    const char *databaseNtv = (*env)->GetStringUTFChars(env, database, NULL);
    const char *usernameNtv = (*env)->GetStringUTFChars(env, username, NULL);
    const char *passwordNtv = (*env)->GetStringUTFChars(env, password, NULL);

    const char *paramNameNtv = (*env)->GetStringUTFChars(env, paramName, NULL);
    const char *paramValueNtv = (*env)->GetStringUTFChars(env, paramValue, NULL);

    /* exec sql begin declare section */
     
     
     

     
     

       
    
#line 602 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 603 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 604 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 606 "NativeAdapter.pgc"
 char param_name [ BUFSIZE ] ;
 
#line 607 "NativeAdapter.pgc"
 char param_value [ BUFSIZE ] ;
 
#line 609 "NativeAdapter.pgc"
 char * conn_name = randstring ( 14 ) ;
/* exec sql end declare section */
#line 610 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    strncpy(param_name, paramNameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(param_value, paramValueNtv, BUFSIZE - 1);
    param_value[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 624 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 624 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 626 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from delete_from_database_by_param ( $1  , $2  , $3  , $4  , $5  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(param_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(param_value),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 627 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 627 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 629 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 629 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, conn_name);
#line 630 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 630 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    (*env)->ReleaseStringUTFChars(env, paramName, paramNameNtv);
    (*env)->ReleaseStringUTFChars(env, paramValue, paramValueNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 642 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 642 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
}

JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_existsByUsername
        (JNIEnv* env,
         jclass clazz,
         jstring usernameToSearch,
         jstring username,
         jstring password,
         jstring database)
{
    const char *usernameToSearchNtv = (*env)->GetStringUTFChars(env, usernameToSearch, NULL);
    const char *databaseNtv = (*env)->GetStringUTFChars(env, database, NULL);
    const char *usernameNtv = (*env)->GetStringUTFChars(env, username, NULL);
    const char *passwordNtv = (*env)->GetStringUTFChars(env, password, NULL);

    /* exec sql begin declare section */
     
     
     
     
       
       
    
#line 661 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 662 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 663 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 664 "NativeAdapter.pgc"
 char username_to_search [ BUFSIZE ] ;
 
#line 665 "NativeAdapter.pgc"
 bool user_found = true ;
 
#line 666 "NativeAdapter.pgc"
 char * conn_name = randstring ( 15 ) ;
/* exec sql end declare section */
#line 667 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;
    strncpy(username_to_search, usernameToSearchNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;

    ECPGset_var( 8, &( database_name ), __LINE__);\
 ECPGset_var( 9, &( user_passwd ), __LINE__);\
 ECPGset_var( 10, &( user_name ), __LINE__);\
 ECPGset_var( 11, &( username_to_search ), __LINE__);\
 /* declare user_curs cursor for select user_exists from user_exists_by_username ( $1  , $2  , $3  , $4  ) */
#line 679 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;
#line 679 "NativeAdapter.pgc"

#line 679 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 681 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 682 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 682 "NativeAdapter.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare user_curs cursor for select user_exists from user_exists_by_username ( $1  , $2  , $3  , $4  )", 
	ECPGt_char,(username_to_search),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 684 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 684 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next user_curs", ECPGt_EOIT, 
	ECPGt_bool,&(user_found),(long)1,(long)1,sizeof(bool), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 685 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 685 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close user_curs", ECPGt_EOIT, ECPGt_EORT);
#line 686 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 686 "NativeAdapter.pgc"


    { ECPGdisconnect(__LINE__, conn_name);
#line 688 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 688 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);
    (*env)->ReleaseStringUTFChars(env, usernameToSearch, usernameToSearchNtv);

    return user_found;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 698 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 698 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
}

JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_addSuperuser
        (JNIEnv* env,
         jclass clazz,
         jstring usernameToSave,
         jstring passwordToSave,
         jstring authUsername,
         jstring authPassword)
{
    const char *usernameToSaveNtv = (*env)->GetStringUTFChars(env, usernameToSave, NULL);
    const char *passwordToSaveNtv = (*env)->GetStringUTFChars(env, passwordToSave, NULL);

    const char *usernameNtv = (*env)->GetStringUTFChars(env, authUsername, NULL);
    const char *passwordNtv = (*env)->GetStringUTFChars(env, authPassword, NULL);

    /* exec sql begin declare section */
     
     
     
     
       
    
#line 718 "NativeAdapter.pgc"
 char username_to_save [ BUFSIZE ] ;
 
#line 719 "NativeAdapter.pgc"
 char password_to_save [ BUFSIZE ] ;
 
#line 720 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 721 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 722 "NativeAdapter.pgc"
 char * conn_name = randstring ( 16 ) ;
/* exec sql end declare section */
#line 723 "NativeAdapter.pgc"


    strncpy(username_to_save, usernameToSaveNtv, BUFSIZE - 1);
    username_to_save[BUFSIZE - 1] = 0;
    strncpy(password_to_save, passwordToSaveNtv, BUFSIZE - 1);
    password_to_save[BUFSIZE - 1] = 0;

    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 735 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 735 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 737 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from add_superuser ( $1  , $2  , $3  , $4  )", 
	ECPGt_char,(username_to_save),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(password_to_save),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 738 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 738 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 740 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 740 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, conn_name);
#line 741 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 741 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, usernameToSave, usernameToSaveNtv);
    (*env)->ReleaseStringUTFChars(env, passwordToSave, passwordToSaveNtv);

    (*env)->ReleaseStringUTFChars(env, authUsername, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, authPassword, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 752 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 752 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
}

JNIEXPORT jboolean JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_addCasual
        (JNIEnv* env,
         jclass clazz,
         jstring usernameToSave,
         jstring passwordToSave,
         jstring authUsername,
         jstring authPassword,
         jstring database)
{
    const char *usernameToSaveNtv = (*env)->GetStringUTFChars(env, usernameToSave, NULL);
    const char *passwordToSaveNtv = (*env)->GetStringUTFChars(env, passwordToSave, NULL);

    const char *usernameNtv = (*env)->GetStringUTFChars(env, authUsername, NULL);
    const char *passwordNtv = (*env)->GetStringUTFChars(env, authPassword, NULL);
    const char *databaseNtv = (*env)->GetStringUTFChars(env, database, NULL);

    /* exec sql begin declare section */
     
     
     
     
     
       
    
#line 774 "NativeAdapter.pgc"
 char username_to_save [ BUFSIZE ] ;
 
#line 775 "NativeAdapter.pgc"
 char password_to_save [ BUFSIZE ] ;
 
#line 776 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 777 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 778 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 779 "NativeAdapter.pgc"
 char * conn_name = randstring ( 17 ) ;
/* exec sql end declare section */
#line 780 "NativeAdapter.pgc"


    strncpy(username_to_save, usernameToSaveNtv, BUFSIZE - 1);
    username_to_save[BUFSIZE - 1] = 0;
    strncpy(password_to_save, passwordToSaveNtv, BUFSIZE - 1);
    password_to_save[BUFSIZE - 1] = 0;

    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;
    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 794 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 794 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 796 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from add_casual_to_database ( $1  , $2  , $3  , $4  , $5  )", 
	ECPGt_char,(username_to_save),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(password_to_save),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 797 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 797 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 799 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 799 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, conn_name);
#line 800 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 800 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, usernameToSave, usernameToSaveNtv);
    (*env)->ReleaseStringUTFChars(env, passwordToSave, passwordToSaveNtv);

    (*env)->ReleaseStringUTFChars(env, authUsername, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, authPassword, passwordNtv);
    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 812 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 812 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
}