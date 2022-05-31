/* Processed by ecpg (12.4) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.pgc"
#include "Native.h"

#define BUFSIZE 64

void delete_database(const char *databaseNtv, const char *usernameNtv, const char *passwordNtv) {

    /* exec sql begin declare section */
     
     
     
    
#line 8 "./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.pgc"
 char database_name [ BUFSIZE ] ;
 
#line 9 "./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.pgc"
 char user_name [ BUFSIZE ] ;
 
#line 10 "./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.pgc"
 char user_passwd [ BUFSIZE ] ;
/* exec sql end declare section */
#line 11 "./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.pgc"


    strncpy(database_name, databaseNtv, BUFSIZE - 1);
    database_name[BUFSIZE - 1] = 0;
    strncpy(user_name, usernameNtv, BUFSIZE - 1);
    user_name[BUFSIZE - 1] = 0;
    strncpy(user_passwd, usernameNtv, BUFSIZE - 1);
    user_passwd[BUFSIZE - 1] = 0;

    { ECPGconnect(__LINE__, 0, "data_management" , user_name , user_passwd , "dm_conn", 0); }
#line 20 "./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.pgc"


    /* exec sql whenever sqlerror  goto  error_lab ; */
#line 22 "./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.pgc"

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select * from delete_database ( $1  , $2  , $3  )", 
	ECPGt_char,(database_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_name),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(user_passwd),(long)BUFSIZE,(long)1,(BUFSIZE)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);
#line 23 "./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 23 "./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.pgc"


    { ECPGtrans(__LINE__, NULL, "commit");
#line 25 "./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 25 "./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.pgc"

    { ECPGdisconnect(__LINE__, "dm_conn");
#line 26 "./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.pgc"

if (sqlca.sqlcode < 0) goto error_lab;}
#line 26 "./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.pgc"


  error_lab:
    printf("sqlcode=%d %s\n",sqlca.sqlcode,sqlca.sqlerrm.sqlerrmc);
}