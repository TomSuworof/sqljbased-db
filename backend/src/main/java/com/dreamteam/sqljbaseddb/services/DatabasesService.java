package com.dreamteam.sqljbaseddb.services;

import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.repositories.DatabaseRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.sql.SQLException;
import java.util.List;

@Service
@RequiredArgsConstructor
public class DatabasesService {
    private final DatabaseRepository databaseRepository;

    public List<String> getAllDatabases(Authentication auth) throws SQLException, ClassNotFoundException {
        return databaseRepository.findAll(auth);
    }

    public void switchToDatabase(String database, Authentication auth) throws SQLException, ClassNotFoundException {
        databaseRepository.testConnect(database, auth);
    }

    public void addDatabase(String database, Authentication auth) throws SQLException, ClassNotFoundException {
        databaseRepository.save(database, auth);
    }

    public void deleteDatabase(String database, Authentication auth) throws SQLException, ClassNotFoundException {
        databaseRepository.delete(database, auth);
    }
}
