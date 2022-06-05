package com.dreamteam.sqljbaseddb.repositories;

import com.dreamteam.sqljbaseddb.entities.Authentication;

import java.sql.SQLException;
import java.util.List;

public interface DatabaseRepository {
    List<String> findAll(Authentication auth);

    void testConnect(String database, Authentication auth) throws SQLException;

    void save(String database, Authentication auth) throws SQLException;

    void delete(String database, Authentication auth) throws SQLException;
}
