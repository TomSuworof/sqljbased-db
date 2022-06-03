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

JNIEXPORT jobjectArray JNICALL Java_com_dreamteam_sqljbaseddb_repositories_NativeAdapter_getAll
        (JNIEnv* env,
         jclass clazz,
         jstring username,
         jstring password)
{
    const char *usernameNtv = (*env)->GetStringUTFChars(env, username, NULL);
    const char *passwordNtv = (*env)->GetStringUTFChars(env, password, NULL);

    const char *databases[10] = {"humorous",
                                 "applaud",
                                 "curlikbnjkrnkjr",
                                 "aware",
                                 "bareable",
                                 "mellow",
                                 "courageous",
                                 "supreme",
                                 "animal",
                                 "cynical"}; // some sample strings for test
    int curr_db = 0;

    /* exec sql begin declare section */
     
     
     
    
#line 32 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 33 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 34 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
/* exec sql end declare section */
#line 35 "NativeAdapter.pgc"


    { ECPGprepare(__LINE__, NULL, 0, "stmt", "select * from get_all_databases()");}
#line 37 "NativeAdapter.pgc"

    /* declare curs cursor for $1 */
#line 38 "NativeAdapter.pgc"


    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, usernameNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 45 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 46 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 46 "NativeAdapter.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare curs cursor for $1", 
	ECPGt_char_variable,(ECPGprepared_statement(NULL, "stmt", __LINE__)),(long)1,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 48 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 48 "NativeAdapter.pgc"
 // crashes Virtual Machine

    while (1)
    {
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next from curs", ECPGt_EOIT, 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 52 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 52 "NativeAdapter.pgc"


        if (curr_db == 10) break;

        databases[curr_db] = database_name;
        curr_db++;
    }

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close curs", ECPGt_EOIT, ECPGt_EORT);
#line 60 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 60 "NativeAdapter.pgc"


    { ECPGdisconnect(__LINE__, "dm_conn");
#line 62 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 62 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    jobjectArray ret = (jobjectArray) (*env)->NewObjectArray(env, 10, (*env)->FindClass(env, "java/lang/String"), (*env)->NewStringUTF(env, ""));

    for (int i = 0; i < 10; i++)
    {
        (*env)->SetObjectArrayElement(env, ret, i, (*env)->NewStringUTF(env, databases[i]));
    }

    return ret;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 77 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 77 "NativeAdapter.pgc"

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
     
     
     
    
#line 94 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 95 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 96 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
/* exec sql end declare section */
#line 97 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, usernameNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 106 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 107 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 107 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 108 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 108 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 117 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 117 "NativeAdapter.pgc"

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
     
     
     
    
#line 134 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 135 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 136 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
/* exec sql end declare section */
#line 137 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, usernameNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 146 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 146 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 148 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from create_database ( $1  , $2  , $3  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 149 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 149 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 151 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 151 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 152 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 152 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 161 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 161 "NativeAdapter.pgc"

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
     
     
     
    
#line 178 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 179 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 180 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
/* exec sql end declare section */
#line 181 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, usernameNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 190 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 190 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 192 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from delete_database ( $1  , $2  , $3  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 193 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 193 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 195 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 195 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 196 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 196 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 205 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 205 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
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
     
     
     

     
     
     
     
     
     
    
#line 234 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 235 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 236 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 238 "NativeAdapter.pgc"
 long item_id ;
 
#line 239 "NativeAdapter.pgc"
 char item_name [ BUFSIZE ] ;
 
#line 240 "NativeAdapter.pgc"
 long item_amount ;
 
#line 241 "NativeAdapter.pgc"
 int item_price ;
 
#line 242 "NativeAdapter.pgc"
 char item_color [ BUFSIZE ] ;
 
#line 243 "NativeAdapter.pgc"
 bool item_refurbished ;
/* exec sql end declare section */
#line 244 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, usernameNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    item_id = idNtv;
    strncpy(item_name, nameNtv, BUFSIZE - 1);
    item_name[BUFSIZE - 1] = 0;
    item_amount = amountNtv;
    item_price = priceNtv;
    strncpy(item_color, colorNtv, BUFSIZE - 1);
    item_color[BUFSIZE - 1] = 0;
    item_refurbished = refurbishedNtv;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 262 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 262 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 264 "NativeAdapter.pgc"

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
#line 265 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 265 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 267 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 267 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 268 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 268 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    (*env)->ReleaseStringUTFChars(env, name, nameNtv);
    (*env)->ReleaseStringUTFChars(env, color, colorNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 280 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 280 "NativeAdapter.pgc"

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
     
     
     

     
     
    
#line 302 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 303 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 304 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 306 "NativeAdapter.pgc"
 char param_name [ BUFSIZE ] ;
 
#line 307 "NativeAdapter.pgc"
 char param_value [ BUFSIZE ] ;
/* exec sql end declare section */
#line 308 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, usernameNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    strncpy(param_name, paramNameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(param_value, paramValueNtv, BUFSIZE - 1);
    param_value[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 322 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 322 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 324 "NativeAdapter.pgc"

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
#line 325 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 325 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 327 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 327 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 328 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 328 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    (*env)->ReleaseStringUTFChars(env, paramName, paramNameNtv);
    (*env)->ReleaseStringUTFChars(env, paramValue, paramValueNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 340 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 340 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
}