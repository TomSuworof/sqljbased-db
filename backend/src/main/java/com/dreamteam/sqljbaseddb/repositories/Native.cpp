#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "com_dreamteam_sqljbaseddb_repositories_Native.h"

#define BUFSIZE 64

EXEC SQL include sqlca;
EXEC SQL include pgtypes_date;

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

    EXEC SQL begin declare section;
    char database_name[BUFSIZE];
    char user_name[BUFSIZE];
    char user_passwd[BUFSIZE];
    EXEC SQL end declare section;

    strncpy(database_name, databaseNtv, BUFSIZE - 1)
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, usernameNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    EXEC SQL connect to data_management as dm_conn user :user_name/:user_passwd;

    EXEC SQL whenever sqlerror goto error_lab;
    EXEC SQL select * from delete_database(:database_name, :user_name, :user_passwd);

//    EXEC sql declare cust_supply cursor for
//      select s.oid,c.name,s.data from
//          (supply s JOIN customer c ON s.cust_id=c.cid)
//    	   where s.sum_price>= :sum_price
//      order by s.oid;
//
//    if(argc!=3){
//      printf("usage:\n%s user_name user_passwd\n",argv[0]);
//      return 1;
//    }
//    strncpy(user_name,argv[1],BUFSIZE-1);
//    user_name[BUFSIZE-1]=0;
//    strncpy(user_passwd,argv[2],BUFSIZE-1);
//    user_passwd[BUFSIZE-1]=0;
//    EXEC sql connect to books as books_connection
//         user :user_name/:user_passwd;
//
//    printf("input price\n");
//    scanf("%d",&sum_price);
//
//    EXEC sql open cust_supply;
//    while(1){
//      EXEC sql fetch cust_supply into :s_oid,:c_name,:s_data;
//      if(sqlca.sqlcode!=0){
//        if(sqlca.sqlcode!=100)
//            printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
//        break;
//      }
//      printf("oid=%d cust_name=%s date=%s\n",s_oid,c_name.arr,PGTYPESdate_to_asc(s_data));
//    }
//    EXEC sql close cust_supply;

    EXEC SQL commit;
    EXEC SQL disconnect dm_conn;

    env->ReleaseStringUTFChars(database, databaseNtv);
    env->ReleaseStringUTFChars(username, usernameNtv);
    env->ReleaseStringUTFChars(password, passwordNtv);

    return true;

  error_lab:
    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
    return false;
}