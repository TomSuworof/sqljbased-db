package com.dreamteam.sqljbaseddb.services;

import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.entities.User;
import com.dreamteam.sqljbaseddb.exceptions.DuplicatedUserException;
import com.dreamteam.sqljbaseddb.exceptions.UserNotFoundException;
import com.dreamteam.sqljbaseddb.repositories.UserRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.sql.SQLException;

@Service
@RequiredArgsConstructor
public class UsersService {
    private final UserRepository userRepository;

    public void addUser(User user, Authentication auth) throws SQLException, ClassNotFoundException {
        if (userRepository.existsByUsername(user.getUsername(), auth)) {
            throw new DuplicatedUserException();
        }
        userRepository.save(user, auth);
    }

    public void removeUser(String username, Authentication auth) throws SQLException, ClassNotFoundException {
        if (!userRepository.existsByUsername(username, auth)) {
            throw new UserNotFoundException();
        }
    }
}
