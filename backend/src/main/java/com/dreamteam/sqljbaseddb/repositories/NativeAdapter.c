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

    const char *databases[10];
    int curr_db = 0;

    /* exec sql begin declare section */
     
     
     
    
#line 23 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 24 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 25 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
/* exec sql end declare section */
#line 26 "NativeAdapter.pgc"


    { ECPGprepare(__LINE__, NULL, 0, "stmt", "select * from get_all_databases()");}
#line 28 "NativeAdapter.pgc"

    /* declare curs cursor for $1 */
#line 29 "NativeAdapter.pgc"


    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, usernameNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 36 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 37 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 37 "NativeAdapter.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare curs cursor for $1", 
	ECPGt_char_variable,(ECPGprepared_statement(NULL, "stmt", __LINE__)),(long)1,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 39 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 39 "NativeAdapter.pgc"


    while (1)
    {
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next from curs", ECPGt_EOIT, 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 43 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 43 "NativeAdapter.pgc"


        if (curr_db == 10) break;

        databases[curr_db] = database_name;
        curr_db++;
    }

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 51 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 51 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    jobjectArray ret = (jobjectArray) (*env)->NewObjectArray(env, 10, (*env)->FindClass(env, "java/lang/String"), (*env)->NewStringUTF(env, ""));

    for (int i = 0; i < curr_db; i++)
    {
        (*env)->SetObjectArrayElement(env, ret, i, (*env)->NewStringUTF(env, databases[i]));
    }

    return ret;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 66 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 66 "NativeAdapter.pgc"

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
     
     
     
    
#line 83 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 84 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 85 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
/* exec sql end declare section */
#line 86 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, usernameNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 95 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 96 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 96 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 97 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 97 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 106 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 106 "NativeAdapter.pgc"

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
     
     
     
    
#line 123 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 124 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 125 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
/* exec sql end declare section */
#line 126 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, usernameNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 135 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 135 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 137 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from create_database ( $1  , $2  , $3  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 138 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 138 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 140 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 140 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 141 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 141 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 150 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 150 "NativeAdapter.pgc"

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
     
     
     
    
#line 167 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 168 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 169 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
/* exec sql end declare section */
#line 170 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, usernameNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 179 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 179 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 181 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from delete_database ( $1  , $2  , $3  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 182 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 182 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 184 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 184 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 185 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 185 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 194 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 194 "NativeAdapter.pgc"

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
     
     
     

     
     
     
     
     
     
    
#line 223 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 224 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 225 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 227 "NativeAdapter.pgc"
 long item_id ;
 
#line 228 "NativeAdapter.pgc"
 char item_name [ BUFSIZE ] ;
 
#line 229 "NativeAdapter.pgc"
 long item_amount ;
 
#line 230 "NativeAdapter.pgc"
 int item_price ;
 
#line 231 "NativeAdapter.pgc"
 char item_color [ BUFSIZE ] ;
 
#line 232 "NativeAdapter.pgc"
 bool item_refurbished ;
/* exec sql end declare section */
#line 233 "NativeAdapter.pgc"


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
#line 251 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 251 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 253 "NativeAdapter.pgc"

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
#line 254 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 254 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 256 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 256 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 257 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 257 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    (*env)->ReleaseStringUTFChars(env, name, nameNtv);
    (*env)->ReleaseStringUTFChars(env, color, colorNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 269 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 269 "NativeAdapter.pgc"

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
     
     
     

     
     
    
#line 291 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 292 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 293 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 295 "NativeAdapter.pgc"
 char param_name [ BUFSIZE ] ;
 
#line 296 "NativeAdapter.pgc"
 char param_value [ BUFSIZE ] ;
/* exec sql end declare section */
#line 297 "NativeAdapter.pgc"


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
#line 311 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 311 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 313 "NativeAdapter.pgc"

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
#line 314 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 314 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 316 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 316 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 317 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 317 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    (*env)->ReleaseStringUTFChars(env, paramName, paramNameNtv);
    (*env)->ReleaseStringUTFChars(env, paramValue, paramValueNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 329 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 329 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
}