# ```sqljbased-bd```

UI and server for accessing PostgreSQL using ESQL and JNI.

## How I run it

Switch to project
```shell
cd D:/Programs/IntelliJIDEA/sqljbased-db
```

Switch to repositories folder
```shell
cd backend/src/main/java/com/dreamteam/sqljbaseddb/repositories
```

Compile Java code to JNI header, precompile PGC to C, compile C to jnilib
```shell
javac -h ./ NativeAdapter.java |\
 ecpg NativeAdapter.pgc |\
  gcc NativeAdapter.c -o ../../../../../resources/libmylib.jnilib -shared \
  -IC:/Users/rc199/.jdks/openjdk-17.0.2/include \
  -IC:/Users/rc199/.jdks/openjdk-17.0.2/include/win32 \
  -ID:/Programs/PostgreSQL/include \
  -LD:/Programs/PostgreSQL/bin \
  -lecpg
```

And run as usual program

## Screenshots

### Operations with items

![img.png](screenshots/img.png)

Prefilled data

![img_1.png](screenshots/img_1.png)

Add item

![img_2.png](screenshots/img_2.png)

Item was added

![img_3.png](screenshots/img_3.png)

Search

![img_4.png](screenshots/img_4.png)

Delete found items

![img_5.png](screenshots/img_5.png)

Add item and edit

![img_6.png](screenshots/img_6.png)

Item was edited

![img_7.png](screenshots/img_7.png)

Delete specific item

![img_8.png](screenshots/img_8.png)

Item was deleted

![img_9.png](screenshots/img_9.png)

Clear table (will clear table in database)

![img_10.png](screenshots/img_10.png)

Table was cleared

## Operations with databases

![img_11.png](screenshots/img_11.png)

All databases

![img_12.png](screenshots/img_12.png)

System shows databases only with 'jdbc_' prefix

![img_13.png](screenshots/img_13.png)

Add new database

![img_14.png](screenshots/img_14.png)

Database was added. Table 'items' was added automatically.
I added one item.

![img_15.png](screenshots/img_15.png)

Database in pgAdmin

![img_16.png](screenshots/img_16.png)

Delete database

![img_17.png](screenshots/img_17.png)

Database deleted from system

![img_18.png](screenshots/img_18.png)

and from server

### Operations with users

![img_19.png](screenshots/img_19.png)

Add user

![img_20.png](screenshots/img_20.png)

User was added

![img_21.png](screenshots/img_21.png)

Login

![img_22.png](screenshots/img_22.png)

User has read-only access to only one database - which
was opened when they were created. If user tries to 
open another database, it will be empty for them.

![img_23.png](screenshots/img_23.png)

Database is empty

![img_24.png](screenshots/img_24.png)

While 'postgres' (superuser) can see items

### Backups

![img_25.png](screenshots/img_25.png)

Backups can be in CSV and in XLSX

![img_26.png](screenshots/img_26.png)

CSV backup

![img_27.png](screenshots/img_27.png)

XLSX backup

Uploading backup not working since there are issues
with API requests