package com.dreamteam.sqljbaseddb.repositories;

import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.entities.User;

public interface UserRepository {
    void save(User user, Authentication auth);

    boolean existsByUsername(String username, Authentication auth);
}
