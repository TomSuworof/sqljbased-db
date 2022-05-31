# ```sqljbased-bd```

UI and server for accessing PostgreSQL using ESQL and JNI.

P.S.: should be SQLJ, but it did not work.

## How I run it

Create header-file for JNI and adapter
```shell
PS D:\Programs\IntelliJIDEA\sqljbased-db> javac -h ./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories ./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/NativeAdapter.java
```

Precompile ECPG sql-access to C 
```shell
PS D:\Programs\IntelliJIDEA\sqljbased-db> ecpg ./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.pgc
```

Compile C to Output
```shell
PS D:\Programs\IntelliJIDEA\sqljbased-db> gcc -c ./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.c -o ./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/Native.o -ID:\Programs\PostgreSQL\include
```

Compile C++ adapter to Output
```shell
PS D:\Programs\IntelliJIDEA\sqljbased-db> gcc -c ./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/NativeAdapter.cpp -o ./backend/src/main/java/com/dreamteam/sqljbaseddb/repositories/NativeAdapter.o -shared -IC:\Users\rc199\.jdks\openjdk-17.0.2\include -IC:\Users\rc199\.jdks\openjdk-17.0.2\include\win32
```

Link Output sql-access and Output adapter
```shell

```