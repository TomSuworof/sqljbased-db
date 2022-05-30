package com.dreamteam.sqljbaseddb.database;

import java.sql.Connection;

public interface ConnectionManager extends AutoCloseable {

    Connection getConnection();
}
