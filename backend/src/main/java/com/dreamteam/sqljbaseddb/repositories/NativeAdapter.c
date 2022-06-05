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
 char * conn_name = randstring ( 5 ) ;
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
 char * conn_name = randstring ( 5 ) ;
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
 char * conn_name ;
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

JNIEXPORT jobjectArray JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_getAllItems
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
 
#line 236 "NativeAdapter.pgc"
 char item_ids [ BUFSIZE ] [ BUFSIZE ] ;
 
#line 237 "NativeAdapter.pgc"
 char item_names [ BUFSIZE ] [ BUFSIZE ] ;
 
#line 238 "NativeAdapter.pgc"
 char item_amounts [ BUFSIZE ] [ BUFSIZE ] ;
 
#line 239 "NativeAdapter.pgc"
 char item_prices [ BUFSIZE ] [ BUFSIZE ] ;
 
#line 240 "NativeAdapter.pgc"
 char item_colors [ BUFSIZE ] [ BUFSIZE ] ;
 
#line 241 "NativeAdapter.pgc"
 char item_refurbisheds [ BUFSIZE ] [ BUFSIZE ] ;
 
#line 243 "NativeAdapter.pgc"
 long long num_items = 2 ;
 
#line 245 "NativeAdapter.pgc"
 char * conn_name = randstring ( 5 ) ;
/* exec sql end declare section */
#line 246 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    ECPGset_var( 0, &( user_passwd ), __LINE__);\
 ECPGset_var( 1, &( user_name ), __LINE__);\
 ECPGset_var( 2, &( database_name ), __LINE__);\
 /* declare num_curs cursor for select count from count_all_from_database ( $1  , $2  , $3  ) */
#line 256 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;
#line 256 "NativeAdapter.pgc"

#line 256 "NativeAdapter.pgc"

    ECPGset_var( 3, &( user_passwd ), __LINE__);\
 ECPGset_var( 4, &( user_name ), __LINE__);\
 ECPGset_var( 5, &( database_name ), __LINE__);\
 /* declare item_curs cursor for select id , name , amountavailable , price , color , refurbished from select_all_from_database ( $1  , $2  , $3  ) */
#line 258 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;
#line 258 "NativeAdapter.pgc"

