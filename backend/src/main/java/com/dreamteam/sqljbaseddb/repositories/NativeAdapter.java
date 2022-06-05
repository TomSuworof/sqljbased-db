package com.dreamteam.sqljbaseddb.repositories;

import java.sql.SQLException;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

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


    private static List<List<String>> preprocessItems(String[][] items) {
        if (items == null) {
            try {
                Arrays.stream(items).forEach(System.out::println); // if 'items' is null, then there is an error in pgc code
            } catch (NullPointerException e) {
                e.printStackTrace();
            }
            return Collections.emptyList();
        }

        return Arrays.stream(items).map(List::of).collect(Collectors.toList());
    }

    public static List<List<String>> findAllItems(String database, String username, String password) {
        long numberOfAllItems = Long.parseLong(getNumberOfAllItems(database, username, password));
        return preprocessItems(getAllItems(database, username, password, numberOfAllItems));
    }

    public static List<List<String>> findItemsByParam(String database, String username, String password, String paramName, String paramValue) {
        long numberOfItemsToFind = Long.parseLong(getNumberOfItemsPyParam(database, username, password, paramName, paramValue));
        return preprocessItems(getItemsByParam(database, username, password, paramName, paramValue, numberOfItemsToFind));
    }

    public static void addItemToDatabase(String database, String username, String password, long id, String name, long amount, int price, String color, boolean refurbished) {
        addItem(database, username, password, id, name, amount, price, color, refurbished);
    }

    public static void deleteItemFromDatabase(String database, String username, String password, String paramName, String paramValue) {
        deleteItem(database, username, password, paramName, paramValue);
    }


    public static boolean userExistsByUsername(String usernameToSearch, String username, String password, String database) {
        return existsByUsername(usernameToSearch, username, password, database);
    }

    public static void addSuperuserToAllDatabases(String usernameToSave, String passwordToSave, String authUsername, String authPassword) {
        addSuperuser(usernameToSave, passwordToSave, authUsername, authPassword);
    }

    public static void addCasualToThisDatabase(String usernameToSave, String passwordToSave, String authUsername, String authPassword, String database) {
        addCasual(usernameToSave, passwordToSave, authUsername, authPassword, database);
    }


    // native methods

    private static native String[] getAll(String username, String password);

    private static native boolean test(String database, String username, String password);

    private static native boolean save(String database, String username, String password);

    private static native boolean delete(String database, String username, String password);


    private static native String getNumberOfAllItems(String database, String username, String password);

    private static native String[][] getAllItems(String database, String username, String password, long numberOfItems);

    private static native String getNumberOfItemsPyParam(String database, String username, String password, String paramName, String paramValue);

    private static native String[][] getItemsByParam(String database, String username, String password, String paramName, String paramValue, long numberOfItems);

    private static native boolean addItem(String database, String username, String password, long id, String name, long amount, int price, String color, boolean refurbished);

    private static native boolean deleteItem(String database, String username, String password, String paramName, String paramValue);


    private static native boolean existsByUsername(String usernameToSearch, String username, String password, String database);

    private static native boolean addSuperuser(String usernameToSave, String passwordToSave, String authUsername, String authPassword);

    private static native boolean addCasual(String usernameToSave, String passwordToSave, String authUsername, String authPassword, String database);
}
