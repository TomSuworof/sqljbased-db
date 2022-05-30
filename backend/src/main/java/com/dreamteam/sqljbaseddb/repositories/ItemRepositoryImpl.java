package com.dreamteam.sqljbaseddb.repositories;

import com.dreamteam.sqljbaseddb.database.PostgresConnectionManager;
import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.entities.Item;
import com.dreamteam.sqljbaseddb.exceptions.DuplicatedItemException;
import org.springframework.stereotype.Repository;

import java.sql.*;
import java.util.*;

@Repository
public class ItemRepositoryImpl implements ItemRepository {
    @Override
    public List<Item> findAll(Authentication auth) throws SQLException, ClassNotFoundException {
        Connection connection = PostgresConnectionManager.getInstance(auth).getConnection();
        connection.setAutoCommit(false);
        Savepoint savepoint = connection.setSavepoint();

        List<Item> items = new LinkedList<>();

        try {
            PreparedStatement statement = connection.prepareStatement("select * from select_all_from_database(?, ?, ?)");
            statement.setString(1, auth.getDatabase());
            statement.setString(2, auth.getUsername());
            statement.setString(3, auth.getPassword());
            ResultSet set = statement.executeQuery();
            connection.commit();

            while (set.next()) {
                items.add(Item.deserialize(set));
            }
        } catch (SQLException e) {
            connection.rollback(savepoint);
            throw e;
        }

        return items;
    }

    @Override
    public void save(Item item, Authentication auth) throws SQLException, ClassNotFoundException {
        Connection connection = PostgresConnectionManager.getInstance(auth).getConnection();
        connection.setAutoCommit(false);
        Savepoint savepoint = connection.setSavepoint();

        try {
            PreparedStatement statement = connection.prepareStatement("select * from insert_into_database(?, ?, ?,  ?, ?, ?, ?, ?, ?)");

            statement.setString(1, auth.getDatabase());
            statement.setString(2, auth.getUsername());
            statement.setString(3, auth.getPassword());

            statement.setLong(4, item.getId());
            statement.setString(5, item.getName());
            statement.setLong(6, item.getAmountAvailable());
            statement.setInt(7, item.getPrice());
            statement.setString(8, item.getColor());
            statement.setBoolean(9, item.getRefurbished());
            statement.execute();
            connection.commit();
        } catch (SQLException e) {
            connection.rollback(savepoint);
            throw e;
        }
    }

    @Override
    public Optional<Item> findItemById(Long id, Authentication auth) throws SQLException, ClassNotFoundException {
        List<Item> items = findItemsByParam("id", String.valueOf(id), auth);
        if (items.size() > 1) {
            throw new DuplicatedItemException();
        } else if (items.size() == 1) {
            return Optional.of(items.get(0));
        } else {
            return Optional.empty();
        }
    }

    @Override
    public List<Item> findAllItemsById(Long id, Authentication auth) throws SQLException, ClassNotFoundException {
        return findItemsByParam("id", String.valueOf(id), auth);
    }

    @Override
    public List<Item> findAllItemsByName(String name, Authentication auth) throws SQLException, ClassNotFoundException {
        return findItemsByParam("name", name, auth);
    }

    @Override
    public List<Item> findAllItemsByAmountAvailable(Long amountAvailable, Authentication auth) throws SQLException, ClassNotFoundException {
        return findItemsByParam("amountAvailable", String.valueOf(amountAvailable), auth);
    }

    @Override
    public List<Item> findAllItemsByPrice(Integer price, Authentication auth) throws SQLException, ClassNotFoundException {
        return findItemsByParam("price", String.valueOf(price), auth);
    }

    @Override
    public List<Item> findAllItemsByColor(String color, Authentication auth) throws SQLException, ClassNotFoundException {
        return findItemsByParam("color", color, auth);
    }

    @Override
    public List<Item> findAllItemsByRefurbished(Boolean refurbished, Authentication auth) throws SQLException, ClassNotFoundException {
        return findItemsByParam("refurbished", String.valueOf(refurbished), auth);
    }

    @Override
    public void deleteById(Long id, Authentication auth) throws SQLException, ClassNotFoundException {
        deleteItemsByParam("id", String.valueOf(id), auth);
    }

    @Override
    public void deleteAllItemsByName(String name, Authentication auth) throws SQLException, ClassNotFoundException {
        deleteItemsByParam("name", name, auth);
    }

    @Override
    public void deleteAllItemsByAmountAvailable(Long amountAvailable, Authentication auth) throws SQLException, ClassNotFoundException {
        deleteItemsByParam("amountAvailable", String.valueOf(amountAvailable), auth);
    }

    @Override
    public void deleteAllItemsByPrice(Integer price, Authentication auth) throws SQLException, ClassNotFoundException {
        deleteItemsByParam("price", String.valueOf(price), auth);
    }

    @Override
    public void deleteAllItemsByColor(String color, Authentication auth) throws SQLException, ClassNotFoundException {
        deleteItemsByParam("color", color, auth);
    }

    @Override
    public void deleteAllItemsByRefurbished(Boolean refurbished, Authentication auth) throws SQLException, ClassNotFoundException {
        deleteItemsByParam("refurbished", String.valueOf(refurbished), auth);
    }

    @Override
    public void deleteAllItems(Authentication auth) throws SQLException, ClassNotFoundException {
        Connection connection = PostgresConnectionManager.getInstance(auth).getConnection();
        connection.setAutoCommit(false);
        Savepoint savepoint = connection.setSavepoint();

        try {
            PreparedStatement statement = connection.prepareStatement("select * from delete_all_from_database(?, ?, ?)");
            statement.setString(1, auth.getDatabase());
            statement.setString(2, auth.getUsername());
            statement.setString(3, auth.getPassword());
            statement.executeQuery();
            connection.commit();
        } catch (SQLException e) {
            connection.rollback(savepoint);
            throw e;
        }
    }

    private List<Item> findItemsByParam(String paramName, String paramValue, Authentication auth) throws SQLException, ClassNotFoundException {
        Connection connection = PostgresConnectionManager.getInstance(auth).getConnection();
        connection.setAutoCommit(false);
        Savepoint savepoint = connection.setSavepoint();

        List<Item> items = new LinkedList<>();

        try {
            PreparedStatement statement = connection.prepareStatement("select * from select_from_database_by_param(?, ?, ?, ?, ?)");
            statement.setString(1, auth.getDatabase());
            statement.setString(2, auth.getUsername());
            statement.setString(3, auth.getPassword());
            statement.setString(4, paramName);
            statement.setString(5, paramValue);
            ResultSet set = statement.executeQuery();
            connection.commit();

            while (set.next()) {
                items.add(Item.deserialize(set));
            }
        } catch (SQLException e) {
            connection.rollback(savepoint);
            throw e;
        }

        return items;
    }

    private void deleteItemsByParam(String paramName, String paramValue, Authentication auth) throws SQLException, ClassNotFoundException {
        Connection connection = PostgresConnectionManager.getInstance(auth).getConnection();
        connection.setAutoCommit(false);
        Savepoint savepoint = connection.setSavepoint();

        try {
            PreparedStatement statement = connection.prepareStatement("select * from delete_from_database_by_param(?, ?, ?, ?, ?)");
            statement.setString(1, auth.getDatabase());
            statement.setString(2, auth.getUsername());
            statement.setString(3, auth.getPassword());
            statement.setString(4, paramName);
            statement.setString(5, paramValue);
            statement.executeQuery();
            connection.commit();
        } catch (SQLException e) {
            connection.rollback(savepoint);
            throw e;
        }
    }
}
