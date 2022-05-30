package com.dreamteam.sqljbaseddb.repositories;

import com.dreamteam.sqljbaseddb.database.PostgresConnectionManager;
import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.entities.User;
import org.springframework.stereotype.Repository;

import java.sql.*;

@Repository
public class UserRepositoryImpl implements UserRepository {
    @Override
    public void save(User user, Authentication auth) throws SQLException, ClassNotFoundException {
        switch (user.getType()) {
            case "superuser" -> saveSuperuser(user, auth);
            case "casual" -> saveCasual(user, auth);
        }
    }

    @Override
    public boolean existsByUsername(String username, Authentication auth) throws SQLException, ClassNotFoundException {
        Connection connection = PostgresConnectionManager.getInstance(auth).getConnection();
        connection.setAutoCommit(false);
        Savepoint savepoint = connection.setSavepoint();

        ResultSet set = null;

        try {
            PreparedStatement statement = connection.prepareStatement("select * from get_user_by_username(?, ?, ?, ?)");
            statement.setString(1, username);
            statement.setString(2, auth.getUsername());
            statement.setString(3, auth.getPassword());
            statement.setString(4, auth.getDatabase());
            set = statement.executeQuery();
            connection.commit();
            return set.next();
        } catch (SQLException e) {
            connection.rollback(savepoint);
        }

        return false;
    }

    private void saveSuperuser(User user, Authentication auth) throws SQLException, ClassNotFoundException {
        Connection connection = PostgresConnectionManager.getInstance(auth).getConnection();
        connection.setAutoCommit(false);
        Savepoint savepoint = connection.setSavepoint();

        try {
            PreparedStatement statement = connection.prepareStatement("select * from add_superuser(?, ?, ?, ?)");
            statement.setString(1, user.getUsername());
            statement.setString(2, user.getPassword());
            statement.setString(3, auth.getUsername());
            statement.setString(4, auth.getPassword());
            statement.execute();
            connection.commit();
        } catch (SQLException e) {
            connection.rollback(savepoint);
            throw e;
        }
    }

    private void saveCasual(User user, Authentication auth) throws SQLException, ClassNotFoundException {
        Connection connection = PostgresConnectionManager.getInstance(auth).getConnection();
        connection.setAutoCommit(false);
        Savepoint savepoint = connection.setSavepoint();

        try {
            PreparedStatement statement = connection.prepareStatement("select * from add_casual_to_database(?, ?, ?, ?, ?)");
            statement.setString(1, user.getUsername());
            statement.setString(2, user.getPassword());
            statement.setString(3, auth.getUsername());
            statement.setString(4, auth.getPassword());
            statement.setString(5, auth.getDatabase());
            statement.execute();
            connection.commit();
        } catch (SQLException e) {
            connection.rollback(savepoint);
            throw e;
        }
    }
}
