package com.dreamteam.sqljbaseddb.repositories;

public class NativeAdapter {
    static {
        System.load("D:\\Programs\\IntelliJIDEA\\sqljbased-db\\backend\\src\\main\\resources\\libmylib.jnilib");
    }

    public static boolean deleteDatabase(String database, String username, String password) {
        return delete(database, username, password);
    }

    private static native boolean delete(String database, String username, String password);
}
