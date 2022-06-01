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
  -lecpg -lpq 
```

And run as usual program