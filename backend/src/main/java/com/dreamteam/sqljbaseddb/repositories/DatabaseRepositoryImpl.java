package com.dreamteam.sqljbaseddb.repositories;

import com.dreamteam.sqljbaseddb.entities.Authentication;
import org.springframework.stereotype.Repository;

import java.sql.*;
import java.util.List;
import java.util.stream.Collectors;

@Repository
public class DatabaseRepositoryImpl implements DatabaseRepository {
    @Override
    public List<String> findAll(Authentication auth) {
        List<String> databases =  NativeAdapter.findAll(auth.getUsername(), auth.getPassword());

        return databases
                .stream()
                .map(name -> name.substring(5)) // remove 'jdbc_' prefix
                .collect(Collectors.toList());
    }

    @Override
    public void testConnect(String database, Authentication auth) throws SQLException {
        NativeAdapter.testConnect(database, auth.getUsername(), auth.getPassword());
    }

    @Override
    public void save(String database, Authentication auth) throws SQLException {
        NativeAdapter.saveDatabase(database, auth.getUsername(), auth.getPassword());
    }

    @Override
    public void delete(String database, Authentication auth) throws SQLException {
        NativeAdapter.deleteDatabase(database, auth.getUsername(), auth.getPassword());
    }
}
