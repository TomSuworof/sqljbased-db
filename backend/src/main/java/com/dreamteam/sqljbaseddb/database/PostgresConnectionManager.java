package com.dreamteam.sqljbaseddb.database;

import com.dreamteam.sqljbaseddb.entities.Authentication;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class PostgresConnectionManager implements ConnectionManager {
    private static final String DRIVER = "org.postgresql.Driver";
    private static final String URL = "jdbc:postgresql://localhost:5432/data_management";
    // default database, where all functions are stored
    // System.getenv("DATASOURCE_URL");

    private static ConnectionManager instance;
    private static Connection conn;

    private PostgresConnectionManager() throws ClassNotFoundException {
        Class.forName(DRIVER);
    }

    public static ConnectionManager getInstance(Authentication auth)
            throws SQLException, ClassNotFoundException {
        if (instance == null) {
            instance = new PostgresConnectionManager();
        }

        if (conn == null || conn.isClosed()) {
            conn = DriverManager.getConnection(URL, auth.getUsername(), auth.getPassword());
        }

        return instance;
    }

    @Override
    public Connection getConnection() {
        return conn;
    }

    @Override
    public void close() throws SQLException {
        if (conn != null) {
            conn.close();
        }
    }
}
