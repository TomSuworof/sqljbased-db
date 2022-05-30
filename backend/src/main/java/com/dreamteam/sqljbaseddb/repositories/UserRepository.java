package com.dreamteam.sqljbaseddb.repositories;

import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.entities.User;

import java.sql.SQLException;

public interface UserRepository {
    void save(User user, Authentication auth) throws SQLException, ClassNotFoundException;

    boolean existsByUsername(String username, Authentication auth) throws SQLException, ClassNotFoundException;
}
