package com.dreamteam.sqljbaseddb.repositories;

import com.dreamteam.sqljbaseddb.entities.Authentication;

import java.sql.SQLException;
import java.util.List;

public interface DatabaseRepository {
    List<String> findAll(Authentication auth) throws SQLException, ClassNotFoundException;

    void testConnect(String database, Authentication auth) throws SQLException, ClassNotFoundException;

    void save(String database, Authentication auth) throws SQLException, ClassNotFoundException;

    boolean delete(String database, Authentication auth) throws SQLException, ClassNotFoundException;
}
