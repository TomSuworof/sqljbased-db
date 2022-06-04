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

    /* exec sql begin declare section */
     
     
     
       
    
#line 20 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 21 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 22 "NativeAdapter.pgc"
 char databases [ BUFSIZE ] [ BUFSIZE ] ;
 
#line 23 "NativeAdapter.pgc"
 int num_databases = BUFSIZE ;
/* exec sql end declare section */
#line 24 "NativeAdapter.pgc"


    /* declare curs cursor for select dbname from get_all_databases ( ) */
#line 27 "NativeAdapter.pgc"


    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 34 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 35 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 35 "NativeAdapter.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select count ( dbname ) from get_all_databases ( )", ECPGt_EOIT, 
	ECPGt_int,&(num_databases),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 37 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 37 "NativeAdapter.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare curs cursor for select dbname from get_all_databases ( )", ECPGt_EOIT, ECPGt_EORT);
#line 39 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 39 "NativeAdapter.pgc"


    for (int i = 0; i < num_databases; i++)
    {
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch next from curs", ECPGt_EOIT, 
	ECPGt_char,(databases[i]),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 43 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 43 "NativeAdapter.pgc"

    }

    for (int i = 0; i < num_databases; i++)
    {
        printf("%d %s\n", i, databases[i]);
    }

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close curs", ECPGt_EOIT, ECPGt_EORT);
#line 51 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 51 "NativeAdapter.pgc"


    { ECPGdisconnect(__LINE__, "dm_conn");
#line 53 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 53 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    jobjectArray ret = (jobjectArray) (*env)->NewObjectArray(env, num_databases, (*env)->FindClass(env, "java/lang/String"), (*env)->NewStringUTF(env, ""));

    for (int i = 0; i < num_databases; i++)
    {
        (*env)->SetObjectArrayElement(env, ret, i, (*env)->NewStringUTF(env, databases[i]));
    }

    return ret;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 68 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 68 "NativeAdapter.pgc"

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
     
     
     
    
#line 85 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 86 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 87 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
/* exec sql end declare section */
#line 88 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 97 "NativeAdapter.pgc"

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 98 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 98 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 99 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 99 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 108 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 108 "NativeAdapter.pgc"

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
     
     
     
    
#line 125 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 126 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 127 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
/* exec sql end declare section */
#line 128 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 137 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 137 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 139 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from create_database ( $1  , $2  , $3  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 140 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 140 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 142 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 142 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 143 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 143 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 152 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 152 "NativeAdapter.pgc"

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
     
     
     
    
#line 169 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 170 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 171 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
/* exec sql end declare section */
#line 172 "NativeAdapter.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 181 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 181 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 183 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from delete_database ( $1  , $2  , $3  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 184 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 184 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 186 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 186 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 187 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 187 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 196 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 196 "NativeAdapter.pgc"

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
     
     
     

     
     
     
     
     
     
    
#line 225 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 226 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 227 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 229 "NativeAdapter.pgc"
 long item_id ;
 
#line 230 "NativeAdapter.pgc"
 char item_name [ BUFSIZE ] ;
 
#line 231 "NativeAdapter.pgc"
 long item_amount ;
 
#line 232 "NativeAdapter.pgc"
 int item_price ;
 
#line 233 "NativeAdapter.pgc"
 char item_color [ BUFSIZE ] ;
 
#line 234 "NativeAdapter.pgc"
 bool item_refurbished ;
/* exec sql end declare section */
#line 235 "NativeAdapter.pgc"


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

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 253 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 253 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 255 "NativeAdapter.pgc"

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
#line 256 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 256 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 258 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 258 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 259 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 259 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    (*env)->ReleaseStringUTFChars(env, name, nameNtv);
    (*env)->ReleaseStringUTFChars(env, color, colorNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 271 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 271 "NativeAdapter.pgc"

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
     
     
     

     
     
    
#line 293 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 294 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 295 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 297 "NativeAdapter.pgc"
 char param_name [ BUFSIZE ] ;
 
#line 298 "NativeAdapter.pgc"
 char param_value [ BUFSIZE ] ;
/* exec sql end declare section */
#line 299 "NativeAdapter.pgc"


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

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 313 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 313 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 315 "NativeAdapter.pgc"

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
#line 316 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 316 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 318 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 318 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 319 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 319 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);
    (*env)->ReleaseStringUTFChars(env, username, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, password, passwordNtv);

    (*env)->ReleaseStringUTFChars(env, paramName, paramNameNtv);
    (*env)->ReleaseStringUTFChars(env, paramValue, paramValueNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 331 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 331 "NativeAdapter.pgc"

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
     
     
     
     
    
#line 351 "NativeAdapter.pgc"
 char username_to_save [ BUFSIZE ] ;
 
#line 352 "NativeAdapter.pgc"
 char password_to_save [ BUFSIZE ] ;
 
#line 353 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 354 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
/* exec sql end declare section */
#line 355 "NativeAdapter.pgc"


    strncpy(username_to_save, usernameToSaveNtv, BUFSIZE - 1);
    username_to_save[BUFSIZE - 1] = 0;
    strncpy(password_to_save, passwordToSaveNtv, BUFSIZE - 1);
    password_to_save[BUFSIZE - 1] = 0;

    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, passwordNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 367 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 367 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 369 "NativeAdapter.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from add_superuser ( $1  , $2  , $3  , $4  )", 
	ECPGt_char,(username_to_save),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(password_to_save),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 370 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 370 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 372 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 372 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 373 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 373 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, usernameToSave, usernameToSaveNtv);
    (*env)->ReleaseStringUTFChars(env, passwordToSave, passwordToSaveNtv);

    (*env)->ReleaseStringUTFChars(env, authUsername, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, authPassword, passwordNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 384 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 384 "NativeAdapter.pgc"

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
     
     
     
     
     
    
#line 406 "NativeAdapter.pgc"
 char username_to_save [ BUFSIZE ] ;
 
#line 407 "NativeAdapter.pgc"
 char password_to_save [ BUFSIZE ] ;
 
#line 408 "NativeAdapter.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 409 "NativeAdapter.pgc"
 char user_passwd [ BUFSIZE ] ;
 
#line 410 "NativeAdapter.pgc"
 char database_name [ BUFSIZE ] ;
/* exec sql end declare section */
#line 411 "NativeAdapter.pgc"


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

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); 
#line 425 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 425 "NativeAdapter.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 427 "NativeAdapter.pgc"

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
#line 428 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 428 "NativeAdapter.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 430 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 430 "NativeAdapter.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 431 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 431 "NativeAdapter.pgc"


    (*env)->ReleaseStringUTFChars(env, usernameToSave, usernameToSaveNtv);
    (*env)->ReleaseStringUTFChars(env, passwordToSave, passwordToSaveNtv);

    (*env)->ReleaseStringUTFChars(env, authUsername, usernameNtv);
    (*env)->ReleaseStringUTFChars(env, authPassword, passwordNtv);
    (*env)->ReleaseStringUTFChars(env, database, databaseNtv);

    return true;

  error_lab:
    { ECPGdisconnect(__LINE__, "dm_conn");
#line 443 "NativeAdapter.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 443 "NativeAdapter.pgc"

    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
}