package com.dreamteam.sqljbaseddb.repositories;

import com.dreamteam.sqljbaseddb.entities.Authentication;
import com.dreamteam.sqljbaseddb.entities.Item;

import java.sql.SQLException;
import java.util.List;
import java.util.Optional;

public interface ItemRepository {
    List<Item> findAll(Authentication auth) throws SQLException, ClassNotFoundException;

    void save(Item item, Authentication auth) throws SQLException, ClassNotFoundException;

    void deleteById(Long id, Authentication auth) throws SQLException, ClassNotFoundException;

    Optional<Item> findItemById(Long id, Authentication auth) throws SQLException, ClassNotFoundException;

    List<Item> findAllItemsById(Long id, Authentication auth) throws SQLException, ClassNotFoundException;

    List<Item> findAllItemsByName(String name, Authentication auth) throws SQLException, ClassNotFoundException;

    List<Item> findAllItemsByAmountAvailable(Long amountAvailable, Authentication auth) throws SQLException, ClassNotFoundException;

    List<Item> findAllItemsByPrice(Integer price, Authentication auth) throws SQLException, ClassNotFoundException;

    List<Item> findAllItemsByColor(String color, Authentication auth) throws SQLException, ClassNotFoundException;

    List<Item> findAllItemsByRefurbished(Boolean refurbished, Authentication auth) throws SQLException, ClassNotFoundException;

    void deleteAllItemsByName(String name, Authentication auth) throws SQLException, ClassNotFoundException;

    void deleteAllItemsByAmountAvailable(Long amountAvailable, Authentication auth) throws SQLException, ClassNotFoundException;

    void deleteAllItemsByPrice(Integer price, Authentication auth) throws SQLException, ClassNotFoundException;

    void deleteAllItemsByColor(String color, Authentication auth) throws SQLException, ClassNotFoundException;

    void deleteAllItemsByRefurbished(Boolean refurbished, Authentication auth) throws SQLException, ClassNotFoundException;

    void deleteAllItems(Authentication auth) throws SQLException, ClassNotFoundException;
}
