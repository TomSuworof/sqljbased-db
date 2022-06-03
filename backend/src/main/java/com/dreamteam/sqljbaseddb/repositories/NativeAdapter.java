package com.dreamteam.sqljbaseddb.repositories;

import java.sql.SQLException;
import java.util.List;

public class NativeAdapter {
    static {
        System.load("D:\\Programs\\IntelliJIDEA\\sqljbased-db\\backend\\src\\main\\resources\\libmylib.jnilib");
    }

    public static List<String> findAll(String username, String password) {
        return List.of(getAll(username, password));
    }

    public static void testConnect(String database, String username, String password) throws SQLException {
        boolean success = test(database, username, password);
        if (!success) {
            throw new SQLException("test connection failed");
        }
    }

    public static void saveDatabase(String database, String username, String password) throws SQLException {
        boolean success = save(database, username, password);

        if (!success) {
            throw new SQLException("save failed");
        }
    }

    public static void deleteDatabase(String database, String username, String password) throws SQLException {
        boolean success = delete(database, username, password);

        if (!success) {
            throw new SQLException("delete failed");
        }
    }


    public static void addItemToDatabase(String database, String username, String password, long id, String name, long amount, int price, String color, boolean refurbished) {
        addItem(database, username, password, id, name, amount, price, color, refurbished);
    }

    public static void deleteItemFromDatabase(String database, String username, String password, String paramName, String paramValue) {
        deleteItem(database, username, password, paramName, paramValue);
    }


    private static native String[] getAll(String username, String password);

    private static native boolean test(String database, String username, String password);

    private static native boolean save(String database, String username, String password);

    private static native boolean delete(String database, String username, String password);


    private static native boolean addItem(String database, String username, String password, long id, String name, long amount, int price, String color, boolean refurbished);

    private static native boolean deleteItem(String database, String username, String password, String paramName, String paramValue);
}