#line 258 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 260 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 261 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 261 "NativeAdapter.pgc"

    printf("connected\n");

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare num_curs cursor for select count from count_all_from_database ( $1  , $2  , $3  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 264 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 264 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next num_curs", ECPGt_EOIT, 
	ECPGt_long_long,&(num_items),(long)1,(long)1,sizeof(long long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 265 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 265 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close num_curs", ECPGt_EOIT, ECPGt_EORT);
#line 266 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 266 "NativeAdapter.pgc"

//    EXEC SQL select count(*) into :num_items from select_all_from_database(:database_name, :user_name, :user_passwd);
    printf("num items: %d\n", num_items);

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare item_curs cursor for select id , name , amountavailable , price , color , refurbished from select_all_from_database ( $1  , $2  , $3  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 270 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 270 "NativeAdapter.pgc"


    for (int i = 0; i < num_items; i++)
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
#line 274 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 274 "NativeAdapter.pgc"

    }

    printf("items collected\n");

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close item_curs", ECPGt_EOIT, ECPGt_EORT);
#line 279 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 279 "NativeAdapter.pgc"


    { ECPGdisconnect(__LINE__, conn_name);
#line 281 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 281 "NativeAdapter.pgc"


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

    jobjectArray items = (jobjectArray) (*env)->NewObjectArray(env, num_items, (*env)->GetObjectClass(env, firstItem), firstItem);

    for (int i = 1; i < num_items; i++)
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
#line 313 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 313 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return NULL;
}

JNIEXPORT jobjectArray JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_getItemsByParam
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
     
     
     
     
     

     
     
     
     
     
     

        

       
    
#line 334 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 335 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 336 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 337 "NativeAdapter.pgc"
 char param_name [ BUFSIZE ] ;
 
#line 338 "NativeAdapter.pgc"
 char param_value [ BUFSIZE ] ;
 
#line 340 "NativeAdapter.pgc"
 char item_ids [ BUFSIZE ] [ BUFSIZE ] ;
 
#line 341 "NativeAdapter.pgc"
 char item_names [ BUFSIZE ] [ BUFSIZE ] ;
 
#line 342 "NativeAdapter.pgc"
 char item_amounts [ BUFSIZE ] [ BUFSIZE ] ;
 
#line 343 "NativeAdapter.pgc"
 char item_prices [ BUFSIZE ] [ BUFSIZE ] ;
 
#line 344 "NativeAdapter.pgc"
 char item_colors [ BUFSIZE ] [ BUFSIZE ] ;
 
#line 345 "NativeAdapter.pgc"
 char item_refurbisheds [ BUFSIZE ] [ BUFSIZE ] ;
 
#line 347 "NativeAdapter.pgc"
 long long num_items = BUFSIZE ;
 
#line 349 "NativeAdapter.pgc"
 char * conn_name = randstring ( 5 ) ;
/* exec sql end declare section */
#line 350 "NativeAdapter.pgc"


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

    ECPGset_var( 6, &( param_value ), __LINE__);\
 ECPGset_var( 7, &( param_name ), __LINE__);\
 ECPGset_var( 8, &( user_passwd ), __LINE__);\
 ECPGset_var( 9, &( user_name ), __LINE__);\
 ECPGset_var( 10, &( database_name ), __LINE__);\
 /* declare item_curs_with_param cursor for select id , name , amountavailable , price , color , refurbished from select_from_database_by_param ( $1  , $2  , $3  , $4  , $5  ) */
#line 364 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;
#line 364 "NativeAdapter.pgc"

#line 364 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 366 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 367 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 367 "NativeAdapter.pgc"

    printf("connected\n");

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select count ( id ) from select_from_database_by_param ( $1  , $2  , $3  , $4  , $5  )", 
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
	ECPGt_long_long,&(num_items),(long)1,(long)1,sizeof(long long), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 370 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 370 "NativeAdapter.pgc"

    printf("num items: %d\n", num_items);

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
#line 373 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 373 "NativeAdapter.pgc"


    for (int i = 0; i < num_items; i++)
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
#line 377 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 377 "NativeAdapter.pgc"

    }

    printf("items collected\n");

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close item_curs_with_param", ECPGt_EOIT, ECPGt_EORT);
#line 382 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 382 "NativeAdapter.pgc"


    { ECPGdisconnect(__LINE__, conn_name);
#line 384 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 384 "NativeAdapter.pgc"


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

    jobjectArray items = (jobjectArray) (*env)->NewObjectArray(env, num_items, (*env)->GetObjectClass(env, firstItem), firstItem);

    for (int i = 1; i < num_items; i++)
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
#line 418 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 418 "NativeAdapter.pgc"

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
     
     
     

     
     
     
     
     
     

       
    
#line 447 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 448 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 449 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 451 "NativeAdapter.pgc"
 long item_id ;
 
#line 452 "NativeAdapter.pgc"
 char item_name [ BUFSIZE ] ;
 
#line 453 "NativeAdapter.pgc"
 long item_amount ;
 
#line 454 "NativeAdapter.pgc"
 int item_price ;
 
#line 455 "NativeAdapter.pgc"
 char item_color [ BUFSIZE ] ;
 
#line 456 "NativeAdapter.pgc"
 bool item_refurbished ;
 
#line 458 "NativeAdapter.pgc"
 char * conn_name = randstring ( 5 ) ;
/* exec sql end declare section */
#line 459 "NativeAdapter.pgc"


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
#line 477 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 477 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 479 "NativeAdapter.pgc"

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
#line 480 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 480 "NativeAdapter.pgc"

    printf("item added\n");

    { ECPGtrans(__LINE__, NULL, "commit");
#line 483 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 483 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, conn_name);
#line 484 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 484 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    (*env)->ReleaseStringUTFChars(env, name, nameNtv);
    (*env)->ReleaseStringUTFChars(env, color, colorNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 496 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 496 "NativeAdapter.pgc"

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
     
     
     

     
     

       
    
#line 518 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 519 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 520 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 522 "NativeAdapter.pgc"
 char param_name [ BUFSIZE ] ;
 
#line 523 "NativeAdapter.pgc"
 char param_value [ BUFSIZE ] ;
 
#line 525 "NativeAdapter.pgc"
 char * conn_name = randstring ( 5 ) ;
/* exec sql end declare section */
#line 526 "NativeAdapter.pgc"


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
#line 540 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 540 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 542 "NativeAdapter.pgc"

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
#line 543 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 543 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 545 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 545 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, conn_name);
#line 546 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 546 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    (*env)->ReleaseStringUTFChars(env, paramName, paramNameNtv);
    (*env)->ReleaseStringUTFChars(env, paramValue, paramValueNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 558 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 558 "NativeAdapter.pgc"

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
     
     
     
     
       
       
    
#line 577 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 578 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 579 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 580 "NativeAdapter.pgc"
 char username_to_search [ BUFSIZE ] ;
 
#line 581 "NativeAdapter.pgc"
 bool user_found = true ;
 
#line 582 "NativeAdapter.pgc"
 char * conn_name = randstring ( 5 ) ;
/* exec sql end declare section */
#line 583 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;
    strncpy(username_to_search, usernameToSearchNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;

    ECPGset_var( 11, &( database_name ), __LINE__);\
 ECPGset_var( 12, &( user_passwd ), __LINE__);\
 ECPGset_var( 13, &( user_name ), __LINE__);\
 ECPGset_var( 14, &( username_to_search ), __LINE__);\
 /* declare user_curs cursor for select user_exists from user_exists_by_username ( $1  , $2  , $3  , $4  ) */
#line 595 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;
#line 595 "NativeAdapter.pgc"

#line 595 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 597 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 598 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 598 "NativeAdapter.pgc"

    printf("connected\n");

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare user_curs cursor for select user_exists from user_exists_by_username ( $1  , $2  , $3  , $4  )", 
	ECPGt_char,(username_to_search),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 601 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 601 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next user_curs", ECPGt_EOIT, 
	ECPGt_bool,&(user_found),(long)1,(long)1,sizeof(bool), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 602 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 602 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close user_curs", ECPGt_EOIT, ECPGt_EORT);
#line 603 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 603 "NativeAdapter.pgc"


    { ECPGdisconnect(__LINE__, conn_name);
#line 605 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 605 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);
    (*env)->ReleaseStringUTFChars(env, usernameToSearch, usernameToSearchNtv);

    return user_found;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 615 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 615 "NativeAdapter.pgc"

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
     
     
     
     
       
    
#line 635 "NativeAdapter.pgc"
 char username_to_save [ BUFSIZE ] ;
 
#line 636 "NativeAdapter.pgc"
 char password_to_save [ BUFSIZE ] ;
 
#line 637 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 638 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 639 "NativeAdapter.pgc"
 char * conn_name = randstring ( 5 ) ;
/* exec sql end declare section */
#line 640 "NativeAdapter.pgc"


    strncpy(username_to_save, usernameToSaveNtv, BUFSIZE - 1);
    username_to_save[BUFSIZE - 1] = 0;
    strncpy(password_to_save, passwordToSaveNtv, BUFSIZE - 1);
    password_to_save[BUFSIZE - 1] = 0;

    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , conn_name, 0); 
#line 652 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 652 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 654 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from add_superuser ( $1  , $2  , $3  , $4  )", 
	ECPGt_char,(username_to_save),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(password_to_save),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 655 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 655 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 657 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 657 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, conn_name);
#line 658 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 658 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, usernameToSave, usernameToSaveNtv);
    (*env)->ReleaseStringUTFChars(env, passwordToSave, passwordToSaveNtv);

    (*env)->ReleaseStringUTFChars(env, authUsername, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, authPassword, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 669 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 669 "NativeAdapter.pgc"

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
     
     
     
     
     
       
    
#line 691 "NativeAdapter.pgc"
 char username_to_save [ BUFSIZE ] ;
 
#line 692 "NativeAdapter.pgc"
 char password_to_save [ BUFSIZE ] ;
 
#line 693 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 694 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 695 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 696 "NativeAdapter.pgc"
 char * conn_name = randstring ( 5 ) ;
/* exec sql end declare section */
#line 697 "NativeAdapter.pgc"


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
#line 711 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 711 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 713 "NativeAdapter.pgc"

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
#line 714 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 714 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 716 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 716 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, conn_name);
#line 717 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 717 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, usernameToSave, usernameToSaveNtv);
    (*env)->ReleaseStringUTFChars(env, passwordToSave, passwordToSaveNtv);

    (*env)->ReleaseStringUTFChars(env, authUsername, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, authPassword, passwordNtv);
    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, conn_name);
#line 729 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 729 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
}