package com.dreamteam.sqljbaseddb.repositories;

import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.entities.User;
import org.springframework.stereotype.Repository;

@Repository
public class UserRepositoryImpl implements UserRepository {
    @Override
    public void save(User user, Authentication auth) {
        switch (user.getType()) {
            case "superuser" -> saveSuperuser(user, auth);
            case "casual" -> saveCasual(user, auth);
        }
    }

    @Override
    public boolean existsByUsername(String username, Authentication auth) {
        return NativeAdapter.userExistsByUsername(username, auth.getUsername(), auth.getPassword(), auth.getDatabase());
    }

    private void saveSuperuser(User user, Authentication auth) {
        NativeAdapter.addSuperuserToAllDatabases(user.getUsername(), user.getPassword(), auth.getUsername(), auth.getPassword());
    }

    private void saveCasual(User user, Authentication auth) {
        NativeAdapter.addCasualToThisDatabase(user.getUsername(), user.getPassword(), auth.getUsername(), auth.getPassword(), auth.getDatabase());
    }
}
